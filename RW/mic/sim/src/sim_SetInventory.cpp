#include"sim_SetInventory.hpp"


namespace rw {
    namespace sim {
        SetInventoryAssembly::SetInventoryAssembly
        (rw::oso::ObjectStoreAssembly assembly)
        {
            //TODO
        }

        SetInventoryCore::VariantItem
        SetInventoryAssembly::getValue()
        {
            //TODO
        }

        ItemStoreType
        SetInventoryAssembly::getValueType()
        {
            //TODO
        }

        void
        SetInventoryAssembly::setConfigs
        (std::vector<SetInventoryItem> configs)
        {
            //TODO
        }

        void
        SetInventoryAssembly::appendSetItem
        (SetInventoryItem item)
        {
            //TODO
        }

        void
        SetInventoryAssembly::appendSetAssembly
        (SetInventoryAssembly assembly)
        {
            //TODO
        }

        SetInventoryAssembly::operator
        oso::ObjectStoreAssembly()
        {
            //TODO
        }

        SetInventory::SetInventory
        (rw::oso::ObjectStoreAssembly assembly)
        {
            if (assembly.getName()!="SetInventory")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "Name")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    name = itemPtr->getValueAsString();
                }
                else if (item->getName() == "Guid")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    guid = itemPtr->getValueAsString();
                }
                else
                {
                    if (item->getName() == "Item")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "Assembly")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        appendSetAssembly(SetInventoryAssembly(*itemPtr));
                    }
                }
            }
            
        }
        std::vector<std::pair<std::shared_ptr<SetInventoryCore>, ItemType>>
        SetInventory::getSetList()
        {
            return _items;
        }
        void
        SetInventory::appendSetItem
        (SetInventoryItem item)
        {
            _items.emplace_back(std::make_shared<SetInventoryItem>(item), ItemType::Item);
        }

        void
        SetInventory::appendSetAssembly
        (SetInventoryAssembly assembly)
        {
            _items.emplace_back(std::make_shared<SetInventoryAssembly>(assembly), ItemType::Assembly);
        }

        SetInventory::operator
        rw::oso::ObjectStoreAssembly() const
        {
            rw::oso::ObjectStoreAssembly result;
            result.setName("SetInventory");

            rw::oso::ObjectStoreItem attributeName;
            attributeName.setName("Name");
            attributeName.setValueFromString(name);
            result.addItem(std::move(attributeName));

            rw::oso::ObjectStoreItem attributeGuid;
            attributeGuid.setName("Guid");
            attributeGuid.setValueFromString(guid);
            result.addItem(std::move(attributeGuid));

            for (const auto & [fst, snd]:_items)
            {
                if (snd == ItemType::Item)
                {
                    auto itemPtr = std::dynamic_pointer_cast<SetInventoryItem>(fst);
                    result.addItem(itemPtr->operator rw::oso::ObjectStoreAssembly());
                }
                else if (snd == ItemType::Assembly)
                {
                    auto assemblyPtr = std::dynamic_pointer_cast<SetInventoryAssembly>(fst);
                    result.addItem(assemblyPtr->operator rw::oso::ObjectStoreAssembly());
                }
                
            }

            return result;

        }

    } // namespace sim

} // namespace rw

