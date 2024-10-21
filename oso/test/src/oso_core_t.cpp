#include"pch.h"
#include <random> 

namespace oso_core{
    TEST(ObjectStoreCore_Class, attribute_name) {
        ObjectStoreCore testObj;

        string name = "testName";
        string errorname = "errorName";

        testObj.setName(name);
        EXPECT_EQ(testObj.getName(), name);

        EXPECT_NE(testObj.getName(), errorname);
    }

    TEST(ObjectStoreCore_Class, attribute_level) {
        ObjectStoreCore testObj;
        
        auto currentLevel = testObj.level;

        //Check if the initial value is 0
        ASSERT_EQ(testObj.level, 0);

        //Check if the level should never be a positive value
        testObj.subLevel();
        ASSERT_EQ(testObj.level, 0)<<"level应不为负值";

        testObj.addLevel();
        EXPECT_EQ(testObj.level, currentLevel+1);

        testObj.subLevel();
        EXPECT_EQ(testObj.level, currentLevel);

        //Randomly add specified levels
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 100);
        int random_number = dis(gen);

        for (int i = 0; i < random_number; ++i) {
            testObj.addLevel();
        }

        EXPECT_EQ(testObj.level, random_number + currentLevel);
    }

    TEST(ObjectStoreCore_Class, attribute_storeType) {
        ObjectStoreCore testObj;

        string storeType = "core";
        string errorStoreType = "error";

        EXPECT_EQ(testObj.getStoreType(), storeType);
        EXPECT_NE(testObj.getStoreType(), errorStoreType);
    }

    TEST(ObjectStoreItem_Class, attribute_storeType) {
        ObjectStoreItem testObj;
        EXPECT_EQ(testObj.getStoreType(), "item");
    }

    TEST(ObjectStoreItem_Class, operate_setValueFromString) {
        ObjectStoreItem testObj;
        
        string value = "string";
        string errorValue = "error";

        testObj.setValueFromString(value);
        EXPECT_EQ(testObj.getValueAsString(), value);
        EXPECT_EQ(testObj.getType(), ObjectDataItemStoreType::item_string);
    }

    TEST(ObjectStoreItem_Class, operate_setValueFromint) {
        ObjectStoreItem testObj;

        int value = 12;
        int errorValue = 0;

        testObj.setValueFromInt(value);
        EXPECT_EQ(testObj.getValueAsInt(), value);
        EXPECT_EQ(testObj.getType(), ObjectDataItemStoreType::item_int);
    }

    TEST(ObjectStoreItem_Class, operate_setValueFromLong) {
        ObjectStoreItem testObj;

        long value = 12;
        long errorValue = 0;

        testObj.setValueFromLong(value);
        EXPECT_EQ(testObj.getValueAsLong(), value);
        EXPECT_EQ(testObj.getType(), ObjectDataItemStoreType::item_long);
    }

    TEST(ObjectStoreItem_Class, operate_setValueFromFloat) {
        ObjectStoreItem testObj;

        float value = 12.0;
        float errorValue = 0.0;

        testObj.setValueFromFloat(value);
        EXPECT_EQ(testObj.getValueAsFloat(), value);
        EXPECT_EQ(testObj.getType(), ObjectDataItemStoreType::item_float);
    }

    TEST(ObjectStoreItem_Class, operate_setValueFromDouble) {
        ObjectStoreItem testObj;

        double value = 12.0;
        double errorValue = 0.0;

        testObj.setValueFromDouble(value);
        EXPECT_EQ(testObj.getValueAsDouble(), value);
        EXPECT_EQ(testObj.getType(), ObjectDataItemStoreType::item_double);
    }

    TEST(ObjectStoreItem_Class, operate_setValueFromBool) {
        ObjectStoreItem testObj;

        bool value = true;
        bool errorValue = false;

        testObj.setValueFromBool(value);
        EXPECT_EQ(testObj.getValueAsBool(), value);
        EXPECT_EQ(testObj.getType(), ObjectDataItemStoreType::item_bool);
    }
}
