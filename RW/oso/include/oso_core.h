#ifndef OSO_CORE_H_
#define OSO_CORE_H_

#include<vector>
#include<memory>
#include<string>
#include<iostream>

namespace rw {
    namespace oso {
        class ObjectStoreCore {
        private:
            /// Class member std:: string m_name of class ObjectiStoreCore
            /// 
            /// This is a private member of class ObjectStoreCore.Means the name representation of the instance object, which can serve as the node name in the class composition structure.
            std::string m_name;

        public:
            //Parameters:
            //      name:The name you are going to set as
            // 
            //setName: Set the name of the object store
            void setName(const std::string& name);

            //Get the name of the object store
            std::string getName() const;

        public:
            // Point to the parent object, if any
            ObjectStoreCore* parent{ nullptr };

        public:
            // This variable is used to represent the hierarchy to which the class instance  in the composite instance.
            //
            //Supplement:
            //      Hierarchical structure:He represents the level of the instance in the object tree, for example, if he has a parent object and the parent object has no parent bject, then his level is 1
            size_t level{ 0 };

            //Increase the hierarchy of class instances
            virtual void addLevel() {
                level++;
            }

            //Reduce the hierarchy of class instances
            virtual void subLevel() {
                if (level == 0) {
                    return;
                }
                level--;
            }

        public:
            //Get the type of the object store
            virtual std::string getStoreType() const {
                return "core";
            }


        public:
            ObjectStoreCore()=default;

            ObjectStoreCore(std::vector<char> binary);

            virtual ~ObjectStoreCore() = default;

        public:
            //Parameters:
            //      os: Output stream
            //Print the object tree of the Object Store with the current instance as the root node
            virtual void print(std::ostream& os);

        public:
            virtual bool operator==(const ObjectStoreCore& other) const;

            virtual bool operator!=(const ObjectStoreCore& other) const;

        public:
            //virtual std::vector<char> getBinary();
        };

        //The type of data stored in the Object Data Item class
        enum  class ObjectDataItemStoreType
        {
            item_string,
            item_int,
            item_long,
            item_float,
            item_double,
            item_bool
        };

        //Composite object, which can combine classes based on Object Store Core
        class ObjectStoreItem
            :public ObjectStoreCore {
        private:
            //The value of the object data item
            std::string _value{ "0" };

            //The type of data stored in the object data item
            ObjectDataItemStoreType _type{ ObjectDataItemStoreType::item_int };
        public:
            ObjectStoreItem()=default;

            ObjectStoreItem(std::vector<char> binary);

            virtual ~ObjectStoreItem() = default;

        public:
            //Parameters:
            //      value: The value you are going to set as
            void setValueFromString(const std::string& value);

            //Parameters:
            //      value: The value you are going to set as
            void setValueFromInt(int value);

            //Parameters:
            //      value: The value you are going to set as
            void setValueFromLong(long value);

            //Parameters:
            //      value: The value you are going to set as
            void setValueFromFloat(float value);

            //Parameters:
            //      value: The value you are going to set as
            void setValueFromDouble(double value);

            //Parameters:
            //      value: The value you are going to set as
            void setValueFromBool(bool value);

        public:
            //getValueAsString::Get the value of the object data item as a string
            std::string getValueAsString() const;

            //getValueAsInt::Get the value of the object data item as an integer
            int getValueAsInt() const;

            //getValueAsLong::Get the value of the object data item as a long integer
            long getValueAsLong() const;

            //getValueAsFloat::Get the value of the object data item as a floating point number
            float getValueAsFloat() const;

            //getValueAsDouble::Get the value of the object data item as a double precision floating point number
            double getValueAsDouble() const;

            //getValueAsBool::Get the value of the object data item as a boolean value
            bool getValueAsBool() const;

            //getType::Get the type of data stored in the object data item
            ObjectDataItemStoreType getType() const;

            //getTypeString::Get the type of data stored in the object data item as a string
            std::string getTypeString() const;

        public:
            // Inheriting through Object Store Core

            //Parameters:
            //      os: Output stream
            //Print the object tree of the Object Store with the current instance as the root node
            void print(std::ostream& os) override;

            //Get the type of the object store
            virtual std::string getStoreType() const override {
                return "item";
            }

        public:
            bool equlas(const ObjectStoreItem& other) const;

            bool operator==(const ObjectStoreCore& other) const override;

            bool operator!=(const ObjectStoreCore& other) const override;

            bool operator==(const ObjectStoreItem& other) const;

            bool operator!=(const ObjectStoreItem& other)const;

        public:
            //std::vector<char> getBinary()override;

        };

