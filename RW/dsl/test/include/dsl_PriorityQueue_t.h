#include"dsl_pch_t.h"

#include"dsl_PriorityQueue.h"

using namespace rw::dsl;
class DHeapTest
    : public ::testing::Test {
protected:
    void SetUp() override {
        int d = generateRandomNumber(2, 20);
        int isHighPriorityFirst = generateRandomNumber(0, 1);
        testObj = new DHeap(d, isHighPriorityFirst);
    }

    void TearDown() override {
        delete testObj;
    }
private:
    int generateRandomNumber(int min, int max) {
        std::random_device rd; // 用于生成种子
        std::mt19937 gen(rd()); // Mersenne Twister 19937 生成器
        std::uniform_int_distribution<> dis(min, max); // 均匀分布
        return dis(gen);
    }
public:
    DHeap* testObj{nullptr};
};