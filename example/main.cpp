
#include <stack>
#include <unordered_set>
#include <stdexcept>

template <typename T>
class ObjectPool {
public:
    T* GetObject() {
        if (!_availableObjects.empty()) {
            T* obj = _availableObjects.top();
            _availableObjects.pop();
            _inUseObjects.insert(obj);
            return obj;
        }
        else {
            T* newObj = new T();
            _inUseObjects.insert(newObj);
            return newObj;
        }
    }

    void ReleaseObject(T* obj) {
        auto it = _inUseObjects.find(obj);
        if (it != _inUseObjects.end()) {
            _inUseObjects.erase(it);
            _availableObjects.push(obj);
        }
        else {
            throw std::invalid_argument("The object being released was not acquired from this pool.");
        }
    }

    ~ObjectPool() {
        while (!_availableObjects.empty()) {
            delete _availableObjects.top();
            _availableObjects.pop();
        }
        for (auto obj : _inUseObjects) {
            delete obj;
        }
    }

private:
    std::stack<T*> _availableObjects;
    std::unordered_set<T*> _inUseObjects;
};

class MyClass {
public:
    MyClass() {
        // Constructor logic
    }

    void Reset() {
        // Reset object state
    }
};

#include <iostream>


int main() {
    ObjectPool<MyClass> pool;

    // 获取对象
    MyClass* obj1 = pool.GetObject();
    MyClass* obj2 = pool.GetObject();

    // 使用对象
    // ...

    // 重置对象状态
    obj1->Reset();
    obj2->Reset();

    // 释放对象
    pool.ReleaseObject(obj1);
    pool.ReleaseObject(obj2);

    return 0;
}