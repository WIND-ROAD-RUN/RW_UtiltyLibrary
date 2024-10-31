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

        template <class TransactionClass,TransactionType type>
        class TransactionHandle;

        template <class TransactionClass>
        class TransactionHandle<TransactionClass, TransactionType::VERIFY> {
        public:
            explicit TransactionHandle(TransactionClass source)
            {
                _transaction = std::make_shared<oso::ObjectStoreAssembly>();
                _transaction->setName(std::to_string(TransactionType::VERIFY));
                auto sourceToAssembly = std::make_shared<oso::ObjectStoreAssembly>(source);
                _transaction->addItem(sourceToAssembly);
            }
        private:
            std::shared_ptr<oso::ObjectStoreAssembly> _transaction;
        public:
            std::shared_ptr<TransactionClass> getTransaction() const {
                return _transaction;
            }

        public:
            bool vertify(std::shared_ptr<TransactionClass> _transaction);

        };

    }

}

#endif // !TDP_TRANSACTIONHANDLE_H_
