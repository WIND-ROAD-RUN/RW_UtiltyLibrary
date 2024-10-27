#include"pch.h"

class OsoOrganizeStructureDataXmlStoreFormat {
private:
    ObjectStoreAssembly _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData;
    ObjectStoreItem _OsoOrganizeStructureDataXmlStoreFormatItemSampleData;
public:
    OsoOrganizeStructureDataXmlStoreFormat();
    ~OsoOrganizeStructureDataXmlStoreFormat() = default;
public:
    operator ObjectStoreAssembly() {
        return _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData;
    }

    operator ObjectStoreItem() {
        return _OsoOrganizeStructureDataXmlStoreFormatItemSampleData;
    }

    static string assemblyStandardString();
    static string itemStandardString();

};

static std::string removeNewlinesAndTabs(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) {
        return c == '\n' || c == '\t';
        }), result.end());
    return result;
}

namespace oso_OrganizeStructure {
    TEST(OrganizeStructure_pugixml_class, checkStringFormat_getStringAssembly) {
        OrganizeStructure_pugixml testObj;
        OsoOrganizeStructureDataXmlStoreFormat data;
        auto str = testObj.getString(std::make_shared<ObjectStoreAssembly>(data));
        str = removeNewlinesAndTabs(str);
        auto standardString = data.assemblyStandardString();

        EXPECT_EQ(str, standardString);
    }

    TEST(OrganizeStructure_pugixml_class, checkStringFormat_getStringItem) {
        OrganizeStructure_pugixml testObj;
        OsoOrganizeStructureDataXmlStoreFormat data;
        auto str = testObj.getString(std::make_shared<ObjectStoreItem>(data));
        str = removeNewlinesAndTabs(str);
        auto standardString = data.itemStandardString();

        EXPECT_EQ(str, standardString);
    }

    TEST(OrganizeStructure_pugixml_class, getStoreAssemblyFromString) {
        OrganizeStructure_pugixml testObj;
        OsoOrganizeStructureDataXmlStoreFormat data;
        auto target=testObj.getStoreAssemblyFromString(OsoOrganizeStructureDataXmlStoreFormat::assemblyStandardString());

        auto result = (*target) == ObjectStoreAssembly(data);
        EXPECT_EQ(result,true);
    }

    TEST(OrganizeStructure_pugixml_class, getStoreItemFromString) {
        OrganizeStructure_pugixml testObj;
        OsoOrganizeStructureDataXmlStoreFormat data;
        auto target = testObj.getStoreItemFromString(OsoOrganizeStructureDataXmlStoreFormat::itemStandardString());

        auto result = (*target) == ObjectStoreItem(data);
        EXPECT_EQ(result, true);
    }

    TEST(OrganizeStructure_pugixml_class, checkStringFormat_getAssemlyAndgetString) {
        OrganizeStructure_pugixml testObj;
        OsoOrganizeStructureDataXmlStoreFormat data;
        auto target = testObj.getStoreAssemblyFromString(OsoOrganizeStructureDataXmlStoreFormat::assemblyStandardString());
        auto str = testObj.getString(std::make_shared<ObjectStoreItem>(data));
        str = removeNewlinesAndTabs(str);
        auto standardString = data.itemStandardString();
        
        EXPECT_EQ(str, standardString);
    }

    TEST(OrganizeStructure_pugixml_class, checkStringFormat_getItemAndgetString) {
        OrganizeStructure_pugixml testObj;
        OsoOrganizeStructureDataXmlStoreFormat data;
        auto target = testObj.getStoreItemFromString(OsoOrganizeStructureDataXmlStoreFormat::itemStandardString());

        auto str = testObj.getString(std::make_shared<ObjectStoreItem>(data));
        str = removeNewlinesAndTabs(str);
        auto standardString = data.itemStandardString();

        EXPECT_EQ(str, standardString);
    }

}

