#ifndef UTILTY_OBJECTPOOL_H_
#define UTILTY_OBJECTPOOL_H_

#include <memory>
#include <vector>
#include <numeric>
#include<cassert>

#include<iostream>

namespace rw {

    template<typename T,typename Allocator=std::allocator<T>>
    class ObjectPool final {
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

    private:
        void addChunk();
        std::vector<T*> m_pool;

        std::vector<T*> m_freeObjects;

        static constexpr std::size_t ms_initialChunkSize{ 5 };

        std::size_t m_newChunkSize{ ms_initialChunkSize };

        Allocator m_allocator;

    };

    template<typename T,typename Allocator>
    ObjectPool<T,Allocator>::ObjectPool(const Allocator & allocator)
        :m_allocator{ allocator }
    {
        
    }

    template<typename T, typename Allocator>
    void ObjectPool<T, Allocator>::addChunk()
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
    std::shared_ptr<T> ObjectPool<T, Allocator>::acquireObject(Args && ... args)
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
            }};
    }

    template<typename T, typename Allocator>
    ObjectPool<T, Allocator>::~ObjectPool()
    {
        assert(m_freeObjects.size() == ms_initialChunkSize * (std::pow(2, m_pool.size()) - 1));
        std::size_t chunkSize{ ms_initialChunkSize };
        for (auto * chunk :m_pool) {
            m_allocator.deallocate(chunk, chunkSize);
            chunkSize *= 2;
        }
        m_pool.clear();
    }

}

#endif // !UTILTY_OBJECTPOOL_H_
