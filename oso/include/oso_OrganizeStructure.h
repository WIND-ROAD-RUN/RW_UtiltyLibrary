#ifndef OSO_ORGANIZESTRUCTURE_H_
#define OSO_ORGANIZESTRUCTURE_H_

#include<string>
#include<memory>

namespace rw {
    namespace oso {
        class ObjectStoreItem;
        class ObjectStoreAssembly;
    }
}

namespace pugi {
    class xml_node;
}

namespace rw {
    namespace oso {

        enum class  OrganizeStructureType {
            XML_pugixml,
            JSON_jsonCpp,
        };

        class OrganizeStructure_core {
        public:
            virtual std::string getString(const std::shared_ptr<ObjectStoreItem> source) = 0;
            virtual std::string getString(const std::shared_ptr<ObjectStoreAssembly> source) = 0;

            virtual std::shared_ptr<ObjectStoreItem> getStoreItemFromString(const std::string& source) = 0;
            virtual std::shared_ptr<ObjectStoreAssembly> getStoreAssemblyFromString(const std::string& source) = 0;

        };

        class OrganizeStructure
            :public OrganizeStructure_core {
        public:
            explicit OrganizeStructure(OrganizeStructureType type);
            ~OrganizeStructure();
        private:
            std::shared_ptr<OrganizeStructure_core> _core;
        public:
            std::string getString(const std::shared_ptr<ObjectStoreItem> source) override;
            std::string getString(const std::shared_ptr<ObjectStoreAssembly> source) override;

            std::shared_ptr<ObjectStoreItem> getStoreItemFromString(const std::string& source) override;
            std::shared_ptr<ObjectStoreAssembly> getStoreAssemblyFromString(const std::string& source) override;
        };

    }
}


#endif // !oso_organizeStructure_H_
