#include"sim_SetInventory.hpp"


namespace rw {
    namespace sim {
        SetInventoryAssembly::SetInventoryAssembly
        (const rw::oso::ObjectStoreAssembly& assembly)
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
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
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

        SetInventoryAssembly::SetInventoryAssembly(rw::oso::ObjectStoreAssembly&& assembly)
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
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
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

        SetInventoryAssembly::SetInventoryAssembly(const SetInventoryAssembly& assembly)
         : SetInventoryCore(assembly)
     {
            for (const auto& item : assembly._items)
            {
                if (item->getObjectType() == ItemType::Item)
                {
                    auto itemPtr = std::dynamic_pointer_cast<SetInventoryItem>(item);
                    _items.push_back(std::make_shared<SetInventoryItem>(*itemPtr));
                }
                else if (item->getObjectType() == ItemType::Assembly)
                {
                    auto assemblyPtr = std::dynamic_pointer_cast<SetInventoryAssembly>(item);
                    _items.push_back(std::make_shared<SetInventoryAssembly>(*assemblyPtr));
                }
            }
        }

        SetInventoryAssembly::SetInventoryAssembly(SetInventoryAssembly&& assembly) noexcept
        {
            name = std::move(assembly.name);
            _items = std::move(assembly._items);
        }

        SetInventoryAssembly::SetInventoryAssembly()
        {
            name = "Undefined";
        }

        SetInventoryAssembly& SetInventoryAssembly::operator=(const SetInventoryAssembly& other)
        {
            name = other.name;
            _items.clear();
            for (const auto& item : other._items)
            {
                if (item->getObjectType() == ItemType::Item)
                {
                    auto itemPtr = std::dynamic_pointer_cast<SetInventoryItem>(item);
                    _items.push_back(std::make_shared<SetInventoryItem>(*itemPtr));
                }
                else if (item->getObjectType() == ItemType::Assembly)
                {
                    auto assemblyPtr = std::dynamic_pointer_cast<SetInventoryAssembly>(item);
                    _items.push_back(std::make_shared<SetInventoryAssembly>(*assemblyPtr));
                }
            }
            return *this;
        }

        SetInventoryAssembly& SetInventoryAssembly::operator=(SetInventoryAssembly&& other) noexcept
        {
            name = std::move(other.name);
            _items = std::move(other._items);
            return *this;
        }

        bool SetInventoryAssembly::operator==(const SetInventoryAssembly& other) const
        {
            if (name != other.name || _items.size() != other._items.size())
            {
                return false;
            }
            for (size_t i = 0; i < _items.size(); i++)
            {
                if (*_items[i] != *other._items[i])
                {
                    return false;
                }
            }
            return true;
        }

