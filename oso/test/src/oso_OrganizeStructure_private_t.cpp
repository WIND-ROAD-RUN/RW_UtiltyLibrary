#include"pch.h"

#include"oso_OrganizeStructure_private_t.h"

namespace oso_OrganizeStructure {
    TEST_F(OrganizeStructure_pugixmlTest, checkStringFormat_getStringAssembly) {
        auto str = testObj.getString(std::make_shared<ObjectStoreAssembly>(_OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData));
        str = removeNewlinesAndTabs(str);
        auto standardString = _assemblyStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_F(OrganizeStructure_pugixmlTest, checkStringFormat_getStringItem) {
        auto str = testObj.getString(std::make_shared<ObjectStoreItem>(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData));
        str = removeNewlinesAndTabs(str);
        auto standardString = _itemStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_F(OrganizeStructure_pugixmlTest, getStoreAssemblyFromString) {
        auto target = testObj.getStoreAssemblyFromString(_assemblyStandardString);

        auto result = (*target) == ObjectStoreAssembly(_OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData);
        EXPECT_EQ(result, true);
    }

    TEST_F(OrganizeStructure_pugixmlTest, getStoreItemFromString) {
        auto target = testObj.getStoreItemFromString(_itemStandardString);

        auto result = (*target) == ObjectStoreItem(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData);
        EXPECT_EQ(result, true);
    }

    TEST_F(OrganizeStructure_pugixmlTest, checkStringFormat_getAssemlyAndgetString) {
        auto target = testObj.getStoreAssemblyFromString(_assemblyStandardString);
        auto str = testObj.getString(std::make_shared<ObjectStoreItem>(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData));
        str = removeNewlinesAndTabs(str);
        auto standardString = _itemStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_F(OrganizeStructure_pugixmlTest, checkStringFormat_getItemAndgetString) {
        auto target = testObj.getStoreItemFromString(_itemStandardString);

        auto str = testObj.getString(std::make_shared<ObjectStoreItem>(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData));
        str = removeNewlinesAndTabs(str);
        auto standardString = _itemStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_F(OrganizeStructure_pugixmlTest, xmlCore_getStringAssembly) {
        auto str = testObj.getString(std::make_shared<ObjectStoreAssembly>(_OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData));
        str = removeNewlinesAndTabs(str);
        auto standardString = _assemblyStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_F(OrganizeStructure_pugixmlTest, xmlCore_getStringItem) {
        auto str = testObj.getString(std::make_shared<ObjectStoreItem>(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData));
        str = removeNewlinesAndTabs(str);
        auto standardString = _itemStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_F(OrganizeStructure_pugixmlTest, xmlCore_getStoreAssemblyFromString) {
        auto target = testObj.getStoreAssemblyFromString(_assemblyStandardString);

        auto result = (*target) == ObjectStoreAssembly(_OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData);
        EXPECT_EQ(result, true);
    }

    TEST_F(OrganizeStructure_pugixmlTest, xmlCore_getStoreItemFromString) {
        auto target = testObj.getStoreItemFromString(_itemStandardString);

        auto result = (*target) == ObjectStoreItem(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData);
        EXPECT_EQ(result, true);
    }

}




