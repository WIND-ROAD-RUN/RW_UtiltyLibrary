#ifndef OSO_FILESAVE_H_
#define OSO_FILESAVE_H_

#include"oso_OrganizeStructure.h"

#include<string>
#include<memory>
#include<filesystem>

namespace rw {
    namespace oso {
        class FileSave_strategy;
    }
}

namespace rw {
    namespace oso {
        class FileSave
            {
        public:
            FileSave(OrganizeStructureType type);
            ~FileSave();
        private:
            std::shared_ptr<FileSave_strategy> _strategy;
        public:
            bool save(const std::filesystem::path& fileName, std::shared_ptr<ObjectStoreAssembly> assembly);

            std::shared_ptr<ObjectStoreAssembly> load(const std::filesystem::path& fileName);

        };
    }

}

#endif // !OSO_FILESAVE_H_
