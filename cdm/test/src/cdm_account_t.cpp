#include"cdm_Account_t.h"

namespace cdm_account {
    TEST(AccountTest, setGetName) {
        string name = "name";
        Account account;
        account.setName(name);
        EXPECT_EQ(account.getName(), name);
    }

    TEST(AccountTest, setGetPassword) {
        string password = "password";
        Account account;
        account.setPassword(password);
        EXPECT_EQ(account.getPassword(), password);
    }

    TEST(AccountTest, copyConstructor) {
        Account account1;
        account1.setName("name");
        account1.setPassword("password");
        Account account2(account1);
        EXPECT_EQ(account1.getName(), account2.getName());
        EXPECT_EQ(account1.getPassword(), account2.getPassword());
    }

    TEST(AccountTest, assignmentOperator) {
        Account account1;
        account1.setName("name");
        account1.setPassword("password");
        Account account2;
        account2 = account1;
        EXPECT_EQ(account1.getName(), account2.getName());
        EXPECT_EQ(account1.getPassword(), account2.getPassword());
    }

    TEST(AccountTest, equalityOperator) {
        Account account1;
        account1.setName("name");
        account1.setPassword("password");
        Account account2;
        account2.setName("name");
        account2.setPassword("password");
        EXPECT_TRUE(account1 == account2);
    }

    TEST(AccountTest, inequalityOperator) {
        Account account1;
        account1.setName("name");
        account1.setPassword("password");
        Account account2;
        account2.setName("name");
        account2.setPassword("password");
        EXPECT_FALSE(account1 != account2);
    }

    TEST(AccountTest, objectStoreAssemblyOperator) {
        Account account;
        account.setName("testName");
        account.setPassword("testPassword");
        rw::oso::ObjectStoreAssembly objectStoreAssembly;
        objectStoreAssembly = account;
        EXPECT_EQ(objectStoreAssembly.getName(), "Account");
        EXPECT_EQ(oso::ObjectStoreCoreToItem(objectStoreAssembly.getItem("AccountName"))->getValueAsString(), "testName");
        EXPECT_EQ(oso::ObjectStoreCoreToItem(objectStoreAssembly.getItem("AccountPassword"))->getValueAsString(), "testPassword");
    }

    TEST(AccountTest, objectStoreAssemblyConstructor) {
        rw::oso::ObjectStoreAssembly objectStoreAssembly;
        objectStoreAssembly.setName("Account");
        oso::ObjectStoreItem nameItem;
        nameItem.setName("AccountName");
        nameItem.setValueFromString("testName");
        oso::ObjectStoreItem passwordItem;
        passwordItem.setName("AccountPassword");
        passwordItem.setValueFromString("testPassword");

        objectStoreAssembly.addItem(oso::makeObjectStoreItemSharedPtr(nameItem));
        objectStoreAssembly.addItem(oso::makeObjectStoreItemSharedPtr(passwordItem));

        Account account(objectStoreAssembly);
        EXPECT_EQ(account.getName(), "testName");
        EXPECT_EQ(account.getPassword(), "testPassword");
    }

}

