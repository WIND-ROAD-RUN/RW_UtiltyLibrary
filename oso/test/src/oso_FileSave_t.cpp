#include"pch.h"

#include"oso_FileSave_t.h"

namespace oso_FileSave { 
    TEST_P(FileSaveTest, save_fileName_assemblyPtr) {
        auto & [type] = GetParam();
        initestObj(type);
        auto result = _testObj->save(_testFileName, _sampleAssembly);
        EXPECT_TRUE(result);
    }

    TEST_P(FileSaveTest, load_fileName) {
        auto& [type] = GetParam();
        initestObj(type);
        auto saveResult = _testObj->save(_testFileName, _sampleAssembly);
        ASSERT_EQ(saveResult, true);

        auto loadResult = _testObj->load(_testFileName);
        ASSERT_TRUE(loadResult);

        ASSERT_EQ(*loadResult, *_sampleAssembly);
    }
}