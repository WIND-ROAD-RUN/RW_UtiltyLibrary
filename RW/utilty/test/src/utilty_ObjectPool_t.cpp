#include"utilty_ObjectPool_t.h"

#include"utilty_ObjectPool.h"
#include<chrono>
#include<array>

class ExpensiveObject
{
public:
    ExpensiveObject() {}
    virtual ~ExpensiveObject() = default;

private:
    std::array<double, 4 * 1024>m_data;
};

using MyPool = rw::ObjectPool<ExpensiveObject>;

std::shared_ptr<ExpensiveObject> getExpensiveObject(MyPool& pool)
{
    auto object{pool.acquireObject()};
    return object;
}

void processExpensiveObject(ExpensiveObject& object) {}

TEST(t, t) {
    const size_t NumberOfIteration{50000};
    std::cout << "Starting loop using pool.."<<std::endl;
    MyPool pool;
    auto start1{std::chrono::steady_clock::now()};
    for (size_t i{ 0 };i<NumberOfIteration;++i) {
        auto object{ getExpensiveObject(pool) };
        processExpensiveObject(*object.get());
    }
    auto end1{ std::chrono::steady_clock::now() };
    auto diff1{ end1 - start1 };
    std::cout << "done in " << std::chrono::duration<double, std::milli>(diff1).count() << " ms\n";
    std::cout << "Starting loop using new/delete.."<<std::endl;
    auto start2{ std::chrono::steady_clock::now() };
    for (size_t i{ 0 };i<NumberOfIteration;++i) {
        auto object{ std::make_shared<ExpensiveObject>() };
        processExpensiveObject(*object.get());
    }
    auto end2{ std::chrono::steady_clock::now() };
    auto diff2{ end2 - start2 };
    std::cout << "done in " << std::chrono::duration<double, std::milli>(diff2).count() << " ms\n";

}

class TestObject {
public:
    TestObject(int value) : value(value) {}
    int getValue() const { return value; }
private:
    int value;
};

TEST(ObjectPoolTest, AcquireObject) {
    rw::ObjectPool<TestObject> pool;
    auto obj = pool.acquireObject(42);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getValue(), 42);
}

TEST(ObjectPoolTest, AcquireMultipleObjects) {
    rw::ObjectPool<TestObject> pool;
    auto obj1 = pool.acquireObject(1);
    auto obj2 = pool.acquireObject(2);
    ASSERT_NE(obj1, nullptr);
    ASSERT_NE(obj2, nullptr);
    EXPECT_EQ(obj1->getValue(), 1);
    EXPECT_EQ(obj2->getValue(), 2);
    std::cout << pool.getTotalAllocatedMemory();
}

TEST(ObjectPoolTest, ReleaseObject) {
    rw::ObjectPool<TestObject> pool;
    auto obj = pool.acquireObject(42);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj.use_count(), 1);
    obj.reset();
    EXPECT_EQ(obj, nullptr);
    auto obj2 = pool.acquireObject(43);
    ASSERT_NE(obj2, nullptr);
    EXPECT_EQ(obj2->getValue(), 43);
}

TEST(ObjectPoolTest, Destructor) {
    rw::ObjectPool<TestObject>* pool = new rw::ObjectPool<TestObject>();
    auto obj = pool->acquireObject(42);
    ASSERT_NE(obj, nullptr);
    obj.reset();
    delete pool;
    // No explicit check here, just ensuring no crash on delete
}