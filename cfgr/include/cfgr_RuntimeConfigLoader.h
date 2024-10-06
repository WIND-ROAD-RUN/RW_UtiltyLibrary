#ifndef CFGR_RUNTIMECONFIGLOADER
#define CFGR_RUNTIMECONFIGLOADER

#include"cfgr_RuntimeConfig.h"

#include<string>
#include<fileSystem>

namespace rw {
    namespace cfgr {
        class RuntimeConfigLoader {
        public:
            static RutimeConfig load(const std::filesystem::path & filePath, bool & isLoad);
            static void save(const std::filesystem::path& filePath, const RutimeConfig& config);
        };
    
    }

}

#endif // !CFGR_RUNTIMECONFIGLOADER