        bool SetInventoryAssembly::operator!=(const SetInventoryAssembly& other) const
        {
            return !(*this == other);
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

        SetInventoryAssembly::operator rw::oso::ObjectStoreAssembly() const
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
        (const rw::oso::ObjectStoreAssembly& assembly)
        {
            if (assembly.getName() != "$Struct$SetInventory$")
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
                else if (item->getName() == "$Field$Guid$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    guid = itemPtr->getValueAsString();
                }
                else
                {
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
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

        SetInventory::SetInventory(rw::oso::ObjectStoreAssembly&& assembly)
        {
            if (assembly.getName() != "$Struct$SetInventory$")
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
                else if (item->getName() == "$Field$Guid$")
                {
                    auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                    guid = itemPtr->getValueAsString();
                }
                else
                {
                    if (item->getName() == "$Struct$SetInventoryItem$")
                    {
                        auto itemPtr = std::dynamic_pointer_cast<rw::oso::ObjectStoreAssembly>(item);
                        appendSetItem(SetInventoryItem(*itemPtr));
                    }
                    else if (item->getName() == "$Struct$SetInventoryAssembly$")
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

        SetInventory::SetInventory(const SetInventory& inventory)
        {
            name = inventory.name;
            guid = inventory.guid;
            for (const auto& item : inventory._items)
            {
                if (item->getObjectType() == ItemType::Item)
                {
                    auto itemPtr = std::dynamic_pointer_cast<SetInventoryItem>(item);
                    _items.push_back(std::make_shared<SetInventoryItem>(*itemPtr));
                }
                else if (item->getObjectType() == ItemType::Assembly)
                {
                    auto assemblyPtr = std::dynamic_pointer_cast<SetInventoryAssembly>(item);
                    _items.push_back(std::make_shared<SetInventoryAssembly>(*assemblyPtr));
                }
            }
        }

        SetInventory::SetInventory(SetInventory&& inventory) noexcept
        {
            name = std::move(inventory.name);
            guid = std::move(inventory.guid);
            _items = std::move(inventory._items);
        }

        SetInventory& SetInventory::operator=(const SetInventory& other)
        {
            name = other.name;
            guid = other.guid;
            _items.clear();
            for (const auto& item : other._items)
            {
                if (item->getObjectType() == ItemType::Item)
                {
                    auto itemPtr = std::dynamic_pointer_cast<SetInventoryItem>(item);
                    _items.push_back(std::make_shared<SetInventoryItem>(*itemPtr));
                }
                else if (item->getObjectType() == ItemType::Assembly)
                {
                    auto assemblyPtr = std::dynamic_pointer_cast<SetInventoryAssembly>(item);
                    _items.push_back(std::make_shared<SetInventoryAssembly>(*assemblyPtr));
                }
            }
            return *this;
        }

        SetInventory& SetInventory::operator=(SetInventory&& other) noexcept
        {
            name = std::move(other.name);
            guid = std::move(other.guid);
            _items = std::move(other._items);
            return *this;
        }

        bool SetInventory::operator==(const SetInventory& other) const
        {
            if (name != other.name || guid != other.guid || _items.size() != other._items.size())
            {
                return false;
            }
            for (size_t i = 0; i < _items.size(); i++)
            {
                if (*_items[i] != *other._items[i])
                {
                    return false;
                }
            }
            return true;
        }

        bool SetInventory::operator!=(const SetInventory& other) const
        {
            return !(*this == other);
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
            result.setName("$Struct$SetInventory$");
            rw::oso::ObjectStoreItem nameItem;
            nameItem.setName("$Field$Name$");
            nameItem.setValueFromString(name);
            result.addItem(std::move(nameItem));
            rw::oso::ObjectStoreItem guidItem;
            guidItem.setName("$Field$Guid$");
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

        SetInventoryItem::SetInventoryItem(const rw::oso::ObjectStoreAssembly& assembly)
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

        SetInventoryItem::SetInventoryItem(rw::oso::ObjectStoreAssembly&& assembly)
        {
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
                    name = itemPtr->getValueAsString();
                }
                else
                {
                    _item = *std::dynamic_pointer_cast<rw::oso::ObjectStoreItem>(item);
                }
            }
        }

        SetInventoryItem::SetInventoryItem(const SetInventoryItem& item)
         : SetInventoryCore(item)
        {
            _item = item._item;
        }

        SetInventoryItem::SetInventoryItem(SetInventoryItem&& item) noexcept
        {
            name = std::move(item.name);
            _item = std::move(item._item);
        }

        SetInventoryItem::SetInventoryItem()
        {
            _item.setValueFromString("Undefined");
        }

        SetInventoryItem& SetInventoryItem::operator=(const SetInventoryItem& other)
        {
            name = other.name;
            _item = other._item;
            return *this;
        }

        SetInventoryItem& SetInventoryItem::operator=(SetInventoryItem&& other) noexcept
        {
            name = std::move(other.name);
            _item = std::move(other._item);
            return *this;
        }

        bool SetInventoryItem::operator==(const SetInventoryItem& other) const
        {
            return name == other.name && _item == other._item;
        }

        bool SetInventoryItem::operator!=(const SetInventoryItem& other) const
        {
            return name != other.name || _item != other._item;
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

        SetInventoryCore::SetInventoryCore(const SetInventoryCore& core)
        {
            name = core.name;
        }

        SetInventoryCore::SetInventoryCore(const SetInventoryCore&& core) noexcept
        {
            name = core.name;
        }

        bool SetInventoryCore::operator==(const SetInventoryCore& other) const
        {
            return name == other.name;
        }

        bool SetInventoryCore::operator!=(const SetInventoryCore& other) const
        {
            return name != other.name;
        }

        SetInventoryCore& SetInventoryCore::operator=(const SetInventoryCore& other)
        {
            name = other.name;
            return *this;
        }

        SetInventoryCore& SetInventoryCore::operator=(SetInventoryCore&& other) noexcept
        {
            name = std::move(other.name);
            return *this;
        }
    } // namespace sim

} // namespace rw

