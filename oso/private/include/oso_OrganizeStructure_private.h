#ifndef OSO_ORGANIZESTRUCTURE_PRIVATE_H_
#define OSO_ORGANIZESTRUCTURE_PRIVATE_H_

#include"oso_OrganizeStructure.h"

namespace pugi {
    class xml_node;
}

namespace rw {
	namespace oso
	{
        class OrganizeStructureFactory {
        public:
            static std::shared_ptr<OrganizeStructure_core> create(OrganizeStructureType type);
        };

        class OrganizeStructure_core {
        public:
            virtual std::string getString(const std::shared_ptr<ObjectStoreItem> source) = 0;
            virtual std::string getString(const std::shared_ptr<ObjectStoreAssembly> source) = 0;
            virtual std::vector<char> getBinary(const std::shared_ptr<ObjectStoreItem> source) = 0;
            virtual std::vector<char> getBinary(const std::shared_ptr<ObjectStoreAssembly> source) = 0;

            virtual std::shared_ptr<ObjectStoreItem> getStoreItemFromString(const std::string& source) = 0;
            virtual std::shared_ptr<ObjectStoreAssembly> getStoreAssemblyFromString(const std::string& source) = 0;
            virtual std::shared_ptr<ObjectStoreItem> getStoreItemFromBinary(const std::vector<char>& source) = 0;
            virtual std::shared_ptr<ObjectStoreAssembly> getStoreAssemblyFromBinary(const std::vector<char>& source) = 0;

        };

        class OrganizeStructure_pugixml
            : public OrganizeStructure_core {
        private:
            void appendXmlNodeFromStoreItem(pugi::xml_node& node, const std::shared_ptr<ObjectStoreItem> source);
            void appendXmlNodeFromStoreAssembly(pugi::xml_node& node, const std::shared_ptr<ObjectStoreAssembly> source);
        public:
            std::string getString(const std::shared_ptr<ObjectStoreItem> source) override;
            std::string getString(const std::shared_ptr<ObjectStoreAssembly> source) override;
            std::vector<char> getBinary(const std::shared_ptr<ObjectStoreItem> source) override;
            std::vector<char> getBinary(const std::shared_ptr<ObjectStoreAssembly> source) override;
        private:
            void appendObjectStoreItemFromXmlNode(std::shared_ptr<ObjectStoreAssembly> target, const pugi::xml_node& node);
            void appendObjectStoreAssemblyFromXmlNode(std::shared_ptr<ObjectStoreAssembly> target, const pugi::xml_node& node);
        public:
            std::shared_ptr<ObjectStoreItem> getStoreItemFromString(const std::string& source) override;
            std::shared_ptr<ObjectStoreAssembly> getStoreAssemblyFromString(const std::string& source) override;
            std::shared_ptr<ObjectStoreItem> getStoreItemFromBinary(const std::vector<char>& source) override;
            std::shared_ptr<ObjectStoreAssembly> getStoreAssemblyFromBinary(const std::vector<char>& source) override;

        };
	}

}

#endif // !OSO_ORGANIZESTRUCTURE_PRIVATE_H_
