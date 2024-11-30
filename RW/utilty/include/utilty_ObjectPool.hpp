#pragma once

#include <memory>
#include <vector>
#include <numeric>
#include<cassert>
#include <mutex>
#include<iostream>

namespace rw {
    const bool ThreadSafe = true;
    const bool NotThreadSafe = false;



    /**
     * @brief: template class ObjectPool
     *      This class is a template class that implements an object pool.
     * @template variable:
     *   - T: The type of the objects that the pool will manage.
     *   - Allocator: The type of the allocator that will be used to allocate memory for the objects.
     *   - isThreadSafe: A boolean value that indicates whether the object pool should be thread-safe.
     *
     * @details:
     *
     */
    template<typename T, typename Allocator = std::allocator<T>, bool isThreadSafe = NotThreadSafe>
    class ObjectPool;

    template<typename T,typename Allocator>
    class ObjectPool<T, Allocator, NotThreadSafe> final {
    public:
        ObjectPool() = default;
        explicit ObjectPool(const Allocator& allocator);
        ~ObjectPool();

        ObjectPool(ObjectPool&&) = delete;
        ObjectPool& operator=(ObjectPool&&) = delete;

        ObjectPool(const ObjectPool&) = delete;
        ObjectPool& operator=(const ObjectPool&) = delete;

        template<typename... Args>
        std::shared_ptr<T> acquireObject(Args && ... args);

        std::size_t getTotalAllocatedMemory() const;
    private:
        void addChunk();
        std::vector<T*> m_pool;

        std::vector<T*> m_freeObjects;

        static constexpr std::size_t ms_initialChunkSize{ 5 };

        std::size_t m_newChunkSize{ ms_initialChunkSize };

        Allocator m_allocator;

    };

    template<typename T, typename Allocator>
    class ObjectPool<T, Allocator, ThreadSafe> final {
    public:
        ObjectPool() = default;
        explicit ObjectPool(const Allocator& allocator);
        ~ObjectPool();

        ObjectPool(ObjectPool&&) = delete;
        ObjectPool& operator=(ObjectPool&&) = delete;

        ObjectPool(const ObjectPool&) = delete;
        ObjectPool& operator=(const ObjectPool&) = delete;

        template<typename... Args>
        std::shared_ptr<T> acquireObject(Args&& ... args);

        std::size_t getTotalAllocatedMemory() const;
    private:
        void addChunk();
        std::vector<T*> m_pool;
        std::vector<T*> m_freeObjects;
        static constexpr std::size_t ms_initialChunkSize{ 5 };
        std::size_t m_newChunkSize{ ms_initialChunkSize };
        Allocator m_allocator;
        mutable std::mutex m_mutex; // 互斥锁
    };

    template<typename T,typename Allocator>
    ObjectPool<T, Allocator, NotThreadSafe>::ObjectPool(const Allocator & allocator)
        :m_allocator{ allocator }
    {
        
    }

    template<typename T, typename Allocator>
    void ObjectPool<T, Allocator, NotThreadSafe>::addChunk()
    {
        std::cout << "Allocating new chunk...";
        m_pool.push_back(nullptr);
        try
        {
            m_pool.back() = m_allocator.allocate(m_newChunkSize);
        }
        catch (const std::exception&)
        {
            m_pool.pop_back();
            throw;
        }

        auto oldFreeObjectsSize{m_freeObjects.size()};
        m_freeObjects.resize(oldFreeObjectsSize+m_newChunkSize);
        std::iota(std::begin(m_freeObjects) + oldFreeObjectsSize, std::end(m_freeObjects), m_pool.back());
        m_newChunkSize *= 2;
    
    }

    template<typename T, typename Allocator>
    template<typename... Args>
    std::shared_ptr<T> ObjectPool<T, Allocator, NotThreadSafe>::acquireObject(Args && ... args)
    {
        if (m_freeObjects.empty()) {
            addChunk();
        }

        T* object{ m_freeObjects.back() };

        object=new T(std::forward<Args>(args)...);

        T* constructedObject{ std::launder(object)};
        m_freeObjects.pop_back();

        return std::shared_ptr<T>{constructedObject, [this](T* object) {
            std::destroy_at(object);
            m_freeObjects.push_back(object);
            }
        };
    }

    template<typename T, typename Allocator>
    ObjectPool<T, Allocator, NotThreadSafe>::~ObjectPool()
    {
        assert(m_freeObjects.size() == ms_initialChunkSize * (std::pow(2, m_pool.size()) - 1));
        std::size_t chunkSize{ ms_initialChunkSize };
        for (auto * chunk :m_pool) {
            m_allocator.deallocate(chunk, chunkSize);
            chunkSize *= 2;
        }
        m_pool.clear();
    }

    template<typename T, typename Allocator>
    std::size_t ObjectPool<T, Allocator, NotThreadSafe>::getTotalAllocatedMemory() const
    {
        std::size_t totalMemory = 0;
        std::size_t chunkSize = ms_initialChunkSize;
        for (const auto* chunk : m_pool) {
            totalMemory += chunkSize * sizeof(T);
            chunkSize *= 2;
        }
        return totalMemory;
    }


    template<typename T, typename Allocator>
    ObjectPool<T, Allocator, ThreadSafe>::ObjectPool(const Allocator& allocator)
        : m_allocator{ allocator }
    {
    }

    template<typename T, typename Allocator>
    void ObjectPool<T, Allocator, ThreadSafe>::addChunk()
    {
        std::cout << "Allocating new chunk...";
        m_pool.push_back(nullptr);
        try
        {
            m_pool.back() = m_allocator.allocate(m_newChunkSize);
        }
        catch (const std::exception&)
        {
            m_pool.pop_back();
            throw;
        }

        auto oldFreeObjectsSize{ m_freeObjects.size() };
        m_freeObjects.resize(oldFreeObjectsSize + m_newChunkSize);
        std::iota(std::begin(m_freeObjects) + oldFreeObjectsSize, std::end(m_freeObjects), m_pool.back());
        m_newChunkSize *= 2;
    }

    template<typename T, typename Allocator>
    template<typename... Args>
    std::shared_ptr<T> ObjectPool<T, Allocator, ThreadSafe>::acquireObject(Args&& ... args)
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        if (m_freeObjects.empty()) {
            addChunk();
        }

        T* object{ m_freeObjects.back() };
        object = new T(std::forward<Args>(args)...);
        T* constructedObject{ std::launder(object) };
        m_freeObjects.pop_back();

        return std::shared_ptr<T>{constructedObject, [this](T* object) {
            std::lock_guard<std::mutex> lock(m_mutex); // 加锁
            std::destroy_at(object);
            m_freeObjects.push_back(object);
            }
        };
    }

    template<typename T, typename Allocator>
    ObjectPool<T, Allocator, ThreadSafe>::~ObjectPool()
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        assert(m_freeObjects.size() == ms_initialChunkSize * (std::pow(2, m_pool.size()) - 1));
        std::size_t chunkSize{ ms_initialChunkSize };
        for (auto* chunk : m_pool) {
            m_allocator.deallocate(chunk, chunkSize);
            chunkSize *= 2;
        }
        m_pool.clear();
    }

    template<typename T, typename Allocator>
    std::size_t ObjectPool<T, Allocator, ThreadSafe>::getTotalAllocatedMemory() const
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        std::size_t totalMemory = 0;
        std::size_t chunkSize = ms_initialChunkSize;
        for (const auto* chunk : m_pool) {
            totalMemory += chunkSize * sizeof(T);
            chunkSize *= 2;
        }
        return totalMemory;
    }
}

