#include"oso_OrganizeStructure.h"

#include"oso_OrganizeStructure_private.h"

namespace rw {

    namespace oso {
        OrganizeStructure::OrganizeStructure(OrganizeStructureType type)
            :_core(OrganizeStructureFactory::create(type))
        {

        }

        OrganizeStructure::~OrganizeStructure(){
        
        }

        std::string
            OrganizeStructure::getString
            (const std::shared_ptr<ObjectStoreItem> source)
        {
            return _core->getString(source);
        }

        std::string
            OrganizeStructure::getString
            (const std::shared_ptr<ObjectStoreAssembly> source)
        {
            return _core->getString(source);
        }

        std::shared_ptr<ObjectStoreItem>
            OrganizeStructure::getStoreItemFromString
            (const std::string& source)
        {
            return _core->getStoreItemFromString(source);
        }

        std::shared_ptr<ObjectStoreAssembly>
            OrganizeStructure::getStoreAssemblyFromString
            (const std::string& source)
        {
            return _core->getStoreAssemblyFromString(source);
        }
        
    }
}