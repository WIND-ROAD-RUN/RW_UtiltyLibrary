#include"oso_StorageStrategy_xml_t.hpp"

namespace oso_StorageStraegy_xml
{
    TEST(StorageStrategy_xml, test)
    {
        ObjectStoreAssembly sampleAssembly;
        sampleAssembly.setName("test");

        ObjectStoreItem item1;
        item1.setName("item1");
        item1.setValueFromInt(1);
        sampleAssembly.addItem(item1);

        ObjectStoreItem item2;
        item2.setName("item2");
        item2.setValueFromDouble(2.0);
        sampleAssembly.addItem(item2);

        ObjectStoreItem item3;
        item3.setName("item3");
        item3.setValueFromBool(true);
        sampleAssembly.addItem(item3);

        StorageStrategy_Xml testObj;
        testObj.save(sampleAssembly,R"(C:\Users\34615\Desktop\1\test.xml)");
    }

    TEST(StorageStrategy_xml, test2)
    {
        StorageStrategy_Xml testObj;
        auto result = testObj.load(R"(C:\Users\34615\Desktop\1\test.xml)");
        EXPECT_TRUE(result);
    }   
}
