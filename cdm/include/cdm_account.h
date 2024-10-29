#ifndef CDM_ACCOUNT_H_
#define CDM_ACCOUNT_H_

#include <string>

namespace rw {
    namespace oso {
        class ObjectStoreAssembly;
    }
}

namespace rw {
    namespace cdm {
        class Account {
        public:
            Account();
            Account(const std::string& name, const std::string& password);
            Account(const Account& account);
            Account& operator=(const Account& account);
            ~Account();
        public:
            void setName(const std::string& name);
            void setPassword(const std::string& password);
            std::string getName() const;
            std::string getPassword() const;

        private:
            std::string _name;
            std::string _password;

        public:
            operator rw::oso::ObjectStoreAssembly() const;
            bool operator==(const Account& account) const;
        };


    
    }
}

#endif // !CDM_ACCOUNT_H_
