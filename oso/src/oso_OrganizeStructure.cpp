#include"oso_OrganizeStructure.h"

#include"oso_core.h"

#include<memory>
#include<sstream>
#include<string>

#include"pugixml.hpp"
#include"json/json.h"

namespace rw {

    namespace oso {
        void
            OrganizeStructure_pugixml::appendXmlNodeFromStoreItem
            (pugi::xml_node& node, const std::shared_ptr<ObjectStoreItem> source)
        {
            node.set_name("ObjectStoreItem");
            node.append_attribute("name").set_value(source->getName().c_str());

            if (source->getType() == ObjectDataItemStoreType::item_bool) {
                node.append_child("value").text().set(source->getValueAsBool() ? "true" : "false");
                node.append_child("type").text().set("bool");
            }
            else if (source->getType() == ObjectDataItemStoreType::item_double) {
                node.append_child("value").text().set(std::to_string(source->getValueAsDouble()).c_str());
                node.append_child("type").text().set("double");
            }
            else if (source->getType() == ObjectDataItemStoreType::item_int) {
                node.append_child("value").text().set(std::to_string(source->getValueAsInt()).c_str());
                node.append_child("type").text().set("int");
            }
            else if (source->getType() == ObjectDataItemStoreType::item_float) {
                node.append_child("value").text().set(std::to_string(source->getValueAsFloat()).c_str());
                node.append_child("type").text().set("float");
            }
            else if (source->getType() == ObjectDataItemStoreType::item_long) {
                node.append_child("value").text().set(std::to_string(source->getValueAsLong()).c_str());
                node.append_child("type").text().set("long");
            }
            else if (source->getType() == ObjectDataItemStoreType::item_string) {
                node.append_child("value").text().set(source->getValueAsString().c_str());
                node.append_child("type").text().set("string");
            }
            else {
                throw std::runtime_error("Unknown value type");
            }

        }

        void
            OrganizeStructure_pugixml::appendXmlNodeFromStoreAssembly
            (pugi::xml_node& node, const std::shared_ptr<ObjectStoreAssembly> source)
        {
            node.set_name("ObjectStoreAssembly");
            node.append_attribute("name").set_value(source->getName().c_str());

            auto children = node.append_child("children");
            for (const auto& item : source->getItems()) {
                if (auto objectAssembly = ObjectStoreCoreToAssembly(item)) {
                    auto child = children.append_child();
                    appendXmlNodeFromStoreAssembly(child, objectAssembly);
                }
                else if (auto objectItem = ObjectStoreCoreToItem(item)) {
                    auto child = children.append_child();
                    appendXmlNodeFromStoreItem(child, objectItem);
                }
                else {
                    throw std::runtime_error("Unknown type which is the superclass of objectStoreCore");
                }
            }
        }

        std::string
            OrganizeStructure_pugixml::getString
            (const std::shared_ptr<ObjectStoreItem> source)
        {
            pugi::xml_document doc;
            pugi::xml_node root = doc.append_child("root");
            appendXmlNodeFromStoreItem(root, source);

            std::ostringstream oss;
            root.print(oss);
            std::string result = oss.str();

            return result;
        }

        std::string
            OrganizeStructure_pugixml::getString
            (const std::shared_ptr<ObjectStoreAssembly> source)
        {
            pugi::xml_document doc;
            pugi::xml_node root = doc.append_child("root");
            appendXmlNodeFromStoreAssembly(root, source);

            std::ostringstream oss;
            root.print(oss);
            std::string result = oss.str();

            return result;
        }

        std::shared_ptr<ObjectStoreItem>
            OrganizeStructure_pugixml::getStoreItemFromString
            (const std::string& source)
        {
            pugi::xml_document doc;
            auto loadResult = doc.load_string(source.c_str());
            if (!loadResult) {
                throw std::runtime_error("Failed to load string to xml document");
            }

            auto result = std::make_shared<ObjectStoreItem>();
            auto root = doc.child("ObjectStoreItem");
            if (!root) {
                throw std::runtime_error("Failed to find root node");
            }

            result->setName(root.attribute("name").as_string());
            if (std::string(root.child("type").text().as_string()) == "bool") {
                result->setValueFromBool(std::string(root.child("value").text().as_string()) == "true");
            }
            else if (std::string(root.child("type").text().as_string()) == "double") {
                result->setValueFromDouble(root.child("value").text().as_double());
            }
            else if (std::string(root.child("type").text().as_string()) == "int") {
                result->setValueFromInt(root.child("value").text().as_int());
            }
            else if (std::string(root.child("type").text().as_string()) == "float") {
                result->setValueFromFloat(root.child("value").text().as_float());
            }
            else if (std::string(root.child("type").text().as_string()) == "long") {
                result->setValueFromLong(root.child("value").text().as_llong());
            }
            else if (std::string(root.child("type").text().as_string()) == "string") {
                result->setValueFromString(root.child("value").text().as_string());
            }
            else {
                throw std::runtime_error("Unknown type");
            }

            return result;
            
        }

        std::shared_ptr<ObjectStoreAssembly>
            OrganizeStructure_pugixml::getStoreAssemblyFromString
            (const std::string& source)
        {
            pugi::xml_document doc;
            auto loadResult = doc.load_string(source.c_str());
            if (!loadResult) {
                throw std::runtime_error("Failed to load string to xml document");
            }

            auto result = std::make_shared<ObjectStoreAssembly>();
            auto root = doc.child("ObjectStoreAssembly");
            if (!root) {
                throw std::runtime_error("Failed to find root node");
            }

            appendObjectStoreAssemblyFromXmlNode(result, root);

            return result;

        }

        void
            OrganizeStructure_pugixml::appendObjectStoreItemFromXmlNode
            (std::shared_ptr<ObjectStoreAssembly> target, const pugi::xml_node& node)
        {
            auto child = std::make_shared<ObjectStoreItem>();
            child->setName(node.attribute("name").as_string());
            if (std::string(node.child("type").text().as_string()) == "bool") {
                child->setValueFromBool(std::string(node.child("value").text().as_string()) == "true");
            }
            else if (std::string(node.child("type").text().as_string()) == "double") {
                child->setValueFromDouble(node.child("value").text().as_double());
            }
            else if (std::string(node.child("type").text().as_string()) == "int") {
                child->setValueFromInt(node.child("value").text().as_int());
            }
            else if (std::string(node.child("type").text().as_string()) == "float") {
                child->setValueFromFloat(node.child("value").text().as_float());
            }
            else if (std::string(node.child("type").text().as_string()) == "long") {
                child->setValueFromLong(node.child("value").text().as_llong());
            }
            else if (std::string(node.child("type").text().as_string()) == "string") {
                child->setValueFromString(node.child("value").text().as_string());
            }
            else {
                throw std::runtime_error("Unknown type");
            }

            target->addItem(child);
        }

        void
            OrganizeStructure_pugixml::appendObjectStoreAssemblyFromXmlNode
            (std::shared_ptr<ObjectStoreAssembly> target, const pugi::xml_node& node)
        {
            target->setName(node.attribute("name").as_string());
            for (const auto& child : node.child("children").children()) {
                if (std::string(child.name()) == "ObjectStoreItem") {
                    appendObjectStoreItemFromXmlNode(target, child);
                }
                else if (std::string(child.name()) == "ObjectStoreAssembly") {
                    auto children = std::make_shared<ObjectStoreAssembly>();
                    target->addItem(children);
                    appendObjectStoreAssemblyFromXmlNode(children, child);
                }
                else {
                    throw std::runtime_error("Unknown type");
                }
            }
        }
    }
}