#ifndef TDP_TRANSACTIONREQUEST_H_
#define TDP_TRANSACTIONREQUEST_H_

#include"tdp_TransactionHandle.h"

#include"oso_OrganizeStructure.h"

#include<string>

namespace rw {
    namespace tdp {
        using TransactionRequestType = oso::OrganizeStructureType;

        template <class TransactionClass, TransactionRequestType requestType >
        class TransactionRequest_base {
            virtual std::string getRequest(std::shared_ptr<TransactionHandle<TransactionClass>> handle)=0;

            virtual std::shared_ptr<TransactionHandle<TransactionClass>> analysisRequest(const std::string& s) = 0;

        };

        template <class TransactionClass, TransactionRequestType requestType= TransactionRequestType::XML_pugixml>
        class TransactionRequest;


        template <class TransactionClass>
        class TransactionRequest<TransactionClass ,TransactionRequestType::XML_pugixml> 
            : public TransactionRequest_base<TransactionClass, TransactionRequestType::XML_pugixml>
        {
        private:
            oso::OrganizeStructure _organizeStructure;
        public:
            TransactionRequest();
        public:
            std::string getRequest(std::shared_ptr<TransactionHandle<TransactionClass>> handle) override;

            std::shared_ptr<TransactionHandle<TransactionClass>> analysisRequest(const std::string& s) override;
        };

        template <class TransactionClass>
        inline 
        TransactionRequest<TransactionClass, TransactionRequestType::XML_pugixml>::
        TransactionRequest()
        :_organizeStructure(TransactionRequestType::XML_pugixml)
        {
        }

        template <class TransactionClass>
        inline std::string 
        TransactionRequest<TransactionClass, TransactionRequestType::XML_pugixml>::getRequest
        (std::shared_ptr<TransactionHandle<TransactionClass>> handle)
        {
            return _organizeStructure.getString(handle->getTransactionAssembly());
        }
        
        template <class TransactionClass>
        inline std::shared_ptr<TransactionHandle<TransactionClass>> 
        TransactionRequest<TransactionClass, TransactionRequestType::XML_pugixml>::analysisRequest(const std::string &s)
        {
            auto assembly = _organizeStructure.getStoreAssemblyFromString(s);
            auto type = rw::to_TransactionType(assembly.getName());


            auto context=ObjectStoreCoreToAssembly(assembly.getItems()[0]);

            auto a = TransactionClass(*context);
            auto result = std::make_shared<TransactionHandle<TransactionClass>>(a, type);

            return result;
            
        }
    }
}

#endif // !TDP_TRANSACTIONREQUEST_H_
