#include"gtest/gtest.h"

#include"dsl_BloomFilter.h"

#include <iostream>
#include <string>
#include <random>

using namespace rw::dsl;

std::string generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
}

TEST(DSL, BLOOMFILTER_REFACTOR) {
    // 随机生成最大错误率和预估的存储数量
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> errorRateDist(0.01, 0.1); // 错误率在0.01到0.1之间
    std::uniform_int_distribution<> storageSizeDist(10, 1000); // 预估存储数量在10到1000之间

    double maxTolerance = errorRateDist(generator);
    size_t estimatedStorageSize = storageSizeDist(generator);

    // 创建BloomFilterRefactor实例
    BloomFilter bf(estimatedStorageSize, maxTolerance);

    // 随机生成存储的key
    size_t numKeys = estimatedStorageSize;
    std::vector<std::string> keys;
    for (size_t i = 0; i < numKeys; ++i) {
        keys.push_back(generateRandomString(10)); // 生成长度为10的随机字符串
    }

    // 插入key到BloomFilter中
    for (const auto& key : keys) {
        bf.insert(key);
    }

    // 检查错误率
    size_t falsePositives = 0;
    size_t numChecks = 1000; // 检查1000个随机字符串
    for (size_t i = 0; i < numChecks; ++i) {
        std::string randomKey = generateRandomString(10);
        if (std::find(keys.begin(), keys.end(), randomKey) == keys.end() && bf.contains(randomKey)) {
            ++falsePositives;
        }
    }

    double actualErrorRate = static_cast<double>(falsePositives) / numChecks;
    double errorDifference = actualErrorRate - maxTolerance;
    std::cout << "Max Tolerance: " << maxTolerance << ", Actual Error Rate: " << actualErrorRate << ", Error Difference: " << errorDifference << std::endl;

    // 断言实际错误率不大于最大错误率，并在失败时输出相关信息
    ASSERT_LE(actualErrorRate, maxTolerance+0.035) << "Actual Error Rate: " << actualErrorRate << ", Max Tolerance: " << maxTolerance << ", Error Difference: " << errorDifference;
}

//该测试用例用于迭代算出BloomFilterRefactor的假阳性率的误差范围(也即给定输入假阳性率0.1,实际可能在0.1上下浮动)
//迭代测试1000次，每次测试1000次，如果1000次测试都通过则认为该假阳性率是可接受的
//如果1000次测试有一次不通过，则增加假阳性率0.001，继续测试
//最终结果应该在0.01~0.035之间
//为提高测试效率，当前adaptiveCount设为1，为测试此测试用例时，请可设置adaptiveCount，参考结果为0.035时adaptiveCount取值为1000
TEST(DSL, BLOOMFILTER_REFACTOR_AdaptiveTEST) {
    int adaptiveCount{ 1 };
    bool result{ false };
    double ErrorRate{ 0.01 };
    int testCount{ 0 };
    
    while (!result) {
        std::cout << "Test Index: " << testCount;
        std::cout << " Current ErrorRate: " << ErrorRate <<std::endl;
        int passcount=0;
        for (int i = 0;i<adaptiveCount;i++) {
            std::cout << "------Adaptive Test Index: " << i;
            // 随机生成最大错误率和预估的存储数量
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_real_distribution<> errorRateDist(0.01, 0.1); // 错误率在0.01到0.1之间
            std::uniform_int_distribution<> storageSizeDist(10, 1000); // 预估存储数量在10到1000之间

            double maxTolerance = errorRateDist(generator);
            size_t estimatedStorageSize = storageSizeDist(generator);

            // 创建BloomFilterRefactor实例
            BloomFilter bf(estimatedStorageSize, maxTolerance);

            // 随机生成存储的key
            size_t numKeys = estimatedStorageSize;
            std::vector<std::string> keys;
            for (size_t i = 0; i < numKeys; ++i) {
                keys.push_back(generateRandomString(10)); // 生成长度为10的随机字符串
            }

            // 插入key到BloomFilter中
            for (const auto& key : keys) {
                bf.insert(key);
            }

            // 检查错误率
            size_t falsePositives = 0;
            size_t numChecks = 1000; // 检查1000个随机字符串
            for (size_t i = 0; i < numChecks; ++i) {
                std::string randomKey = generateRandomString(10);
                if (std::find(keys.begin(), keys.end(), randomKey) == keys.end() && bf.contains(randomKey)) {
                    ++falsePositives;
                }
            }

            double actualErrorRate = static_cast<double>(falsePositives) / numChecks;
            double errorDifference = actualErrorRate - maxTolerance;

            std::cout << "Max Tolerance: " << maxTolerance << ", Actual Error Rate: " << actualErrorRate << ", Error Difference: " << errorDifference << std::endl;
           
            if (actualErrorRate <= maxTolerance) {
                passcount++;
            }
            else {
                if (errorDifference < ErrorRate) {
                    passcount++;
                }
                else {
                    break;
                }
            }
        }

        if (passcount == adaptiveCount) {
            result = true;
        }
        else {
            ErrorRate += 0.001;
        }
        
        testCount++;
    }

    std::cout << "Result ErrorRate " << ErrorRate << std::endl;

    ASSERT_LE(ErrorRate, 0.04);
}