#include"tdp_TransactionRequest_t.h"

namespace rw {
    namespace tdp {
        TEST(TransactionRequestTest, TransactionRequestTest1)
        {
            cdm::Account account;
            account.setName("test");
            account.setPassword("1234567890");
            
            std::shared_ptr<TransactionHandle<cdm::Account>> handle = std::make_shared<TransactionHandle<cdm::Account>>(account, TransactionType::VERIFY);
            TransactionRequest<cdm::Account,tdp::TransactionRequestType::XML_pugixml> request;
            std::string s = request.getRequest(handle);
            std::shared_ptr<TransactionHandle<cdm::Account>> handle2 = request.analysisRequest(s);

            EXPECT_EQ(*(handle->getTransaction()), *(handle2->getTransaction()));
            EXPECT_EQ(*(handle->getTransactionAssembly()), *(handle2->getTransactionAssembly()));
            EXPECT_TRUE(handle->vertify(handle2->getTransaction()));


        }
 
    }
}