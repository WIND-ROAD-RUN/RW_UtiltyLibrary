#include"oso_StorageContext.hpp"

#include"oso_StorageStrategy_xml.hpp"

namespace rw
{
    namespace oso
    {
        StorageContext::StorageContext(StorageType type)
        {
            switch (type)
            {
            case StorageType::Xml:
                _strategy = std::make_shared<StorageStrategy_Xml>();
                break;
            default:
                break;
            }
        }

        void StorageContext::save(const ObjectStoreAssembly& assembly, const std::filesystem::path& fileName) const
        {
            _strategy->save(assembly, fileName);
        }

        void StorageContext::save(const ObjectStoreAssembly& assembly, const std::string& fileName) const
        {
            _strategy->save(assembly, fileName);
        }

        std::shared_ptr<ObjectStoreAssembly> StorageContext::load(const std::filesystem::path& fileName) const
        {
            return _strategy->load(fileName);
        }

        std::shared_ptr<ObjectStoreAssembly> StorageContext::load(const std::string& fileName) const
        {
            return _strategy->load(fileName);
        }

        std::string StorageContext::getFormatString(const ObjectStoreAssembly& assembly) const
        {
            return _strategy->getFormatString(assembly);
        }
    } // namespace oso
} // namespace rw