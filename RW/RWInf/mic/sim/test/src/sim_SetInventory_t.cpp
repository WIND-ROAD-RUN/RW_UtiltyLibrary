#include"sim_SetInventory_t.hpp"

namespace sim_SetInventory
{
    TEST(SetInventory_Struct,fieldName)
    {
        SetInventory inventory;
        EXPECT_EQ(inventory.name, "Undefined");

        inventory.name = "Test";
        EXPECT_EQ(inventory.name, "Test");

        inventory.name = "Test2";
        EXPECT_EQ(inventory.name, "Test2");
    }

    TEST(SetInventory_Struct,fieldGuid)
    {
        SetInventory inventory;
        EXPECT_EQ(inventory.guid, "Undefined");
        inventory.guid = "Test";
        EXPECT_EQ(inventory.guid, "Test");
        inventory.guid = "Test2";
        EXPECT_EQ(inventory.guid, "Test2");
    }

    TEST(SetInventory_Struct, ConstructorDefault)
    {
        SetInventory testObj;
        EXPECT_EQ(testObj.name, "Undefined");
        EXPECT_EQ(testObj.guid, "Undefined");
        EXPECT_EQ(testObj.getSetList().size(), 0);
    }

    TEST(SetInventory_Struct, ConstructorByAssembly)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventory$");
        rw::oso::ObjectStoreItem nameItem;
        nameItem.setName("$Field$Name$");
        nameItem.setValueFromString("Test");
        assembly.addItem(nameItem);
        rw::oso::ObjectStoreItem guidItem;
        guidItem.setName("$Field$Guid$");
        guidItem.setValueFromString("Test2");
        assembly.addItem(guidItem);
        try
        {
            SetInventory testObj(assembly);
            EXPECT_EQ(testObj.name, "Test");
            EXPECT_EQ(testObj.guid, "Test2");
            EXPECT_EQ(testObj.getSetList().size(), 0);
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << e.what();
        }
    }

    TEST(SetInventory_Struct, ConstructorByAssemblyMove)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventory$");
        rw::oso::ObjectStoreItem nameItem;
        nameItem.setName("$Field$Name$");
        nameItem.setValueFromString("Test");
        assembly.addItem(nameItem);
        rw::oso::ObjectStoreItem guidItem;
        guidItem.setName("$Field$Guid$");
        guidItem.setValueFromString("Test2");
        assembly.addItem(guidItem);
        SetInventory testObj(std::move(assembly));
        EXPECT_EQ(testObj.name, "Test");
        EXPECT_EQ(testObj.guid, "Test2");
        EXPECT_EQ(testObj.getSetList().size(), 0);
    }

    TEST(SetInventory_Struct, ConstructorByCopy)
    {
        SetInventory testObj;
        testObj.name = "Test";
        testObj.guid = "Test2";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);

        SetInventory testObj2(testObj);
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.guid, "Test2");
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventory_Struct, ConstructorByMove)
    {
        SetInventory testObj;
        testObj.name = "Test";
        testObj.guid = "Test2";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        SetInventory testObj2(std::move(testObj));
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.guid, "Test2");
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventory_Struct, OperatorMove)
    {
        SetInventory testObj;
        testObj.name = "Test";
        testObj.guid = "Test2";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        SetInventory testObj2;
        testObj2 = std::move(testObj);
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.guid, "Test2");
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventory_Struct, OperatorAssign)
    {
        SetInventory testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);

        SetInventory testObj2;
        testObj2 = testObj;
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventory_Struct, OperatorEqual)
    {
        SetInventory testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);

        SetInventory testObj2;
        testObj2.name = "Test";
        SetInventoryItem item2;
        item2.name = "TestItem";
        item2.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj2.appendSetItem(item2);

        EXPECT_TRUE(testObj == testObj2);
    }

    TEST(SetInventory_Struct, OperatorNotEqual)
    {
        SetInventory testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);

        SetInventory testObj2;
        testObj2.name = "Test";
        SetInventoryItem item2;
        item2.name = "TestItem1";
        item2.setValue<std::string, ItemStoreType::Item_String>("test2");
        testObj2.appendSetItem(item2);
        EXPECT_TRUE(testObj != testObj2);

        SetInventory testObj3;
        testObj3.name = "Test2";
        SetInventoryItem item3;
        item3.name = "TestItem";
        item3.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj3.appendSetItem(item3);
        EXPECT_TRUE(testObj != testObj3);

        SetInventory testObj4;
        testObj4.name = "Test";
        SetInventoryItem item4;
        item4.name = "TestItem";
        item4.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj4.appendSetItem(item4);
        EXPECT_FALSE(testObj != testObj4);
        
    }

    TEST(SetInventory_Struct, ApiSetAppendItem)
    {
        SetInventory testObj;
        SetInventoryItem item;
        item.name = "Test";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        EXPECT_EQ(testObj.getSetList().size(), 1);
        auto item2 = testObj.getSetList()[0];
        EXPECT_EQ(item2->name, "Test");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventory_Struct, ApiSetAppendAssembly)
    {
        SetInventory testObj;
        SetInventoryAssembly item;
        item.name = "Test";
        testObj.appendSetAssembly(item);
        EXPECT_EQ(testObj.getSetList().size(), 1);
        auto item2 = testObj.getSetList()[0];
        EXPECT_EQ(item2->name, "Test");
        EXPECT_EQ(item2->getObjectType(), ItemType::Assembly);
    }

}

