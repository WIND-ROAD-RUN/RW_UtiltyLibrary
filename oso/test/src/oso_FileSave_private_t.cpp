#include"oso_FileSave_private_t.h"

namespace oso_FileSave {
    TEST_F(FileSave_pugixmlTest, save_fileName_assemblyPtr) {
        auto result = testObj->save(testFileName, sampleAssembly);
        EXPECT_TRUE(result);
    }

    TEST_F(FileSave_pugixmlTest, load_fileName) {
        auto saveResult = testObj->save(testFileName, sampleAssembly);
        ASSERT_EQ(saveResult, true);

        auto loadResult = testObj->load(testFileName);
        ASSERT_TRUE(loadResult);

        ASSERT_EQ(*loadResult, *sampleAssembly);
    }

}

