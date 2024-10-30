#include"cdm_account.h"

#include"oso_core.h"

#include<string>
#include<memory>

namespace rw {
    namespace cdm {
        Account::Account(const rw::oso::ObjectStoreAssembly &assembly)
        {
            auto isAccountAssembly = assembly.getName();
            if (isAccountAssembly != "Account")
            {
                throw std::runtime_error("Assembly is not Account");
            }
            auto name = oso::ObjectStoreCoreToItem(assembly.getItem("AccountName"));

            if (!name) {
                throw std::runtime_error("AccountName is not found");
            }

            auto password = oso::ObjectStoreCoreToItem(assembly.getItem("AccountPassword"));

            if (!password) {
                throw std::runtime_error("AccountPassword is not found");
            }

            _name = name->getValueAsString();
            _password = password->getValueAsString();
        }

        Account::Account(std::string name, std::string password)
            :_name(name), _password(password)
        {

        }

        Account::Account(const Account &account)
            :_name(account._name), _password(account._password)
        {

        }

        Account& Account::operator=(const Account& account)
        {
            if (this != &account)
            {
                _name = account._name;
                _password = account._password;
            }
            return *this;
        }

        void Account::setName(const std::string &name)
        {
            _name = name;
        }

        void Account::setPassword(const std::string &password)
        {
            _password = password;
        }

        std::string Account::getName() const
        {
            return _name;
        }

        std::string Account::getPassword() const
        {
            return  _password;
        }

        Account::operator rw::oso::ObjectStoreAssembly() const
        {
            rw::oso::ObjectStoreAssembly assembly;
            assembly.setName("Account");

            auto name=std::make_shared<oso::ObjectStoreItem>();
            name->setValueFromString(_name);
            name->setName("AccountName");
            assembly.addItem(name);

            auto password = std::make_shared<oso::ObjectStoreItem>();
            password->setValueFromString(_password);
            password->setName("AccountPassword");
            assembly.addItem(password);

            return assembly;
        }

        bool Account::operator==(const Account &account) const
        {
            return this->_name == account._name;
        }

        bool Account::operator!=(const Account &account) const
        {
            return !((*this)==account);
        }
    }
}