namespace sim_SetInventory
{
    TEST(SetInventoryItem_Struct,ConstructorDefault)
    {
        SetInventoryItem testObj;
        EXPECT_EQ(testObj.name, "Undefined");
        EXPECT_EQ(testObj.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj.getValue());
        EXPECT_EQ(value,"Undefined" );
    }

    TEST(SetInventoryItem_Struct,ConstructorByAssembly)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventoryItem$");

        rw::oso::ObjectStoreItem item;
        item.setName("$Field$Name$");
        item.setValueFromString("Test");

        assembly.addItem(item);

        rw::oso::ObjectStoreItem item2;
        item2.setName("name");
        item2.setValueFromString("Test2");

        assembly.addItem(item2);

        try
        {
            SetInventoryItem testObj(assembly);
            EXPECT_EQ(testObj.name, "Test");
            EXPECT_EQ(testObj.getObjectType(), ItemType::Item);
            EXPECT_EQ(testObj.getValueType(), ItemStoreType::Item_String);
            auto value = std::get<std::string>(testObj.getValue());
            EXPECT_EQ(value, "Test2");
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << e.what();
        }

    }

    TEST(SetInventoryItem_Struct, ConstructorByAssemblyMove)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventoryItem$");
        rw::oso::ObjectStoreItem item;
        item.setName("$Field$Name$");
        item.setValueFromString("Test");
        assembly.addItem(item);
        rw::oso::ObjectStoreItem item2;
        item2.setName("name");
        item2.setValueFromString("Test2");
        assembly.addItem(item2);
        SetInventoryItem testObj(std::move(assembly));
        EXPECT_EQ(testObj.name, "Test");
        EXPECT_EQ(testObj.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj.getValue());
        EXPECT_EQ(value, "Test2");
    }

    TEST(SetInventoryItem_Struct, ConstructorByCopy)
    {
        SetInventoryItem testObj;
        testObj.name = "Test";
        testObj.setValue<std::string, ItemStoreType::Item_String>("test");
        SetInventoryItem testObj2(testObj);
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj2.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj2.getValue());
        EXPECT_EQ(value, "test");
    }


    TEST(SetInventoryItem_Struct, ConstructorByMove)
    {
        SetInventoryItem testObj;
        testObj.name = "Test";
        testObj.setValue<std::string, ItemStoreType::Item_String>("test");
        SetInventoryItem testObj2(std::move(testObj));
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj2.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj2.getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryItem_Struct, OperatorMove)
    {
        SetInventoryItem testObj;
        testObj.name = "Test";
        testObj.setValue<std::string, ItemStoreType::Item_String>("test");
        SetInventoryItem testObj2;
        testObj2 = std::move(testObj);
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj2.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj2.getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryItem_Struct, OperatorAssign)
    {
        SetInventoryItem testObj;
        testObj.name = "Test";
        testObj.setValue<std::string, ItemStoreType::Item_String>("test");
        SetInventoryItem testObj2;
        testObj2 = testObj;
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj2.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj2.getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryItem_Struct, OperatorEqual)
    {
        SetInventoryItem testObj;
        testObj.name = "Test";
        testObj.setValue<std::string, ItemStoreType::Item_String>("test");
        SetInventoryItem testObj2;
        testObj2.name = "Test";
        testObj2.setValue<std::string, ItemStoreType::Item_String>("test");
        EXPECT_TRUE(testObj == testObj2);
    }

    TEST(SetInventoryItem_Struct, OperatorNotEqual)
    {
        SetInventoryItem testObj;
        testObj.name = "Test";
        testObj.setValue<std::string, ItemStoreType::Item_String>("test");
        SetInventoryItem testObj2;
        testObj2.name = "Test";
        testObj2.setValue<std::string, ItemStoreType::Item_String>("test2");
        EXPECT_TRUE(testObj != testObj2);

        SetInventoryItem testObj3;
        testObj3.name = "Test2";
        testObj3.setValue<std::string, ItemStoreType::Item_String>("test");
        EXPECT_TRUE(testObj != testObj3);

        SetInventoryItem testObj4;
        testObj4.name = "Test";
        testObj4.setValue<std::string, ItemStoreType::Item_String>("test");
        EXPECT_FALSE(testObj != testObj4);

    }

    TEST(SetInventoryItem_Struct, ApiSetGetValue)
    {
        SetInventoryItem testObj;
        testObj.setValue<std::string,ItemStoreType::Item_String>("test");
        EXPECT_EQ(testObj.name, "Undefined");
        EXPECT_EQ(testObj.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj.getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryItem_Struct, operatorToAssembly)
    {
        SetInventoryItem testObj;
        testObj.name = "Test";
        testObj.setValue<std::string, ItemStoreType::Item_String>("test");
        rw::oso::ObjectStoreAssembly assembly = testObj;
        EXPECT_EQ(assembly.getName(), "$Struct$SetInventoryItem$");
        EXPECT_EQ(assembly.getItems().size(), 2);

        auto itemName = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(assembly.getItems()[0]);
        EXPECT_EQ(itemName->getName(), "$Field$Name$");
        EXPECT_EQ(itemName->getValueAsString(), "Test");
        auto item = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(assembly.getItems()[1]);
        EXPECT_EQ(item->getValueAsString(), "test");
    }

}

