#pragma once

#include"oso_core.h"

#include<string>
#include <variant>

namespace rw {
    namespace sim {
        enum class ItemType
        {
            Item,
            Assembly
        };
        struct SetInventoryItem;
        enum class ItemStoreType
        {
            Item_String,
            Item_Int,
            Item_Float,
            Item_Double,
            Item_Bool,
            Item_Long
        };
        using VariantItem = std::variant<int, long, float, double, std::string, bool>;

        struct SetInventoryCore
        {
        public:
            std::string name{"Undefined"};
        public:
            virtual ~SetInventoryCore();
            virtual ItemType getObjectType() = 0;
            virtual VariantItem getValue() =0;
            virtual ItemStoreType getValueType() =0;
        };

        struct SetInventoryItem final
            :public SetInventoryCore
        {
        private:
            rw::oso::ObjectStoreItem _item;
        public:
            explicit SetInventoryItem(rw::oso::ObjectStoreAssembly assembly);
            SetInventoryItem();
        public:
            ItemType getObjectType() override { return ItemType::Item; }
            VariantItem getValue() override ;
            ItemStoreType getValueType() override;
        public:
            template<typename Value, ItemStoreType Type>
            void setValue(Value value);
        public:
            operator rw::oso::ObjectStoreAssembly() const;
        };

        struct SetInventoryAssembly final
            :public SetInventoryCore
        {
        private:
            VariantItem getValue() override;
            ItemStoreType getValueType() override;
        private:
            std::vector<std::shared_ptr<SetInventoryCore>> _items;
        public:
            explicit SetInventoryAssembly(rw::oso::ObjectStoreAssembly assembly);
            SetInventoryAssembly();
        public:
            ItemType getObjectType() override { return ItemType::Assembly; }
        public:
            void appendSetItem(const SetInventoryItem & item);
            void appendSetItem(SetInventoryItem&& item);

            void appendSetAssembly(const SetInventoryAssembly & assembly);
            void appendSetAssembly(SetInventoryAssembly&& assembly);

        public:
            std::vector<std::shared_ptr<SetInventoryCore>> getSetList();
        public:
            operator rw::oso::ObjectStoreAssembly();
        };

        struct SetInventory
        {
        private:
            std::vector<std::shared_ptr<SetInventoryCore>> _items;
        public:
            explicit SetInventory(rw::oso::ObjectStoreAssembly assembly);
            SetInventory() = default;
        public:
            std::string name{"Undefined"};
            std::string guid{"Undefined"};
        public:
            std::vector<std::shared_ptr<SetInventoryCore>> getSetList();
        public:
            void appendSetItem(const SetInventoryItem & item);
            void appendSetAssembly(const SetInventoryAssembly & assembly);
        public:
            operator rw::oso::ObjectStoreAssembly() const;
        };

        template<typename Value, ItemStoreType Type>
        inline void SetInventoryItem::setValue(Value value)
        {
            if constexpr (Type == ItemStoreType::Item_String)
            {
                _item.setValueFromString(value);
            }
            else if constexpr (Type == ItemStoreType::Item_Int)
            {
                _item.setValueFromInt(value);
            }
            else if constexpr (Type == ItemStoreType::Item_Float)
            {
                _item.setValueFromFloat(value);
            }
            else if constexpr (Type == ItemStoreType::Item_Double)
            {
                _item.setValueFromDouble(value);
            }
            else if constexpr (Type == ItemStoreType::Item_Bool)
            {
                _item.setValueFromBool(value);
            }
            else if constexpr (Type == ItemStoreType::Item_Long)
            {
                _item.setValueFromLong(value);
            }
            else
            {
                throw std::runtime_error("Invalid assembly type");
            }
        }

    } // namespace sim

} // namespace rw
