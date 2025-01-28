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