        //
        class ObjectStoreAssembly
            :public ObjectStoreCore {
        private:
            //Store sub objects, which can be Object Store Assembly and Object Store Item
            std::vector<std::shared_ptr<ObjectStoreCore>> m_items;

        public:
            ObjectStoreAssembly()=default;

            ObjectStoreAssembly(std::vector<char> binary);

            virtual ~ObjectStoreAssembly() = default;

        public:
            //Parameters:
            //      item: The item you are going to add
            //
            //addItem: Add an item to the object store
            void addItem(std::shared_ptr<ObjectStoreCore> item);

            //Parameters:
            //      assembly: The assembly you are going to add
            //
            //addItem: Add an assembly to the object store
            void addItem(ObjectStoreAssembly&& assembly);

            //Parameters:
            //      item: The item you are going to add
            //
            //addItem: Add an item to the object store
            void addItem(ObjectStoreItem&& item);

            //Parameters:
            //      name: The name of the item you are going to remove
            //
            //removeItem: Remove an item from the object store
            void removeItem(std::shared_ptr<ObjectStoreCore> item);

        public:
            using size_type = std::vector<std::shared_ptr<ObjectStoreCore>>::size_type;

            //Parameters:
            //      i: The index of the item you are going to get
            //
            //operator[]: Get the item by index
            std::shared_ptr<ObjectStoreCore> operator[](const size_type& i);

            //Parameters:
            //      i: The index of the item you are going to get
            //
            //at: Get the item by index
            const std::shared_ptr<ObjectStoreCore> at(const size_type& i)const;

        public:
            //Get the number of items in the object store
            std::vector<std::shared_ptr<ObjectStoreCore>> getItems() const;

            //Parameters:
            //      name: The name of the item you are going to get
            //
            //getItem: Get the item by name if it exists, otherwise return nullptr
            const std::shared_ptr<ObjectStoreCore> getItem(const std::string& name) const;

        public:
            //Parameters:
            //      os: Output stream
            // print:Inheriting through Object Store Core
            void print(std::ostream& os) override;

            virtual void addLevel() override;

            virtual void subLevel() override;

            virtual std::string getStoreType() const override {
                return "assembly";
            }
        public:
            bool equlas(const ObjectStoreAssembly& other) const;

            bool operator==(const ObjectStoreCore& other) const override;

            bool operator!=(const ObjectStoreCore& other)const override;

            bool operator==(const ObjectStoreAssembly& other) const;

            bool operator!=(const ObjectStoreAssembly& other)const;

        public:
            //std::vector<char> getBinary() override;
        };

        inline std::shared_ptr<ObjectStoreAssembly>
            makeObjectStoreAssemblySharedPtr
            (const ObjectStoreAssembly& assembly) {
            return std::make_shared<ObjectStoreAssembly>(assembly);
        }

        inline std::shared_ptr<ObjectStoreItem>
            makeObjectStoreItemSharedPtr
            (const ObjectStoreItem& item) {
            return std::make_shared<ObjectStoreItem>(item);
        }

        inline std::shared_ptr<ObjectStoreAssembly>
            ObjectStoreCoreToAssembly
            (std::shared_ptr<ObjectStoreCore> core) {
            std::shared_ptr<ObjectStoreAssembly> assembly = std::dynamic_pointer_cast<ObjectStoreAssembly>(core);

            return assembly;
        }

        inline std::shared_ptr<ObjectStoreItem>
            ObjectStoreCoreToItem
            (std::shared_ptr<ObjectStoreCore> core) {
            std::shared_ptr<ObjectStoreItem> item = std::dynamic_pointer_cast<ObjectStoreItem>(core);

            return item;
        }

    }

}


#endif // !OSO_CORE_H_