OsoOrganizeStructureDataXmlStoreFormat::OsoOrganizeStructureDataXmlStoreFormat()
{
    _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData.setName("OcrDataXmlStoreFormatSampleData");

    ObjectStoreItem boolItem;
    boolItem.setName("bool");
    boolItem.setValueFromBool(false);
    _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData.addItem(std::make_shared<ObjectStoreItem>(boolItem));

    ObjectStoreItem doubleItem;
    doubleItem.setName("double");
    doubleItem.setValueFromDouble(1.1);
    _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData.addItem(std::make_shared<ObjectStoreItem>(doubleItem));

    ObjectStoreItem intItem;
    intItem.setName("int");
    intItem.setValueFromInt(1);
    _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData.addItem(std::make_shared<ObjectStoreItem>(intItem));

    ObjectStoreItem floatItem;
    floatItem.setName("float");
    floatItem.setValueFromFloat(1.1);
    _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData.addItem(std::make_shared<ObjectStoreItem>(floatItem));


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

    _OsoOrganizeStructureDataXmlStoreFormatAssemblySampleData.addItem(std::make_shared<ObjectStoreAssembly>(childAssembly));
    
    _OsoOrganizeStructureDataXmlStoreFormatItemSampleData.setName("OcrDataXmlStoreFormatSampleData");
    _OsoOrganizeStructureDataXmlStoreFormatItemSampleData.setValueFromString("test");

}

string OsoOrganizeStructureDataXmlStoreFormat::assemblyStandardString()
{
    string result;
    /*    */result.append(R"(<ObjectStoreAssembly name="OcrDataXmlStoreFormatSampleData">)");
    /*        */result.append(R"(<children>)");
    /*            */result.append(R"(<ObjectStoreItem name="bool">)");
    /*                 */result.append(R"(<value>false</value>)");
    /*                 */result.append(R"(<type>bool</type>)");
    /*            */result.append(R"(</ObjectStoreItem>)");
    /*            */result.append(R"(<ObjectStoreItem name="double">)");
    /*                */result.append(R"(<value>1.100000</value>)");
    /*                */result.append(R"(<type>double</type>)");
    /*            */result.append(R"(</ObjectStoreItem>)");
    /*            */result.append(R"(<ObjectStoreItem name="int">)");
    /*                */result.append(R"(<value>1</value>)");
    /*                */result.append(R"(<type>int</type>)");
    /*            */result.append(R"(</ObjectStoreItem>)");
    /*            */result.append(R"(<ObjectStoreItem name="float">)");
    /*               */result.append(R"(<value>1.100000</value>)");
    /*               */result.append(R"(<type>float</type>)");
    /*            */result.append(R"(</ObjectStoreItem>)");
    /*            */result.append(R"(<ObjectStoreAssembly name="childAssembly">)");
    /*              */result.append(R"(<children>)");
    /*                   */result.append(R"(<ObjectStoreItem name="long">)");
    /*                       */result.append(R"(<value>1</value>)");
    /*                       */result.append(R"(<type>long</type>)");
    /*                   */result.append(R"(</ObjectStoreItem>)");
    /*                   */result.append(R"(<ObjectStoreItem name="string">)");
    /*                       */result.append(R"(<value>string</value>)");
    /*                       */result.append(R"(<type>string</type>)");
    /*                   */result.append(R"(</ObjectStoreItem>)");
    /*              */result.append(R"(</children>)");
    /*            */result.append(R"(</ObjectStoreAssembly>)");
    /**/        result.append(R"(</children>)");
    /**/    result.append(R"(</ObjectStoreAssembly>)");



    return result;
}

string OsoOrganizeStructureDataXmlStoreFormat::itemStandardString()
{
    string result;
    /*    */result.append(R"(<ObjectStoreItem name="OcrDataXmlStoreFormatSampleData">)");
    /*        */result.append(R"(<value>test</value>)");
    /*        */result.append(R"(<type>string</type>)");
    /*    */result.append(R"(</ObjectStoreItem>)");

    return result;
}


