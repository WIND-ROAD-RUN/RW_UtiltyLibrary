#include"dsl_pch_t.h"

#include"dsl_PriorityQueue_t.h"

namespace dsl_PriorityQueue
{

    /**
     * @brief Test the top method can throw exception when the heap is empty
     *
     * @details
     * Test Steps:
     * 1. Create a heap
     * 2. Call the top method
     * 3. Check if the exception is thrown
     *
     * Expected Result:
     * 1. The exception should be thrown
     * 2. The isException should be true
     *
     * Boundary Conditions:
     * 1. The heap is empty
     */
    TEST_F(DHeapTest, topCanTrow) {
        bool isException = false;
        try {
            testObj->top();
        }
        catch (std::runtime_error& e) {
            isException = true;
        }
        ASSERT_TRUE(isException);
    }

    /**
     * @brief Test the top method can get the value from the heap and delete it
     *
     * @details
     * Test Steps:
     * 1. Create a heap
     * 2. Insert some elements into the heap
     * 3. Call the top method
     * 4. Check if the value is correct
     *
     * Expected Result:
     * 1. The value should be correct
     *
     * Boundary Conditions:
     * 1. The heap is not empty
     */
    TEST_F(DHeapTest, topCanGetValueAndDeleteFromHeap) {
        auto isHighPriorityFirst = testObj->getIsHighPriorityFirst();
        testObj->insert(1, 1);
        testObj->insert(2, 2);
        testObj->insert(3, 3);
        testObj->insert(4, 4);
        testObj->insert(5, 5);
        if (isHighPriorityFirst)
        {
            ASSERT_EQ(testObj->top(), 5);
            ASSERT_EQ(testObj->top(), 4);
            ASSERT_EQ(testObj->top(), 3);
            ASSERT_EQ(testObj->top(), 2);
            ASSERT_EQ(testObj->top(), 1);
        }
        else
        {
            ASSERT_EQ(testObj->top(), 1);
            ASSERT_EQ(testObj->top(), 2);
            ASSERT_EQ(testObj->top(), 3);
            ASSERT_EQ(testObj->top(), 4);
            ASSERT_EQ(testObj->top(), 5);
        }

    }

    /**
     * @brief Test the peek method can throw exception when the heap is empty
     *
     * @details
     * Test Steps:
     * 1. Create a heap
     * 2. Call the peek method
     * 3. Check if the exception is thrown
     *
     * Expected Result:
     * 1. The exception should be thrown
     * 2. The isException should be true
     *
     * Boundary Conditions:
     * 1. The heap is empty
     */
    TEST_F(DHeapTest, peekCanTrow) {
        bool isException = false;
        try {
            testObj->peek();
        }
        catch (std::runtime_error& e) {
            isException = true;
        }
        ASSERT_TRUE(isException);
    }

    /**
     * @brief Test the peek method can get the value from the heap without deleting it
     *
     * @details
     * Test Steps:
     * 1. Create a heap
     * 2. Insert some elements into the heap
     * 3. Call the peek method
     * 4. Check if the value is correct
     *
     * Expected Result:
     * 1. The value should be correct
     *
     * Boundary Conditions:
     * 1. The heap is not empty
     */
    TEST_F(DHeapTest, peekCanGetValueWithoutDeleteFromHeap) {
        auto isHighPriorityFirst = testObj->getIsHighPriorityFirst();
        testObj->insert(1, 1);
        testObj->insert(2, 2);
        testObj->insert(3, 3);
        testObj->insert(4, 4);
        testObj->insert(5, 5);
        if (isHighPriorityFirst)
        {
            ASSERT_EQ(testObj->peek(), 5);
            ASSERT_EQ(testObj->peek(), 5);
        }
        else
        {
            ASSERT_EQ(testObj->peek(), 1);
            ASSERT_EQ(testObj->peek(), 1);
        }
    }

    /**
     * @brief Test the insert method can insert an element into the heap
     *
     * @details
     * Test Steps:
     * 1. Create a heap
     * 2. Insert some elements into the heap
     * 3. Check if the size is correct
     *
     * Expected Result:
     * 1. The size should be correct
     *
     * Boundary Conditions:
     * 1. The heap is empty
     */
    TEST_F(DHeapTest, insertCanInsertElement) {
        testObj->insert(1, 1);
        testObj->insert(2, 2);
        testObj->insert(3, 3);
        testObj->insert(4, 4);
        testObj->insert(5, 5);
        ASSERT_EQ(testObj->size(), 5);
    }

    /**
     * @brief Test the insert method can insert an element with the same priority into the heap
     *
     * @details
     * Test Steps:
     * 1. Create a heap
     * 2. Insert some elements with the same priority into the heap
     * 3. Check if the size is correct
     *
     * Expected Result:
     * 1. The size should be correct
     *
     * Boundary Conditions:
     * 1. The heap is empty
     */
    TEST_F(DHeapTest, insertCanInsertElementWithSamePriority) {
        testObj->insert(1, 1);
        testObj->insert(2, 1);
        testObj->insert(3, 1);
        testObj->insert(4, 1);
        testObj->insert(5, 1);
        ASSERT_EQ(testObj->size(), 5);
    }

    /**
     * @brief Test the insert method can insert an element with the same value into the heap
     *
     * @details
     * Test Steps:
     * 1. Create a heap
     * 2. Insert some elements with the same value into the heap
     * 3. Check if the size is correct
     *
     * Expected Result:
     * 1. The size should be correct
     *
     * Boundary Conditions:
     * 1. The heap insert element 's value is the same as the existing element
     */
    TEST_F(DHeapTest, insertCanInsertElementWithSameValue) {
        testObj->insert(1, 1);
        testObj->insert(1, 2);
        testObj->insert(1, 3);
        testObj->insert(1, 4);
        testObj->insert(1, 5);
        ASSERT_EQ(testObj->size(), 5);
    }

    TEST_F(DHeapTest, removeCanRemoveTheElementsWhichIsNotExisting) {
        testObj->insert(1, 1);
        testObj->insert(2, 2);
        testObj->insert(3, 3);
        testObj->insert(4, 4);
        testObj->insert(5, 5);
        testObj->remove(6);
        ASSERT_EQ(testObj->size(), 5);
    }
}
