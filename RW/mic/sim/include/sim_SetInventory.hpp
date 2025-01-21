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

        struct SetInventoryItem;
        struct SetInventoryCore
        {
        public:
            using VariantItem = std::variant<int, long, float, double, std::string, bool, std::vector<SetInventoryItem>>;
        public:
            std::string name{"Undefined"};
        public:
            virtual ~SetInventoryCore() = default;
            virtual ItemType getType() = 0;

            virtual VariantItem getValue()=0;
            virtual ItemStoreType getValueType()=0;
        };

        struct SetInventoryItem final
            :public SetInventoryCore
        {
        public:
            explicit SetInventoryItem(rw::oso::ObjectStoreAssembly assembly);
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
        public:
            std::string name;
            std::string guid;
        public:
            std::vector<std::pair<std::shared_ptr<SetInventoryCore>, ItemType>> getSetList();
        public:
            void appendSetItem(SetInventoryItem item);
            void appendSetAssembly(SetInventoryAssembly assembly);
        public:
            operator rw::oso::ObjectStoreAssembly() const;
        };

    } // namespace sim

} // namespace rw
