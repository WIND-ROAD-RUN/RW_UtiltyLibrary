#include"pch.h"

#include"oso_OrganizeStructure_t.h"

namespace oso_OrganizeStructure {
    TEST_P(OrganizeStructureTest, checkStringFormat_getStringAssembly) {
        auto& [type] = GetParam();
        initestObj(type);

        auto str = _testObj->getString(std::make_shared<ObjectStoreAssembly>(_OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData));
        str = removeNewlinesAndTabs(str);
        auto & standardString = _assemblyStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_P(OrganizeStructureTest, checkStringFormat_getStringItem) {
        auto& [type] = GetParam();
        initestObj(type);

        auto str = _testObj->getString(std::make_shared<ObjectStoreItem>(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData));
        str = removeNewlinesAndTabs(str);
        auto& standardString = _itemStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_P(OrganizeStructureTest, getStoreAssemblyFromString) {
        auto& [type] = GetParam();
        initestObj(type);

        auto target = _testObj->getStoreAssemblyPtrFromString(_assemblyStandardString);

        auto result = (*target) == ObjectStoreAssembly(_OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData);
        EXPECT_EQ(result, true);
    }

    TEST_P(OrganizeStructureTest, getStoreItemFromString) {
        auto& [type] = GetParam();
        initestObj(type);

        auto target = _testObj->getStoreItemPtrFromString(_itemStandardString);

        auto result = (*target) == ObjectStoreItem(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData);
        EXPECT_EQ(result, true);
    }

    TEST_P(OrganizeStructureTest, checkStringFormat_getAssemlyAndgetString) {
        auto& [type] = GetParam();
        initestObj(type);

        auto target = _testObj->getStoreAssemblyPtrFromString(_assemblyStandardString);
        auto str = _testObj->getString(std::make_shared<ObjectStoreItem>(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData));
        str = removeNewlinesAndTabs(str);
        auto& standardString = _itemStandardString;

        EXPECT_EQ(str, standardString);
    }

    TEST_P(OrganizeStructureTest, checkStringFormat_getItemAndgetString) {
        auto& [type] = GetParam();
        initestObj(type);

        auto target = _testObj->getStoreItemPtrFromString(_itemStandardString);

        auto str = _testObj->getString(std::make_shared<ObjectStoreItem>(_OsoOrganizeStructureDataXmlStoreFormatItemSampleData));
        str = removeNewlinesAndTabs(str);
        auto& standardString = _itemStandardString;

        EXPECT_EQ(str, standardString);
    }




}