#pragma once

#include"sim_SetInventory.hpp"

#include"oso_core.h"

namespace rw
{
    namespace sim
    {
        class SetInventoryFactory
        {
            static SetInventory createSetInventory(const oso::ObjectStoreAssembly& assembly);

            static SetInventoryItem createSetInventoryItem(const oso::ObjectStoreAssembly& assembly);

            static SetInventoryAssembly createSetInventoryAssembly(const oso::ObjectStoreAssembly& assembly);


        };

    } // namespace sim
} // namespace rw
