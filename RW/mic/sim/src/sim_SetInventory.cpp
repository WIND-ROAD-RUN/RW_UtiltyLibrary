#include"sim_SetInventory.hpp"


namespace rw {
    namespace sim {
        SetInventoryAssembly::SetInventoryAssembly
        (rw::oso::ObjectStoreAssembly assembly)
        {
            //TODO
        }

        VariantItem
        SetInventoryAssembly::getValue()
        {
            //TODO
            return VariantItem(static_cast<int>(0));
        }

        ItemStoreType
        SetInventoryAssembly::getValueType()
        {
            //TODO
            return ItemStoreType();
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

        std::vector<std::pair<std::shared_ptr<SetInventoryCore>, ItemType>> SetInventoryAssembly::getSetList()
        {
            return std::vector<std::pair<std::shared_ptr<SetInventoryCore>, ItemType>>();
        }

        SetInventoryAssembly::operator rw::oso::ObjectStoreAssembly()
        {
            //TODO
            return rw::oso::ObjectStoreAssembly();
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

        SetInventoryItem::SetInventoryItem(rw::oso::ObjectStoreAssembly assembly)
        {

        }

        SetInventoryItem::SetInventoryItem()
        {

        }

        VariantItem SetInventoryItem::getValue()
        {
            auto itemType = _item.getType();
            switch (itemType)
            {
            case rw::oso::ObjectDataItemStoreType::item_string:
                return VariantItem(_item.getValueAsString());
            case rw::oso::ObjectDataItemStoreType::item_int:
                return VariantItem(_item.getValueAsInt());
            case rw::oso::ObjectDataItemStoreType::item_long:
                return VariantItem(_item.getValueAsLong());
            case rw::oso::ObjectDataItemStoreType::item_float:
                return VariantItem(_item.getValueAsFloat());
            case rw::oso::ObjectDataItemStoreType::item_double:
                return VariantItem(_item.getValueAsDouble());
            case rw::oso::ObjectDataItemStoreType::item_bool:
                return VariantItem(_item.getValueAsBool());
            default:
                throw std::runtime_error("Invalid item type");
            }
        }

        ItemStoreType SetInventoryItem::getValueType()
        {
            switch (auto itemType = _item.getType())
            {
            case rw::oso::ObjectDataItemStoreType::item_string:
                return ItemStoreType::Item_String;
            case rw::oso::ObjectDataItemStoreType::item_int:
                return ItemStoreType::Item_Int;
            case rw::oso::ObjectDataItemStoreType::item_long:
                return ItemStoreType::Item_Long;
            case rw::oso::ObjectDataItemStoreType::item_float:
                return ItemStoreType::Item_Float;
            case rw::oso::ObjectDataItemStoreType::item_double:
                return ItemStoreType::Item_Double;
            case rw::oso::ObjectDataItemStoreType::item_bool:
                return ItemStoreType::Item_Bool;
            default:
                throw std::runtime_error("Invalid item type");
            }
        }

        SetInventoryItem::operator rw::oso::ObjectStoreAssembly()
        {
            rw::oso::ObjectStoreAssembly result;
            result.setName("SetInventoryItem");

            rw::oso::ObjectStoreItem item;
            item.setName("Name");
            item.setValueFromString(this->name);
            result.addItem(std::move(item));

            return result;
           
        }

        SetInventoryCore::~SetInventoryCore()
        {
        }

} // namespace sim

} // namespace rw

