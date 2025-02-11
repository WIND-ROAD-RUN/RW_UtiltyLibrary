#pragma once

#include"oso_core.h"

#include<string>
#include <variant>
#include <memory>
#include <vector>

namespace rw {
    namespace oso
    {
        class ObjectStoreCore;
        class ObjectStoreItem;
        class ObjectStoreAssembly;
    }

    namespace sim {
        struct SetInventoryFactory;
        enum class ItemType
        {
            Item,//Represents an item
            Assembly//Represents an assembly
        };

        struct SetInventoryItem;
        enum class ItemStoreType
        {
            Item_String,//If SetInventoryItem stores a string, it is of this type
            Item_Int,//If SetInventoryItem stores an integer, it is of this type
            Item_Float,//If SetInventoryItem stores a float, it is of this type
            Item_Double,//If SetInventoryItem stores a double, it is of this type
            Item_Bool,//If SetInventoryItem stores a boolean, it is of this type
            Item_Long//If SetInventoryItem stores a long, it is of this type
        };

        //The type of data stored in the Object Data Item class
        using VariantItem = std::variant<int, long, float, double, std::string, bool>;

        struct SetInventoryCore
        {
            friend struct SetInventoryFactory;
        public:

            /**
             * @brief The name of the object store
             *
             * The name representation of the instance object, which can serve as the node name in the class composition structure.
             */
            std::string name{ "Undefined" };
        public:

            SetInventoryCore() = default;
            virtual ~SetInventoryCore() = default;
            SetInventoryCore(const SetInventoryCore& core);
            SetInventoryCore(const SetInventoryCore&& core) noexcept;
        public:
            bool operator==(const SetInventoryCore& other) const;
            bool operator!=(const SetInventoryCore& other) const;
        public:
            SetInventoryCore& operator=(const SetInventoryCore& other);
            SetInventoryCore& operator=(SetInventoryCore&& other) noexcept;

        public:
            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the type of the object store
             *
             *@Returns: ItemType
             *   - ItemType::Item : If the object is an item
             *   - ItemType::Assembly: If the object is an assembly
             *
             *@Throws:
             *  void
             */
            virtual ItemType getObjectType() = 0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the value of the object store
             *
             *@Returns: VariantItem
             *   - The value of the object store
             *
             *@Throws:
             *  void
             *@Warning:
             *  It is just for struct SetInventoryItem to implement
             */
            virtual VariantItem getValue() = 0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the type of the object store
             *
             *@Returns: ItemStoreType
             *   - The type of the object store
             *
             *@Throws:
             *  void
             *@warning:
             *  It is just for struct SetInventoryItem to implement
             */
            virtual ItemStoreType getValueType() = 0;
        };

