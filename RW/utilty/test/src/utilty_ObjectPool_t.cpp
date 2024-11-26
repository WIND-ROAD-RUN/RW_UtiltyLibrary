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
    std::array<double, 4 * 1024 *5>m_data;
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
    std::allocator<ExpensiveObject> allocator;
    MyPool pool(allocator);
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