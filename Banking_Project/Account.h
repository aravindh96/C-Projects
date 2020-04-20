//"Account.h" contains variable and functions declarations
// for the Account class.

#ifndef __ACCOUNT_H_INCLUDED__
#define __ACCOUNT_H_INCLUDED__
#include <iostream>
class Account{
    private:
        int account_number_;
        std::string account_name_;
        char account_type_;
        long long int account_balance_;

    public:
        int GetAccountNumber();
        void SetAccountNumber(int number);

        std::string GetAccountName();
        void SetAccountName(std::string name);

        char GetAccountType();
        void SetAccountType(char type);

        long long int GetAccountBalance();
        void SetAccountBalance(long long int balance);

        void ShowAccountStatus();
};

#endif