        struct SetInventoryItem final
            :public SetInventoryCore
        {
            //Friend SetInventoryFactory to help create SetInventoryItem
            friend struct SetInventoryFactory;
        private:
            /**
             * @brief ObjectStoreItem which stores the real data
             *
             * The real data of the SetInventoryItem is stored in the ObjectStoreItem
             */
            rw::oso::ObjectStoreItem _item;
        public:
            /**
             *@Parameters:
             *  - assembly: The assembly,which has fixed format, will be used to create the SetInventoryItem
             *@Methods:
             *  Constructor
             *@Returns:
             *  void
             *@Throws:
             *  std::runtime_error: If the assembly is invalid
             *      - If the assembly name is not "$Struct$SetInventoryItem$"
             *      - If the assembly size is not 2
             *@Warning:
             * Please make sure the assembly is valid
             */
            explicit SetInventoryItem(const rw::oso::ObjectStoreAssembly& assembly);

            /**
             *@Parameters:
             *  - assembly: The assembly,which has fixed format, will be used to create the SetInventoryItem
             *@Methods:
             *  Constructor
             *@Returns:
             *  void
             *@Throws:
             *  std::runtime_error: If the assembly is invalid
             *      - If the assembly name is not "$Struct$SetInventoryItem$"
             *      - If the assembly size is not 2
             *@Warning:
             * Please make sure the assembly is valid
             */
            explicit SetInventoryItem(rw::oso::ObjectStoreAssembly&& assembly);

            /**
             *@Parameters:
             *  - item: The SetInventoryItem, which will be used to create the SetInventoryItem
             *@Methods:
             *  Constructor
             *@Returns:
             *  void
             */
            SetInventoryItem(const  SetInventoryItem& item);

            /**
             *@Parameters:
             *  - item: The SetInventoryItem, which will be used to create the SetInventoryItem
             *@Methods:
             *  Constructor
             *@Returns:
             *  void
             */
            SetInventoryItem(SetInventoryItem&& item) noexcept;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Constructor
             *@Returns:
             *  void
             *@warning:
             *  If you use this constructor, the SetInventoryItem will be initialized with default
             *value which value is "Undefined" and type is Item_String
             */
            SetInventoryItem();
            ~SetInventoryItem() override = default;
        public:
            /**
             *@Parameters:
             *  - other: The SetInventoryItem, which will be used to assign to the current SetInventoryItem
             *@Methods:
             *  Copy assignment operator
             *@Returns: SetInventoryItem&
             *  - The reference of the current SetInventoryItem
             *@Throws:
             *  void
             */
            SetInventoryItem& operator=(const SetInventoryItem& other);

            /**
             *@Parameters:
             *  - other: The SetInventoryItem, which will be used to move to the current SetInventoryItem
             *@Methods:
             *  Move assignment operator
             *@Returns: SetInventoryItem&
             *  - The reference of the current SetInventoryItem
             *@Throws:
             *  void
             */
            SetInventoryItem& operator=(SetInventoryItem&& other) noexcept;

        public:
            /**
             *@Parameters:
             *  - other: The SetInventoryItem, which will be used to compare with the current SetInventoryItem
             *@Methods:
             *  Compare operator
             *@Returns: bool
             *  - true: If the current SetInventoryItem is equal to the other SetInventoryItem
             *  - false: If the current SetInventoryItem is not equal to the other SetInventoryItem
             *@Throws:
             *  void
             */
            bool operator==(const SetInventoryItem& other) const;

            /**
             *@Parameters:
             *  - other: The SetInventoryItem, which will be used to compare with the current SetInventoryItem
             *@Methods:
             *  Compare operator
             *@Returns: bool
             *  - true: If the current SetInventoryItem is not equal to the other SetInventoryItem
             *  - false: If the current SetInventoryItem is equal to the other SetInventoryItem
             *@Throws:
             *  void
             */
            bool operator!=(const SetInventoryItem& other) const;

        public:
            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the type of the object store
             *@Returns: ItemType::Item
             *  - ItemType::Item : The object is an item
             *@Throws:
             *  void
             */
            ItemType getObjectType() override { return ItemType::Item; }

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the value of the object store
             *@Returns: VariantItem
             *  - The value of the object store
             *@Throws:
             *  void
             */
            VariantItem getValue() override;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the type of the object store
             *@Returns: ItemStoreType
             *  - Item_String : The object is a string
             *  - Item_Int : The object is an integer
             *  - Item_Float : The object is a float
             *  - Item_Double : The object is a double
             *  - Item_Bool : The object is a boolean
             *  - Item_Long : The object is a long
             *@Throws:
             *  void
             */
            ItemStoreType getValueType() override;
        public:
            /**
             *@Template Parameters:
             *  - Value: The type of the value you are going to set
             *  - Type: The type of the value you are going to set
             *
             *@Parameters:
             *  - value: The value you are going to set as
             *@Methods:
             *  Set the value of the object store
             *@Returns: void
             *@Throws:
             *  std::runtime_error: If the type is invalid
             */
            template<typename Value, ItemStoreType Type>
            void setValue(Value value);

        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Convert the SetInventoryItem to ObjectStoreAssembly
             *@Returns: rw::oso::ObjectStoreAssembly
             *  - The ObjectStoreAssembly which is converted from the SetInventoryItem
             *@Throws:
             *  void
             */
            operator rw::oso::ObjectStoreAssembly() const;
        };

