#include"sim_SetInventory.hpp"


namespace rw {
    namespace sim {
        SetInventoryAssembly::SetInventoryAssembly
        (rw::oso::ObjectStoreAssembly assembly)
        {
            if (assembly.getName() != "$Struct$SetInventoryAssembly$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    name = itemPtr->getValueAsString();
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
                    else
                    {
                        throw std::runtime_error("Invalid assembly type");
                    }
                }
            }
        }

        SetInventoryAssembly::SetInventoryAssembly()
        {
            name = "Undefined";
        }

        void SetInventoryAssembly::appendSetItem(const SetInventoryItem& item)
        {
            _items.push_back(std::make_shared<SetInventoryItem>(item));
        }

        void SetInventoryAssembly::appendSetItem(SetInventoryItem&& item)
        {
            _items.push_back(std::make_shared<SetInventoryItem>(std::move(item)));
        }

        void SetInventoryAssembly::appendSetAssembly(const SetInventoryAssembly& assembly)
        {
            _items.push_back(std::make_shared<SetInventoryAssembly>(assembly));
        }

        void SetInventoryAssembly::appendSetAssembly(SetInventoryAssembly&& assembly)
        {
            _items.push_back(std::make_shared<SetInventoryAssembly>(std::move(assembly)));
        }

        std::vector<std::shared_ptr<SetInventoryCore>> SetInventoryAssembly::getSetList()
        {
            return _items;
        }

        SetInventoryAssembly::operator rw::oso::ObjectStoreAssembly()
        {
            rw::oso::ObjectStoreAssembly result;
            result.setName("$Struct$SetInventoryAssembly$");
            rw::oso::ObjectStoreItem attributeName;
            attributeName.setName("$Field$Name$");
            attributeName.setValueFromString(name);
            result.addItem(std::move(attributeName));

            for (auto & item:_items)
            {
                if (item->getObjectType() == ItemType::Item)
                {
                    auto itemPtr = std::dynamic_pointer_cast<SetInventoryItem>(item);
                    result.addItem(itemPtr->operator rw::oso::ObjectStoreAssembly());
                }
                else if (item->getObjectType() == ItemType::Assembly)
                {
                    auto assemblyPtr = std::dynamic_pointer_cast<SetInventoryAssembly>(item);
                    result.addItem(assemblyPtr->operator rw::oso::ObjectStoreAssembly());
                }
            }
            return result;
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

        std::vector<std::shared_ptr<SetInventoryCore>> SetInventory::getSetList()
        {
            return _items;
        }

        void SetInventory::appendSetItem(const SetInventoryItem& item)
        {
            _items.push_back(std::make_shared<SetInventoryItem>(item));
        }

        void SetInventory::appendSetAssembly(const SetInventoryAssembly& assembly)
        {
            _items.push_back(std::make_shared<SetInventoryAssembly>(assembly));
        }

        SetInventory::operator
        rw::oso::ObjectStoreAssembly() const
        {
            rw::oso::ObjectStoreAssembly result;
            result.setName("SetInventory");
            rw::oso::ObjectStoreItem nameItem;
            nameItem.setName("Name");
            nameItem.setValueFromString(name);
            result.addItem(std::move(nameItem));
            rw::oso::ObjectStoreItem guidItem;
            guidItem.setName("Guid");
            guidItem.setValueFromString(guid);
            result.addItem(std::move(guidItem));
            for (const auto& item : _items)
            {
                if (item->getObjectType() == ItemType::Item)
                {
                    auto itemPtr = std::dynamic_pointer_cast<SetInventoryItem>(item);
                    result.addItem(itemPtr->operator rw::oso::ObjectStoreAssembly());
                }
                else if (item->getObjectType() == ItemType::Assembly)
                {
                    auto assemblyPtr = std::dynamic_pointer_cast<SetInventoryAssembly>(item);
                    result.addItem(assemblyPtr->operator rw::oso::ObjectStoreAssembly());
                }
            }
            return result;
        }

        SetInventoryItem::SetInventoryItem(rw::oso::ObjectStoreAssembly assembly)
        {
            if (assembly.getName() != "$Struct$SetInventoryItem$")
            {
                throw std::runtime_error("Invalid assembly type");
            }
            if (assembly.getItems().size()!=2)
            {
                throw std::runtime_error("Invalid assembly size");
            }
            for (const auto& item : assembly.getItems())
            {
                if (item->getName() == "$Field$Name$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    name = itemPtr->getValueAsString();
                }
                else
                {
                    _item = *std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                }
            }
        }

        SetInventoryItem::SetInventoryItem()
        {
            _item.setValueFromString("Undefined");
        }

        VariantItem SetInventoryItem::getValue()
        {
            auto itemType = _item.getType();
            switch (itemType)
            {
            case rw::oso::ObjectDataItemStoreType::item_string:
                return { _item.getValueAsString() };
            case rw::oso::ObjectDataItemStoreType::item_int:
                return { _item.getValueAsInt() };
            case rw::oso::ObjectDataItemStoreType::item_long:
                return { _item.getValueAsLong() };
            case rw::oso::ObjectDataItemStoreType::item_float:
                return { _item.getValueAsFloat() };
            case rw::oso::ObjectDataItemStoreType::item_double:
                return {_item.getValueAsDouble()
            };
            case rw::oso::ObjectDataItemStoreType::item_bool:
                return { _item.getValueAsBool() };
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

        SetInventoryItem::operator rw::oso::ObjectStoreAssembly() const
        {
            rw::oso::ObjectStoreAssembly result;
            result.setName("$Struct$SetInventoryItem$");

            rw::oso::ObjectStoreItem item;
            item.setName("$Field$Name$");
            item.setValueFromString(this->name);
            result.addItem(std::move(item));
            result.addItem(_item);

            return result;
           
        }

        VariantItem SetInventoryAssembly::getValue()
        {
            return {"Undefined"};
        }

        ItemStoreType SetInventoryAssembly::getValueType()
        {
            return ItemStoreType::Item_String;
        }

        SetInventoryCore::~SetInventoryCore()
        {

        }

} // namespace sim

} // namespace rw

