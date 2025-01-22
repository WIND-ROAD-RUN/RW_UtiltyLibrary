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
            Item_Long,
            Item_Item,
            Item_Assembly
        };
        using VariantItem = std::variant<int, long, float, double, std::string, bool, std::vector<SetInventoryItem>>;

        struct SetInventoryCore
        {
        public:
            std::string name{"Undefined"};
        public:
            virtual ~SetInventoryCore();
            virtual ItemType getType() = 0;

            virtual VariantItem getValue()=0;
            virtual ItemStoreType getValueType()=0;
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
            ItemType getType() override { return ItemType::Item; }
            VariantItem getValue() override;
            ItemStoreType getValueType() override;
        public:
            template<typename Value, ItemStoreType Type>
            void setValue(Value value);
        public:
            operator rw::oso::ObjectStoreAssembly();
        };

        struct SetInventoryAssembly final
            :public SetInventoryCore
        {
        public:
            explicit SetInventoryAssembly(rw::oso::ObjectStoreAssembly assembly);
            SetInventoryAssembly() = default;
        public:
            ItemType getType() override { return ItemType::Assembly; }
            VariantItem getValue() override;
            ItemStoreType getValueType() override;
        public:
            void setConfigs(std::vector<SetInventoryItem> configs);
            void appendSetItem(SetInventoryItem item);
            void appendSetAssembly(SetInventoryAssembly assembly);
        public:
            std::vector<std::pair<std::shared_ptr<SetInventoryCore>, ItemType>> getSetList();
        public:
            operator rw::oso::ObjectStoreAssembly();
        };

        struct SetInventory
        {
        private:
            std::vector<std::pair<std::shared_ptr<SetInventoryCore>, ItemType>> _items;
        public:
            explicit SetInventory(rw::oso::ObjectStoreAssembly assembly);
            SetInventory() = default;
        public:
            std::string name{"Undefined"};
            std::string guid{"Undefined"};
        public:
            std::vector<std::pair<std::shared_ptr<SetInventoryCore>, ItemType>> getSetList();
        public:
            void appendSetItem(SetInventoryItem item);
            void appendSetAssembly(SetInventoryAssembly assembly);
        public:
            operator rw::oso::ObjectStoreAssembly() const;
        };

        template<typename Value, ItemStoreType Type>
        inline void SetInventoryItem::setValue(Value value)
        {
            //TODO
        }

    } // namespace sim

} // namespace rw