namespace sim_SetInventory
{
    TEST(SetInventoryAssembly_Struct, ConstructorDefault)
    {
        SetInventoryAssembly testObj;
        EXPECT_EQ(testObj.name, "Undefined");
        EXPECT_EQ(testObj.getObjectType(), ItemType::Assembly);
        EXPECT_EQ(testObj.getSetList().size(), 0);
    }

    TEST(SetInventoryAssembly_Struct, ConstructorByAssembly)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventoryAssembly$");
        rw::oso::ObjectStoreItem item;
        item.setName("$Field$Name$");
        item.setValueFromString("Test");
        assembly.addItem(item);

        try
        {
            SetInventoryAssembly testObj(assembly);
            EXPECT_EQ(testObj.name, "Test");
            EXPECT_EQ(testObj.getObjectType(), ItemType::Assembly);
            EXPECT_EQ(testObj.getSetList().size(), 0);
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << e.what();
        }
    }

    TEST(SetInventoryAssembly_Struct, ConstructorByAssemblyMove)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventoryAssembly$");
        rw::oso::ObjectStoreItem item;
        item.setName("$Field$Name$");
        item.setValueFromString("Test");
        assembly.addItem(item);
        SetInventoryAssembly testObj(std::move(assembly));
        EXPECT_EQ(testObj.name, "Test");
        EXPECT_EQ(testObj.getObjectType(), ItemType::Assembly);
        EXPECT_EQ(testObj.getSetList().size(), 0);
    }


    TEST(SetInventoryAssembly_Struct, ConstructorByCopy)
    {
        SetInventoryAssembly testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        SetInventoryAssembly testObj2(testObj);
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Assembly);
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryAssembly_Struct, ConstructorByMove)
    {
        SetInventoryAssembly testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        SetInventoryAssembly testObj2(std::move(testObj));
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Assembly);
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryAssembly_Struct, OperatorMove)
    {
        SetInventoryAssembly testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        SetInventoryAssembly testObj2;
        testObj2 = std::move(testObj);
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Assembly);
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryAssembly_Struct, OperatorAssign)
    {
        SetInventoryAssembly testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        SetInventoryAssembly testObj2;
        testObj2 = testObj;
        EXPECT_EQ(testObj2.name, "Test");
        EXPECT_EQ(testObj2.getObjectType(), ItemType::Assembly);
        EXPECT_EQ(testObj2.getSetList().size(), 1);
        auto item2 = testObj2.getSetList()[0];
        EXPECT_EQ(item2->name, "TestItem");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryAssembly_Struct, OperatorEqual)
    {
        SetInventoryAssembly testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        SetInventoryAssembly testObj2;
        testObj2.name = "Test";
        SetInventoryItem item2;
        item2.name = "TestItem";
        item2.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj2.appendSetItem(item2);
        EXPECT_TRUE(testObj == testObj2);
    }

    TEST(SetInventoryAssembly_Struct, OperatorNotEqual)
    {
        SetInventoryAssembly testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);

        SetInventoryAssembly testObj2;
        testObj2.name = "Test";
        SetInventoryItem item2;
        item2.name = "TestItem1";
        item2.setValue<std::string, ItemStoreType::Item_String>("test2");
        testObj2.appendSetItem(item2);
        EXPECT_TRUE(testObj != testObj2);

        SetInventoryAssembly testObj3;
        testObj3.name = "Test2";
        SetInventoryItem item3;
        item3.name = "TestItem";
        item3.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj3.appendSetItem(item3);
        EXPECT_TRUE(testObj != testObj3);

        SetInventoryAssembly testObj4;
        testObj4.name = "Test";
        SetInventoryItem item4;
        item4.name = "TestItem";
        item4.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj4.appendSetItem(item4);
        EXPECT_FALSE(testObj != testObj4);
    }

    TEST(SetInventoryAssembly_Struct, ApiSetAppendItem)
    {
        SetInventoryAssembly testObj;
        SetInventoryItem item;
        item.name = "Test";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        EXPECT_EQ(testObj.getSetList().size(), 1);
        auto item2 = testObj.getSetList()[0];
        EXPECT_EQ(item2->name, "Test");
        EXPECT_EQ(item2->getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(item2->getValue());
        EXPECT_EQ(value, "test");
    }

    TEST(SetInventoryAssembly_Struct, ApiSetAppendAssembly)
    {
        SetInventoryAssembly testObj;
        SetInventoryAssembly item;
        item.name = "Test";
        testObj.appendSetAssembly(item);
        EXPECT_EQ(testObj.getSetList().size(), 1);
        auto item2 = testObj.getSetList()[0];
        EXPECT_EQ(item2->name, "Test");
        EXPECT_EQ(item2->getObjectType(), ItemType::Assembly);
    }

    TEST(SetInventoryAssembly_Struct, operatorToAssembly)
    {
        SetInventoryAssembly testObj;
        testObj.name = "Test";
        SetInventoryItem item;
        item.name = "TestItem";
        item.setValue<std::string, ItemStoreType::Item_String>("test");
        testObj.appendSetItem(item);
        rw::oso::ObjectStoreAssembly assembly = testObj;

        EXPECT_EQ(assembly.getName(), "$Struct$SetInventoryAssembly$");
        EXPECT_EQ(assembly.getItems().size(), 2);
        auto itemName = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(assembly.getItems()[0]);
        EXPECT_EQ(itemName->getName(), "$Field$Name$");
        EXPECT_EQ(itemName->getValueAsString(), "Test");

        auto item2 = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(assembly.getItems()[1]);
        EXPECT_EQ(item2->getName(), "$Struct$SetInventoryItem$");
        EXPECT_EQ(item2->getItems().size(), 2);
        auto itemName2 = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item2->getItems()[0]);
        EXPECT_EQ(itemName2->getName(), "$Field$Name$");
        EXPECT_EQ(itemName2->getValueAsString(), "TestItem");
        auto item3 = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item2->getItems()[1]);
        EXPECT_EQ(item3->getValueAsString(), "test");
    }

}


