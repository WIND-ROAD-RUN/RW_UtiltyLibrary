#ifndef TDP_TRANSACTIONHANDLE_H_
#define TDP_TRANSACTIONHANDLE_H_

#include"oso_core.h"

#include<memory>
#include<string>

namespace rw {
    namespace tdp {
        
        enum class TransactionType {
            VERIFY,
        };

        template <class TransactionClass>
        class TransactionHandle;

        template <class TransactionClass>
        class TransactionHandle {
        public:
            explicit TransactionHandle(TransactionClass source, TransactionType type)
                :_transaction(std::make_shared<TransactionClass>(source)), _type(type)
            {
                _transactionAssembly = std::make_shared<oso::ObjectStoreAssembly>();
                _transactionAssembly->setName(rw::to_string(type));
                auto sourceToAssembly = std::make_shared<oso::ObjectStoreAssembly>(source);
                _transactionAssembly->addItem(sourceToAssembly);
            }
        private:
            TransactionType _type;
            std::shared_ptr<TransactionClass> _transaction;
            std::shared_ptr<oso::ObjectStoreAssembly> _transactionAssembly;
        public:
            std::shared_ptr<TransactionClass> getTransaction() const {
                return _transaction;
            }

            std::shared_ptr<oso::ObjectStoreAssembly> getTransactionAssembly() const {
                return _transactionAssembly;
            }

        public:
            bool vertify(std::shared_ptr<TransactionClass> _transaction);
        };

        template <class TransactionClass>
        inline bool TransactionHandle<TransactionClass>::vertify(std::shared_ptr<TransactionClass> _transaction)
        {
            return *(this->_transaction)==(*_transaction);
        }

    }

    std::string to_string(tdp::TransactionType type);

    tdp::TransactionType to_TransactionType(const std::string& s);
}

#endif // !TDP_TRANSACTIONHANDLE_H_
