#include"oso_FileSave_private.h"


#include<pugixml.hpp>
#include<sstream>

namespace rw {
    namespace oso {
        FileSave_pugixml::FileSave_pugixml(OrganizeStructureType type)
        {
            _organizeStructure = std::make_shared<OrganizeStructure>(type);
        }

        bool FileSave_pugixml::save(const std::filesystem::path& fileName, std::shared_ptr<ObjectStoreAssembly> assembly)
        {
            pugi::xml_document doc;
            auto str = _organizeStructure->getString(assembly);
            auto loadResult = doc.load_string(str.c_str());
            if (!loadResult) {
                return false;
            }
            auto saveResult = doc.save_file(fileName.string().c_str());

            return saveResult;
        }

        std::shared_ptr<ObjectStoreAssembly> FileSave_pugixml::load(const std::filesystem::path& fileName)
        {
            pugi::xml_document doc;
            auto loadResult = doc.load_file(fileName.string().c_str());
            if (!loadResult) {
                return nullptr;
            }
            auto root = doc.root();
            std::ostringstream oss;
            root.print(oss);
            std::string str = oss.str();
            auto assembly = _organizeStructure->getStoreAssemblyFromString(str);
            return assembly;
        }
    }

}