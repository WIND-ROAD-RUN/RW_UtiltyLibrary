#ifndef TDP_TRANSACTIONREQUEST_H_
#define TDP_TRANSACTIONREQUEST_H_

#include"tdp_TransactionHandle.h"

#include"oso_OrganizeStructure.h"

#include<string>

namespace rw {
    namespace tdp {
        using TransactionRequestType = oso::OrganizeStructureType;
        
        using TransactionRequestType = oso::OrganizeStructureType;

        class TransactionRequestBase {
        public:
            virtual ~TransactionRequestBase() = default;
            virtual std::string getRequest(std::shared_ptr<void> handle) = 0;
            virtual std::shared_ptr<void> analysisRequest(const std::string& s) = 0;
        };

        template <class TransactionClass, TransactionType type, TransactionRequestType requestType>
        class TransactionRequest;


        template <class TransactionClass, TransactionType type>
        class TransactionRequest<TransactionClass, type, TransactionRequestType::XML_pugixml> : public TransactionRequestBase {
        private:
            using TransactionHandle = TransactionHandle<TransactionClass, type>;
        public:
            std::string getRequest(std::shared_ptr<TransactionHandle> handle) override;

            std::shared_ptr<TransactionHandle> analysisRequest(const std::string& s) override;
        };


    }
}

#endif // !TDP_TRANSACTIONREQUEST_H_
