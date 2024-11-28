#include"utilty_ThreadPool_t.h"
namespace utilty_TreadPool {
    TEST(t,t) {
        rw::ThreadPool pool(std::thread::hardware_concurrency());

        auto result1 = pool.enqueue([] { return std::string("Hello from thread 1"); });
        auto result2 = pool.enqueue([] { return std::string("Hello from thread 2"); });

        std::cout << result1.get() << std::endl;
        std::cout << result2.get() << std::endl;
    
    }

    TEST_F(ThreadPoolTest, ThreadPoolTest_LargeQuantity_random) {
        auto start = std::chrono::high_resolution_clock::now();
        rw::ThreadPool pool(std::thread::hardware_concurrency());

        std::vector<std::future<bool>> results;

        for (int i = 0; i < 20000; ++i) {
            results.emplace_back(pool.enqueue([this] { return this->cheapOperate(std::chrono::microseconds(distMs(gen))); }));
        }

        for (int i = 0; i < 20; ++i) {
            results.emplace_back(pool.enqueue([this] { return this->expensiveOperate(std::chrono::seconds(distS(gen))); }));
        }

        for (auto&& result : results) {
            result.get();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Total cheap operate num:" << this->cheapOperateNum << std::endl;
        std::cout << "Total cheap time:" << this->totalCheapOperateTime.count() << "ms" << std::endl;
        std::cout << "Total expensive operate num:" << this->expensiveOperateNum << std::endl;
        std::cout << "Total expensive time:" << this->totalExpensiveOperateTime.count() << "s" << std::endl;
        std::cout << "Total time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

        SUCCEED();
    }

    TEST_F(ThreadPoolTest, ThreadPoolTest_LargeQuantity) {
        auto start = std::chrono::high_resolution_clock::now();
        rw::ThreadPool pool(std::thread::hardware_concurrency());

        std::vector<std::future<bool>> results;

        for (int i = 0;i<10000;++i) {
            results.emplace_back(pool.enqueue([this] { return this->cheapOperate(std::chrono::microseconds(200)); }));
        }

        for (int i = 0; i < 20; ++i) {
            results.emplace_back(pool.enqueue([this] { return this->expensiveOperate(std::chrono::seconds(2)); }));
        }

        for (auto&& result : results) {
            result.get();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Total cheap operate num:" << this->cheapOperateNum << std::endl;
        std::cout << "Total cheap time:" << this->totalCheapOperateTime.count() << "ms" << std::endl;
        std::cout << "Total expensive operate num:" << this->expensiveOperateNum << std::endl;
        std::cout << "Total expensive time:" << this->totalExpensiveOperateTime.count() << "s" << std::endl;
        std::cout << "Total time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
        
        SUCCEED();
    }

    TEST_F(ThreadPoolTest, ThreadPoolTest_LargeQuantity_NoThreadPool) {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        std::mutex mtx;
        std::condition_variable cv;
        size_t activeThreads = 0;
        const size_t maxThreads = std::thread::hardware_concurrency();

        auto threadTask = [&](auto&& func) {
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&] { return activeThreads < maxThreads; });
                ++activeThreads;
            }

            std::thread([&, func] {
                func();
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    --activeThreads;
                }
                cv.notify_one();
                }).detach();
            };

        for (int i = 0; i < 10000; ++i) {
            threadTask([this] { this->cheapOperate(std::chrono::microseconds(200)); });
        }

        for (int i = 0; i < 20; ++i) {
            threadTask([this] { this->expensiveOperate(std::chrono::seconds(2)); });
        }

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return activeThreads == 0; });
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Total cheap operate num:" << this->cheapOperateNum << std::endl;
        std::cout << "Total cheap time:" << this->totalCheapOperateTime.count() << "ms" << std::endl;
        std::cout << "Total expensive operate num:" << this->expensiveOperateNum << std::endl;
        std::cout << "Total expensive time:" << this->totalExpensiveOperateTime.count() << "s" << std::endl;
        std::cout << "Total time without thread pool:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

        SUCCEED();
    }

}

bool ThreadPoolTest::expensiveOperate(std::chrono::seconds time)
{
    std::this_thread::sleep_for(time);
    {
        std::lock_guard<std::mutex> lockNum(mtxExpensive);
        this->expensiveOperateNum++;
        totalExpensiveOperateTime += time;
        std::lock_guard<std::mutex> lock(mtxCout);
    }
    return true;
}

bool ThreadPoolTest::cheapOperate(std::chrono::microseconds time)
{
    std::this_thread::sleep_for(time);
    {
        std::lock_guard<std::mutex> lockNum(mtxCheap);
        this->totalCheapOperateTime += time;
        this->cheapOperateNum++;
        std::lock_guard<std::mutex> lock(mtxCout);
        
    }
    return true;
}

