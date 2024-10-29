#include"oso_FileSave.h"

#include"oso_FileSave_private.h"

#include<pugixml.hpp>

#include<sstream>

namespace rw {
    namespace oso {
        FileSave::FileSave(OrganizeStructureType type)
        {
            switch (type)
            {
            case rw::oso::OrganizeStructureType::XML_pugixml:
                _strategy = std::make_shared<FileSave_pugixml>(type);
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
    }
}