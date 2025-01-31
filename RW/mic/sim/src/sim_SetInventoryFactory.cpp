#include"sim_SetInventoryFactory.hpp"

namespace rw
{
    namespace sim
    {
        SetInventory SetInventoryFactory::createSetInventory(const oso::ObjectStoreAssembly& assembly)
        {
            SetInventory result;

            if (assembly.getName() != "$Struct$SetInventory$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.name = itemPtr->getValueAsString();
                }
                else if (item->getName() == "$Field$Guid$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.guid = itemPtr->getValueAsString();
                }
                else
                {
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetAssembly(SetInventoryAssembly(*itemPtr));
                    }
                    else
                    {
                        throw std::runtime_error("Invalid assembly type");
                    }
                }
            }
            return result;
        }

        SetInventory SetInventoryFactory::createSetInventory(oso::ObjectStoreAssembly&& assembly)
        {
            SetInventory result;
            if (assembly.getName() != "$Struct$SetInventory$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.name = itemPtr->getValueAsString();
                }
                else if (item->getName() == "$Field$Guid$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.guid = itemPtr->getValueAsString();
                }
                else
                {
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetAssembly(SetInventoryAssembly(*itemPtr));
                    }
                    else
                    {
                        throw std::runtime_error("Invalid assembly type");
                    }
                }
            }
            return result;
        }

        SetInventoryItem SetInventoryFactory::createSetInventoryItem(const oso::ObjectStoreAssembly& assembly)
        {
            SetInventoryItem result;
            if (assembly.getName() != "$Struct$SetInventoryItem$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            if (assembly.getItems().size() != 2)
            {
                throw std::runtime_error("Invalid assembly size");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.name = itemPtr->getValueAsString();
                }
                else
                {
                    result._item = *std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                }
            }
            return result;
        }

        SetInventoryItem SetInventoryFactory::createSetInventoryItem(oso::ObjectStoreAssembly&& assembly)
        {
            SetInventoryItem result;
            if (assembly.getName() != "$Struct$SetInventoryItem$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            if (assembly.getItems().size() != 2)
            {
                throw std::runtime_error("Invalid assembly size");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.name = itemPtr->getValueAsString();
                }
                else
                {
                    result._item = *std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                }
            }
            return result;
        }

        SetInventoryAssembly SetInventoryFactory::createSetInventoryAssembly(const oso::ObjectStoreAssembly& assembly)
        {
            SetInventoryAssembly result;
            if (assembly.getName() != "$Struct$SetInventoryAssembly$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.name = itemPtr->getValueAsString();
                }
                else
                {
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetAssembly(SetInventoryAssembly(*itemPtr));
                    }
                    else
                    {
                        throw std::runtime_error("Invalid assembly type");
                    }
                }
            }
            return result;
        }

        SetInventoryAssembly SetInventoryFactory::createSetInventoryAssembly(oso::ObjectStoreAssembly&& assembly)
        {
            SetInventoryAssembly result;
            if (assembly.getName() != "$Struct$SetInventoryAssembly$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    result.name = itemPtr->getValueAsString();
                }
                else
                {
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        result.appendSetAssembly(SetInventoryAssembly(*itemPtr));
                    }
                    else
                    {
                        throw std::runtime_error("Invalid assembly type");
                    }
                }
            }
            return result;
        }
    } // namespace sim
} // namespace rw
