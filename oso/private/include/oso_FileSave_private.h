#ifndef OSO_FILESAVE_PRIVATE_H_
#define OSO_FILESAVE_PRIVATE_H_

#include"oso_FileSave.h"

namespace rw {
    namespace oso {
        class FileSave_strategy {
        public:
            virtual ~FileSave_strategy() = default;

            virtual bool save(const std::filesystem::path& fileName, std::shared_ptr<ObjectStoreAssembly> assembly) = 0;

            virtual std::shared_ptr<ObjectStoreAssembly> load(const std::filesystem::path& fileName) = 0;
        };

        class FileSave_pugixml
            :public FileSave_strategy {
        private:
            std::shared_ptr<OrganizeStructure> _organizeStructure;
        public:
            explicit FileSave_pugixml(OrganizeStructureType type);
            ~FileSave_pugixml() = default;
        public:
            // 通过 FileSave_strategy 继承
            bool save(const std::filesystem::path& fileName, std::shared_ptr<ObjectStoreAssembly> assembly) override;

            std::shared_ptr<ObjectStoreAssembly> load(const std::filesystem::path& fileName) override;
        };
    }

}


#endif // !OSO_FILESAVE_PRIVATE_H_
