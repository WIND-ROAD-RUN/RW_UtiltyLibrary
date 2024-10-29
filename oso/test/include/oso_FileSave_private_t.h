#ifndef OSO_FILESAVE_PRIVATE_T_H_
#define OSO_FILESAVE_PRIVATE_T_H_

#include"pch.h"

#include <filesystem>

class FileSave_pugixmlTest
    : public ::testing::Test {
protected:
    void SetUp() override {
        testObj = std::make_shared<FileSave_pugixml>(OrganizeStructureType::XML_pugixml);
        testFileName = std::filesystem::current_path() / "test.xml";

        sampleAssembly = std::make_shared<ObjectStoreAssembly>();

        sampleAssembly->setName("OcrDataXmlStoreFormatSampleData");

        ObjectStoreItem boolItem;
        boolItem.setName("bool");
        boolItem.setValueFromBool(false);
        sampleAssembly->addItem(std::make_shared<ObjectStoreItem>(boolItem));

        ObjectStoreItem doubleItem;
        doubleItem.setName("double");
        doubleItem.setValueFromDouble(1.1);
        sampleAssembly->addItem(std::make_shared<ObjectStoreItem>(doubleItem));

        ObjectStoreItem intItem;
        intItem.setName("int");
        intItem.setValueFromInt(1);
        sampleAssembly->addItem(std::make_shared<ObjectStoreItem>(intItem));

        ObjectStoreItem floatItem;
        floatItem.setName("float");
        floatItem.setValueFromFloat(1.1);
        sampleAssembly->addItem(std::make_shared<ObjectStoreItem>(floatItem));


        ObjectStoreAssembly childAssembly;
        childAssembly.setName("childAssembly");
        ObjectStoreItem longItem;
        longItem.setName("long");
        longItem.setValueFromLong(1);
        childAssembly.addItem(std::make_shared<ObjectStoreItem>(longItem));

        ObjectStoreItem stringItem;
        stringItem.setName("string");
        stringItem.setValueFromString("string");
        childAssembly.addItem(std::make_shared<ObjectStoreItem>(stringItem));

        sampleAssembly->addItem(std::make_shared<ObjectStoreAssembly>(childAssembly));
    }

    void TearDown() override {
        if (std::filesystem::exists(testFileName)) {
            std::filesystem::remove(testFileName);
        }
    }

protected:
    std::shared_ptr<FileSave_pugixml>  testObj;
    std::filesystem::path testFileName;
    std::shared_ptr<ObjectStoreAssembly> sampleAssembly;
};

#endif // !OSO_FILESAVE_PRIVATE_T_H_
