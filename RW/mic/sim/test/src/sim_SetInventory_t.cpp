#include"sim_SetInventory_t.hpp"

namespace sim_SetInventory
{
    TEST(SetInventory_TEST,fieldName)
    {
        SetInventory inventory;
        EXPECT_EQ(inventory.name, "Undefined");

        inventory.name = "Test";
        EXPECT_EQ(inventory.name, "Test");

        inventory.name = "Test2";
        EXPECT_EQ(inventory.name, "Test2");
    }

    TEST(SetInventory_TEST,fieldGuid)
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
    TEST(SetInventoryItem_TEST,ConstructorByAssembly)
    {
        rw::oso::ObjectStoreAssembly assembly;
        assembly.setName("Test");

        SetInventoryItem item(rw::oso::ObjectStoreAssembly());

    }
}
