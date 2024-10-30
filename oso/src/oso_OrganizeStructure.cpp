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

        std::string OrganizeStructure::getString(const ObjectStoreItem &source)
        {
            auto result = this->getString(std::make_shared<ObjectStoreItem>(source));
            return result;
        }

        std::string
            OrganizeStructure::getString
            (const std::shared_ptr<ObjectStoreAssembly> source)
        {
            return _core->getString(source);
        }

        std::string OrganizeStructure::getString(const ObjectStoreAssembly &source)
        {
            auto result = this->getString(std::make_shared<ObjectStoreAssembly>(source));
            return result;
        }

        std::shared_ptr<ObjectStoreItem>
            OrganizeStructure::getStoreItemPtrFromString
            (const std::string& source)
        {
            return _core->getStoreItemFromString(source);
        }

        ObjectStoreItem OrganizeStructure::getStoreItemFromString(const std::string &source)
        {
            auto result = this->getStoreItemPtrFromString(source);
            return *result;
        }

        std::shared_ptr<ObjectStoreAssembly>
            OrganizeStructure::getStoreAssemblyPtrFromString
            (const std::string& source)
        {
            return _core->getStoreAssemblyFromString(source);
        }

        ObjectStoreAssembly OrganizeStructure::getStoreAssemblyFromString(const std::string &source)
        {
            auto result = this->getStoreAssemblyPtrFromString(source);
            return *result;
        }
    }
}