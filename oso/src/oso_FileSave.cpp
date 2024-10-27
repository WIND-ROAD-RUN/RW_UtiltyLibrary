#include"oso_FileSave.h"

#include"oso_core.h"
#include"oso_OrganizeStructure.h"

#include<pugixml.hpp>

#include<sstream>

namespace rw {
    namespace oso {
        FileSave::FileSave(OrganizeStructureType type)
        {
            switch (type)
            {
            case rw::oso::OrganizeStructureType::XML_pugixml:
                _strategy = std::make_shared<FileSaveRefactor_pugixml>(type);
                break;
            default:
                throw std::runtime_error("FileSave::FileSave: unknown OrganizeStructureType");
                break;
            }
        }

        FileSave::~FileSave()
        {

        }

        bool FileSave::save(const std::filesystem::path& fileName, std::shared_ptr<ObjectStoreAssembly> assembly)
        {
            auto result=_strategy->save(fileName, assembly);
            return result;
        }
        std::shared_ptr<ObjectStoreAssembly> FileSave::load(const std::filesystem::path& fileName)
        {
            auto result = _strategy->load(fileName);
            return result;
        }

        FileSaveRefactor_pugixml::FileSaveRefactor_pugixml(OrganizeStructureType type)
        {
            _organizeStructure = std::make_shared<OrganizeStructure>(type);
        }

        bool FileSaveRefactor_pugixml::save(const std::filesystem::path& fileName, std::shared_ptr<ObjectStoreAssembly> assembly)
        {
            pugi::xml_document doc;
            auto str=_organizeStructure->getString(assembly);
            auto loadResult = doc.load_string(str.c_str());
            if (!loadResult) {
                return false;
            }
            auto saveResult = doc.save_file(fileName.string().c_str());

            return saveResult;
        }

        std::shared_ptr<ObjectStoreAssembly> FileSaveRefactor_pugixml::load(const std::filesystem::path& fileName)
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