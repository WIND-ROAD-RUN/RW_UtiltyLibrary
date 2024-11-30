#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>
#include <type_traits>

//TODO:添加异常处理
//TODO:更改为优先队列
namespace rw {
    class ThreadPool {
    public:

        /**
         *@Parameters:
         *  - numThreads: The number of threads in the thread pool,it usually equals to the number of cores in the CPU
         *@Methods:
         *  constructor: Create a thread pool with the specified number of threads
         *@Returns: void
         *
         *@Throws:
         *
         */
        explicit ThreadPool(size_t numThreads);

        /**
         * @brief Destructor
         *
         * The destructor will stop the worker threads and join them
         */
        ~ThreadPool();

        /**
         *@Parameters:
         *  - f: The function to be executed
         *  - args: The arguments to be passed to the function
         *@Methods:
         *  enqueue: Add a task to the task queue
         *@Returns: std::future<typename std::invoke_result<F, Args...>::type>
         *  return a future object that can be used to get the result of the function
         *@Throws:
         *  
         */
        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type>;

    private:

        /**
         * @brief The worker threads
         *
         * The worker threads will pull tasks from the task queue and execute
         */
        std::vector<std::thread> workers; 

        /**
         * @brief The task queue
         *
         * The task queue is a queue of tasks that need to be executed by the worker threads
         */
        std::queue<std::function<void()>> tasks;

        /**
         * @brief The mutex to protect the task queue
         *
         * The mutex is used to protect the task queue from being accessed by multiple threads at the same time
         */
        std::mutex queueMutex;

        /**
         * @brief The condition variable to notify the worker threads
         *
         * The condition variable is used to notify the worker threads that there is a new task in the task queue
         */
        std::condition_variable condition;

        /**
         * @brief A flag to indicate that the thread pool should stop
         *
         * The stop flag is used to indicate that the thread pool should stop and that the worker threads should exit
         */
        bool stop;
    };

    ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);
                        this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
                });
        }
    }

    // 添加任务到线程池
    template<class F, class... Args>
    auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type> {
        using returnType = typename std::invoke_result<F, Args...>::type;

        auto task = std::make_shared<std::packaged_task<returnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<returnType> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ThreadPool::~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

}