#include "cfgr_RuntimeConfigLoader.h"

#include"oso_FileSave.h"
#include"oso_OrganizeStructure.h"
#include"oso_core.h"

namespace rw {
    namespace cfgr {
        RutimeConfig 
            RuntimeConfigLoader::load
            (const std::filesystem::path& filePath, bool & isLoad)
        {
            bool isLoadSuccess = false;
            oso::FileSave fileSave(rw::oso::OrganizeStructureType::XML_pugixml);
            auto config = fileSave.loadPtr(filePath);
            if (!config) {
                isLoad = false;
                return RutimeConfig();
            }
            auto result=RutimeConfig::toRuntimeConfig(*config);
            isLoad = true;
            return result;
        }

        void 
            RuntimeConfigLoader::save
            (const std::filesystem::path& filePath, const RutimeConfig& config)
        {
            oso::FileSave fileSave(rw::oso::OrganizeStructureType::XML_pugixml);
            fileSave.save(filePath, std::make_shared<oso::ObjectStoreAssembly>(RutimeConfig::toObjectStoreAssembly(config)));
        }
    }
}
