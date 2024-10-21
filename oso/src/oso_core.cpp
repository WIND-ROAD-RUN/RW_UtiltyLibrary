#include"oso_core.h"

#include<cassert>
#include<algorithm>

namespace rw {
    namespace oso {
        ObjectStoreCore::ObjectStoreCore() {

        }

        ObjectStoreItem::ObjectStoreItem() {

        }

        void 
            ObjectStoreItem::setValueFromString
            (const std::string& value)
        {
            _value = value;
            _type = ObjectDataItemStoreType::item_string;
        }

        void 
            ObjectStoreItem::setValueFromInt
            (int value)
        {
            _value = std::to_string(value);
            _type = ObjectDataItemStoreType::item_int;
        }

        void 
            ObjectStoreItem::setValueFromLong
            (long value)
        {
            _value = std::to_string(value);
            _type = ObjectDataItemStoreType::item_long;
        }

        void 
            ObjectStoreItem::setValueFromFloat
            (float value)
        {
            _value = std::to_string(value);
            _type = ObjectDataItemStoreType::item_float;
        }

        void 
            ObjectStoreItem::setValueFromDouble
            (double value)
        {
            _value = std::to_string(value);
            _type = ObjectDataItemStoreType::item_double;
        }

        void 
            ObjectStoreItem::setValueFromBool
            (bool value)
        {
            _value = value ? "true" : "false";
            _type = ObjectDataItemStoreType::item_bool;
        }

        std::string 
            ObjectStoreItem::getValueAsString
            () const
        {
            assert(_type == ObjectDataItemStoreType::item_string);
            return _value;
        }

        int 
            ObjectStoreItem::getValueAsInt
            () const
        {
            assert(_type == ObjectDataItemStoreType::item_int);
            return std::stoi(_value);
        }

        long 
            ObjectStoreItem::getValueAsLong
            () const
        {
            assert(_type == ObjectDataItemStoreType::item_long);
            return std::stol(_value);
        }

        float 
            ObjectStoreItem::getValueAsFloat
            () const
        {
            assert(_type == ObjectDataItemStoreType::item_float);
            return std::stof(_value);
        }

        double 
            ObjectStoreItem::getValueAsDouble
            () const
        {
            assert(_type == ObjectDataItemStoreType::item_double);
            return std::stod(_value);
        }

        bool 
            ObjectStoreItem::getValueAsBool
            () const
        {
            assert(_type == ObjectDataItemStoreType::item_bool);
            return _value == "true";
        }

        ObjectDataItemStoreType 
            ObjectStoreItem::getType
            () const
        {
            return _type;
        }

        std::string 
            ObjectStoreItem::getTypeString
            () const
        {
            switch (_type)
            {   
            case rw::oso::ObjectDataItemStoreType::item_string:
                return "string";
                break;
            case rw::oso::ObjectDataItemStoreType::item_int:
                return "int";
                break;
            case rw::oso::ObjectDataItemStoreType::item_float:
                return "float";
                break;
            case rw::oso::ObjectDataItemStoreType::item_double:
                return "double";
                break;
            case rw::oso::ObjectDataItemStoreType::item_bool:
                return "bool";
                break;
            case rw::oso::ObjectDataItemStoreType::item_long:
                return "long";
                break;
            default:
                return "undefined";
                break;
            }
        }

        void 
            ObjectStoreItem::print
            (std::ostream& os)
        {
            ObjectStoreCore::print(os);
            os << "*" << this->getName() << ": " << _value << " (" << this->getTypeString() << ")" << std::endl;
        }

        ObjectStoreAssembly::ObjectStoreAssembly() {

        }

        void 
            ObjectStoreAssembly::addItem
            (std::shared_ptr<ObjectStoreCore> item) {
            item->addLevel();
            m_items.push_back(item);
            item->parent = this;
        }

        void ObjectStoreAssembly::addItem(ObjectStoreAssembly&& assembly)
        {
            assembly.addLevel();
            m_items.push_back(std::make_shared<ObjectStoreAssembly>(std::move(assembly)));
            m_items.back()->parent = this;
        }

        void ObjectStoreAssembly::addItem(ObjectStoreItem&& item)
        {
            item.addLevel();
            m_items.push_back(std::make_shared<ObjectStoreItem>(std::move(item)));
            m_items.back()->parent = this;
        }

        void 
            ObjectStoreAssembly::removeItem
            (std::shared_ptr<ObjectStoreCore> item) {
            item->subLevel();
            m_items.erase(std::remove_if(m_items.begin(), m_items.end(),
                [&item](const std::shared_ptr<ObjectStoreCore>& i) { return i == item; }), m_items.end());
            item->parent = nullptr;
        }

        void 
            ObjectStoreAssembly::print
            (std::ostream& os)
        {
            ObjectStoreCore::print(os);
            os << "-" << this->getName() << "" << std::endl;
            for (auto& item : m_items) {
                item->print(os);
            }
        }

        void ObjectStoreAssembly::addLevel()
        {
            level++;
            for (auto& item : m_items) {
                item->addLevel();
            }
        }

        void ObjectStoreAssembly::subLevel()
        {
            level--;
            for (auto& item : m_items) {
                item->subLevel();
            }
        }

        std::shared_ptr<ObjectStoreCore> ObjectStoreAssembly::operator[](const size_type& i)
        {
            return m_items[i];
        }

        const std::shared_ptr<ObjectStoreCore> ObjectStoreAssembly::at(const size_type& i) const
        {
            return m_items.at(i);
        }

        std::vector<std::shared_ptr<ObjectStoreCore>>
            ObjectStoreAssembly::getItems
            () const
        {
            return m_items;
        }

        const std::shared_ptr<ObjectStoreCore> 
            ObjectStoreAssembly::getItem
            (const std::string& name) const
        {
            for (auto& item : m_items) {
                if (item->getName() == name) {
                    return item;
                }
            }
            return nullptr;
        }

        void 
            ObjectStoreCore::setName
            (const std::string& name) {
            m_name = name;
        }

        std::string 
            ObjectStoreCore::getName() const {
            return m_name;
        }

        void ObjectStoreCore::print(std::ostream& os)
        {
            for (size_t i = 0; i < level; ++i) {
                os << "  ";
            }
        }

}
}
