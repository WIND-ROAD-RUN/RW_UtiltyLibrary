#include"sim_SetInventoryFactory_t.hpp"

namespace sim_SetInventoryFactory
{
    TEST(SetInventoryFactory_struct,staticApiCreateItemByAssembly)
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
            auto testObj=SetInventoryFactory::createSetInventoryItem(assembly);
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
    TEST(SetInventoryFactory_struct, staticApiCreateItemByAssemblyMove)
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
        auto testObj = SetInventoryFactory::createSetInventoryItem(std::move(assembly));
        EXPECT_EQ(testObj.name, "Test");
        EXPECT_EQ(testObj.getObjectType(), ItemType::Item);
        EXPECT_EQ(testObj.getValueType(), ItemStoreType::Item_String);
        auto value = std::get<std::string>(testObj.getValue());
        EXPECT_EQ(value, "Test2");

    }

    TEST(SetInventoryFactory_struct, staticApiCreateAssemblyByAssembly)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventoryAssembly$");
        rw::oso::ObjectStoreItem item;
        item.setName("$Field$Name$");
        item.setValueFromString("Test");
        assembly.addItem(item);

        try
        {
            SetInventoryAssembly testObj = SetInventoryFactory::createSetInventoryAssembly(assembly);
            EXPECT_EQ(testObj.name, "Test");
            EXPECT_EQ(testObj.getObjectType(), ItemType::Assembly);
            EXPECT_EQ(testObj.getSetList().size(), 0);
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << e.what();
        }
    }
    TEST(SetInventoryFactory_struct, staticApiCreateAssemblyByAssemblyMove)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("$Struct$SetInventoryAssembly$");
        rw::oso::ObjectStoreItem item;
        item.setName("$Field$Name$");
        item.setValueFromString("Test");
        assembly.addItem(item);
        SetInventoryAssembly testObj = SetInventoryFactory::createSetInventoryAssembly(std::move(assembly));
        EXPECT_EQ(testObj.name, "Test");
        EXPECT_EQ(testObj.getObjectType(), ItemType::Assembly);
        EXPECT_EQ(testObj.getSetList().size(), 0);

    }

    TEST(SetInventoryFactory_struct, staticApiCreateInventoryByAssembly)
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
            auto testObj = SetInventoryFactory::createSetInventory(assembly);
            EXPECT_EQ(testObj.name, "Test");
            EXPECT_EQ(testObj.guid, "Test2");
            EXPECT_EQ(testObj.getSetList().size(), 0);
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << e.what();
        }

    }
    TEST(SetInventoryFactory_struct, staticApiCreateInventoryByAssemblyMove)
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
            auto testObj = SetInventoryFactory::createSetInventory(std::move(assembly));
            EXPECT_EQ(testObj.name, "Test");
            EXPECT_EQ(testObj.guid, "Test2");
            EXPECT_EQ(testObj.getSetList().size(), 0);
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << e.what();
        }

    }

}