        struct SetInventoryAssembly final
            :public SetInventoryCore
        {
            //Friend SetInventoryFactory to help create SetInventoryAssembly
            friend struct SetInventoryFactory;
        private:
            VariantItem getValue() override;
            ItemStoreType getValueType() override;
        private:
            /**
             * @brief The details of the assembly
             *
             * The details of the assembly are stored in the _items
             */
            std::vector<std::shared_ptr<SetInventoryCore>> _items;
        public:
            /**
             *@Parameters:
             *  - assembly: The assembly,which has fixed format, will be used to create the SetInventoryAssembly
             *@Methods:
             *  Constructor with assembly,if the assembly is invalid, it will throw a runtime_error
             *@Returns: 
             *  void
             *@Throws:
             *  std::runtime_error: If the assembly is invalid
             *      - If the assembly name is not "$Struct$SetInventoryAssembly$"
             *      - If the _items has invalid type,which is not ItemType::Item or ItemType::Assembly or the name is not "$Struct$SetInventoryItem$" or "$Struct$SetInventoryAssembly$"
             *
             */
            explicit SetInventoryAssembly(const rw::oso::ObjectStoreAssembly& assembly);

            /**
             *@Parameters:
             *  - assembly: The assembly,which has fixed format, will be used to create the SetInventoryAssembly
             *@Methods:
             *  Constructor with assembly,if the assembly is invalid, it will throw a runtime_error
             *@Returns:
             *  void
             *@Throws:
             *  std::runtime_error: If the assembly is invalid
             *      - If the assembly name is not "$Struct$SetInventoryAssembly$"
             *      - If the _items has invalid type,which is not ItemType::Item or ItemType::Assembly or the name is not "$Struct$SetInventoryItem$" or "$Struct$SetInventoryAssembly$"
             *
             */
            explicit SetInventoryAssembly(rw::oso::ObjectStoreAssembly&& assembly);

            /**
             *@Parameters:
             *  - assembly: The SetInventoryAssembly, which will be used to create the SetInventoryAssembly
             *@Methods:
             *  Constructor with SetInventoryAssembly
             *@Returns:
             *  void
             */
            SetInventoryAssembly(const SetInventoryAssembly& assembly);

            /**
             *@Parameters:
             *  - assembly: The SetInventoryAssembly, which will be used to create the SetInventoryAssembly
             *@Methods:
             *  Constructor with SetInventoryAssembly
             *@Returns:
             *  void
             */
            SetInventoryAssembly(SetInventoryAssembly&& assembly) noexcept;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Constructor
             *@Returns:
             *  void
             */
            SetInventoryAssembly();

            ~SetInventoryAssembly() override = default;
        public:
            /**
             *@Parameters:
             *  - other: The SetInventoryAssembly, which will be used to assign to the current SetInventoryAssembly
             *@Methods:
             *  Copy assignment operator
             *@Returns: SetInventoryAssembly&
             *  - The reference of the current SetInventoryAssembly
             *@Throws:
             *  void
             */
            SetInventoryAssembly& operator=(const SetInventoryAssembly& other);

            /**
             *@Parameters:
             *  - other: The SetInventoryAssembly, which will be used to move to the current SetInventoryAssembly
             *@Methods:
             *  Move assignment operator
             *@Returns: SetInventoryAssembly&
             *  - The reference of the current SetInventoryAssembly
             *@Throws:
             *  void
             */
            SetInventoryAssembly& operator=(SetInventoryAssembly&& other) noexcept;
        public:

            /**
             *@Parameters:
             *  - other: The SetInventoryAssembly, which will be used to compare with the current SetInventoryAssembly
             *@Methods:
             *  Compare operator
             *@Returns: bool
             *  - true: If the current SetInventoryAssembly is equal to the other SetInventoryAssembly
             *  - false: If the current SetInventoryAssembly is not equal to the other SetInventoryAssembly
             *@Throws:
             *  void
             */
            bool operator==(const SetInventoryAssembly& other) const;

            /**
             *@Parameters:
             *  - other: The SetInventoryAssembly, which will be used to compare with the current SetInventoryAssembly
             *@Methods:
             *  Compare operator
             *@Returns: bool
             *  - true: If the current SetInventoryAssembly is not equal to the other SetInventoryAssembly
             *  - false: If the current SetInventoryAssembly is equal to the other SetInventoryAssembly
             *@Throws:
             *  void
             */
            bool operator!=(const SetInventoryAssembly& other) const;

        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the type of the object store
             *@Returns: ItemType::Assembly
             *  - ItemType::Assembly : The object is an assembly
             *@Throws:
             *  void
             */
            ItemType getObjectType() override { return ItemType::Assembly; }

        public:

            /**
             *@Parameters:
             *  - item: The SetInventoryItem, which will be appended to the current SetInventoryAssembly
             *@Methods:
             *  Append the SetInventoryItem to the current SetInventoryAssembly
             *@Returns:
             *  void
             *@Throws:
             *  void
             */
            void appendSetItem(const SetInventoryItem& item);

            /**
             *@Parameters:
             *  - item: The SetInventoryItem, which will be appended to the current SetInventoryAssembly
             *@Methods:
             *  Append the SetInventoryItem to the current SetInventoryAssembly
             *@Returns:
             *  void
             *@Throws:
             *  void
             */
            void appendSetItem(SetInventoryItem&& item);

            /**
             *@Parameters:
             *  - assembly: The SetInventoryAssembly, which will be appended to the current SetInventoryAssembly
             *@Methods:
             *  Append the SetInventoryAssembly to the current SetInventoryAssembly
             *@Returns:
             *  void
             *@Throws:
             *  void
             */
            void appendSetAssembly(const SetInventoryAssembly& assembly);

            /**
             *@Parameters:
             *  - assembly: The SetInventoryAssembly, which will be appended to the current SetInventoryAssembly
             *@Methods:
             *  Append the SetInventoryAssembly to the current SetInventoryAssembly
             *@Returns:
             *  void
             *@Throws:
             *  void
             */
            void appendSetAssembly(SetInventoryAssembly&& assembly);

        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the list of the items
             *@Returns: rw::oso::ObjectStoreAssembly
             *  - The list of the items
             *@Throws:
             *  void
             */
            std::vector<std::shared_ptr<SetInventoryCore>> getSetList();
        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Convert the SetInventoryAssembly to ObjectStoreAssembly
             *@Returns: rw::oso::ObjectStoreAssembly
             *  - The ObjectStoreAssembly which is converted from the SetInventoryAssembly
             *@Throws:
             *  void
             */
            operator rw::oso::ObjectStoreAssembly() const;
        };

