#ifndef DSL_CORE_H_
#define DSL_CORE_H_

#include<vector>
#include<memory>
#include<string>

namespace rw {
    namespace dsl {
        using String = std::string;

        template<typename T>
        using Vector = std::vector<T>;
        
        template<typename T>
        using Shared_ptr = std::shared_ptr<T>;

        template<typename T, typename... Args>
        inline Shared_ptr<T> make_shared(Args&&... args) {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
    
    }
}


#endif // !DSL_CORE_H_