namespace sim_SetInventory
{
   TEST(SetInventoryUse,MutiConfigs)
   {
       SetInventory inventory;
       inventory.name = "ConfigTableTest";
       inventory.guid = "ConfigTableTestGuid";

       SetInventoryItem price;
       price.name = "Price";
       price.setValue<float, ItemStoreType::Item_Float>(10.5);
       inventory.appendSetItem(price);

       SetInventoryAssembly baseConfigs;
       baseConfigs.name = "BaseConfigs";
       SetInventoryItem size;
       size.name = "Size";
       size.setValue<int, ItemStoreType::Item_Int>(10);
       baseConfigs.appendSetItem(size);
       SetInventoryItem weight;
       weight.name = "Weight";
       weight.setValue<float, ItemStoreType::Item_Float>(10.5);
       baseConfigs.appendSetItem(weight);
       inventory.appendSetAssembly(baseConfigs);

       SetInventoryAssembly advancedConfigs;
       advancedConfigs.name = "AdvancedConfigs";
       SetInventoryItem size2;
       size2.name = "Size";
       size2.setValue<int, ItemStoreType::Item_Int>(20);
       advancedConfigs.appendSetItem(size2);
       SetInventoryItem weight2;
       weight2.name = "Weight";
       weight2.setValue<float, ItemStoreType::Item_Float>(20.5);
       advancedConfigs.appendSetItem(weight2);
       inventory.appendSetAssembly(advancedConfigs);

       rw::oso::ObjectStoreAssembly assembly = inventory;
       SetInventory inventory2(assembly);
       EXPECT_EQ(inventory2.name, "ConfigTableTest");
       EXPECT_EQ(inventory2.guid, "ConfigTableTestGuid");
       EXPECT_EQ(inventory2.getSetList().size(), 3);

       rw::oso::ObjectStoreAssembly assembly2 = inventory2;
       EXPECT_EQ(assembly, assembly2);
   }
}