        struct SetInventory
        {
            //Friend SetInventoryFactory to help create SetInventory
            friend struct SetInventoryFactory;
        private:
            /**
             * @brief The details of the assembly
             *
             * The details of the assembly are stored in the _items
             */
            std::vector<std::shared_ptr<SetInventoryCore>> _items;
        public:

            /**
             *@Parameters:
             *  - assembly: The assembly,which has fixed format, will be used to create the SetInventory
             *@Methods:
             *  Constructor with assembly,if the assembly is invalid, it will throw a runtime_error
             *@Returns:
             *  void
             *@Throws:
             *  std::runtime_error: If the assembly is invalid
             *      - If the assembly name is not "$Struct$SetInventory$"
             *      - If the _items has invalid type,which is not ItemType::Item or ItemType::Assembly or the name is not "$Struct$SetInventoryItem$" or "$Struct$SetInventoryAssembly$"
             *
             */
            explicit SetInventory(const rw::oso::ObjectStoreAssembly& assembly);

            /**
             *@Parameters:
             *  - assembly: The assembly,which has fixed format, will be used to create the SetInventory
             *@Methods:
             *  Constructor with assembly,if the assembly is invalid, it will throw a runtime_error
             *@Returns:
             *  void
             *@Throws:
             *  std::runtime_error: If the assembly is invalid
             *      - If the assembly name is not "$Struct$SetInventory$"
             *      - If the _items has invalid type,which is not ItemType::Item or ItemType::Assembly or the name is not "$Struct$SetInventoryItem$" or "$Struct$SetInventoryAssembly$"
             *
             */
            explicit SetInventory(rw::oso::ObjectStoreAssembly&& assembly);

