#pragma once

#include"oso_IStorageStrategy.hpp"

namespace rw {
    namespace oso {
        class StorageStrategy_Sqlite final
            : public IStorageStrategy {
        public:

            void save(const ObjectStoreAssembly& assembly, const std::filesystem::path& fileName) override;

            std::shared_ptr<ObjectStoreAssembly> load(const std::filesystem::path& fileName) override;

            std::string getFormatString(const ObjectStoreAssembly& assembly) override;

        };
    } // namespace oso

} // namespace rw
