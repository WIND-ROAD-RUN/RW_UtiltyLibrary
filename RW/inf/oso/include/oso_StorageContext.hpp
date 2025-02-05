#pragma once

#include"oso_core.h"
#include"oso_StorageStrategy.hpp"

namespace rw
{
    namespace oso
    {
        enum class StorageType
        {
            Sqlite,
            Text,
            Binary,
            Json,
            Xml,
            Csv,
            Excel,
            Odbc,
            Oracle,
            Postgres,
            Mysql,
            SqlServer,
            Access,
            Parquet,
            Avro,
            Arrow,
            Hdf5,
            Kafka,
            Redis,
            S3
        };

        class StorageContext
        {
        public:
            StorageContext(StorageType type, const std::string& path);
            void save(const ObjectStoreCore& object);
            std::shared_ptr<ObjectStoreCore> load(const std::filesystem::path& fileName);
            std::string getFormatString(const ObjectStoreCore& object);
        private:
            std::shared_ptr<IStorageStrategy> _strategy;
        };


    } // namespace oso
} // namespace rw