            /**
             *@Parameters:
             *  - inventory: The SetInventory, which will be used to create the SetInventory
             *@Methods:
             *  Constructor with SetInventory
             *@Returns:
             *  void
             */
            SetInventory(const SetInventory& inventory);

            /**
             *@Parameters:
             *  - inventory: The SetInventory, which will be used to create the SetInventory
             *@Methods:
             *  Constructor with SetInventory
             *@Returns:
             *  void
             */
            SetInventory(SetInventory&& inventory) noexcept;

            SetInventory() = default;

            ~SetInventory() = default;

        public:

            /**
             *@Parameters:
             *  - other: The SetInventory, which will be used to assign to the current SetInventory
             *@Methods:
             *  Copy assignment operator
             *@Returns: SetInventory&
             *  - The reference of the current SetInventory
             *@Throws:
             *  void
             */
            SetInventory& operator=(const SetInventory& other);

            /**
             *@Parameters:
             *  - other: The SetInventory, which will be used to move to the current SetInventory
             *@Methods:
             *  Move assignment operator
             *@Returns: SetInventory&
             *  - The reference of the current SetInventory
             *@Throws:
             *  void
             */
            SetInventory& operator=(SetInventory&& other) noexcept;

        public:

            /**
             *@Parameters:
             *  - other: The SetInventory, which will be used to compare with the current SetInventory
             *@Methods:
             *  Compare operator
             *@Returns: bool
             *  - true: If the current SetInventory is equal to the other SetInventory
             *  - false: If the current SetInventory is not equal to the other SetInventory
             *@Throws:
             *  void
             */
            bool operator==(const SetInventory& other) const;

            /**
             *@Parameters:
             *  - other: The SetInventory, which will be used to compare with the current SetInventory
             *@Methods:
             *  Compare operator
             *@Returns: bool
             *  - true: If the current SetInventory is not equal to the other SetInventory
             *  - false: If the current SetInventory is equal to the other SetInventory
             *@Throws:
             *  void
             */
            bool operator!=(const SetInventory& other) const;

        public:
            /**
             * @brief The name of the object store
             *
             * The name representation of the instance object, which can serve as the node name in the class composition structure.
             */
            std::string name{ "Undefined" };

            /**
             * @brief The guid of the object store
             *
             * The guid representation of the instance object, which can serve as the node guid in the class composition structure.
             */
            std::string guid{ "Undefined" };

        public:
            /**
             * @brief The parent object of the object store
             *
             * Point to the parent object, if any
             */
            std::vector<std::shared_ptr<SetInventoryCore>> getSetList();

        public:
            /**
             *@Parameters:
             *  - item: The SetInventoryItem, which will be appended to the current SetInventory
             *@Methods:
             *  Append the SetInventoryItem to the current SetInventory
             *@Returns:
             *  void
             *@Throws:
             *  void
             */
            void appendSetItem(const SetInventoryItem& item);

            /**
             *@Parameters:
             *  - item: The SetInventoryItem, which will be appended to the current SetInventory
             *@Methods:
             *  Append the SetInventoryItem to the current SetInventory
             *@Returns:
             *  void
             *@Throws:
             *  void
             */
            void appendSetAssembly(const SetInventoryAssembly& assembly);
        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Convert the SetInventory to ObjectStoreAssembly
             *@Returns: rw::oso::ObjectStoreAssembly
             *  - The ObjectStoreAssembly which is converted from the SetInventory
             *@Throws:
             *  void
             */
            operator rw::oso::ObjectStoreAssembly() const;
        };

        /*------------------------------------------------------------------------------------
         *                          Inline implementation of SetInventoryItem
         *-----------------------------------------------------------------------------------*/

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
