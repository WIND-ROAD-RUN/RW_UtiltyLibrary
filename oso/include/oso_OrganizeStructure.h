#ifndef OSO_ORGANIZESTRUCTURE_H_
#define OSO_ORGANIZESTRUCTURE_H_

#include<string>
#include<memory>

#include"oso_core.h"

namespace rw {
    namespace oso
    {
        class OrganizeStructure_core;
    }
}

namespace rw {
    namespace oso {

        enum class  OrganizeStructureType {
            XML_pugixml,
            JSON_jsonCpp,
        };

        class OrganizeStructure{
        public:
            explicit OrganizeStructure(OrganizeStructureType type);
            ~OrganizeStructure();
        private:
            std::shared_ptr<OrganizeStructure_core> _core;
        public:
            std::string getString(const std::shared_ptr<ObjectStoreItem> source);
            std::string getString(const std::shared_ptr<ObjectStoreAssembly> source);

            std::shared_ptr<ObjectStoreItem> getStoreItemFromString(const std::string& source);
            std::shared_ptr<ObjectStoreAssembly> getStoreAssemblyFromString(const std::string& source);
        };

    }
}


#endif // !oso_organizeStructure_H_
