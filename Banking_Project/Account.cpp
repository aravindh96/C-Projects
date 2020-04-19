//Implements the Account Class

#include "Account.h"
#include "util.h"
#include <iostream>

using namespace std;
int Account::GetAccountNumber(){
    return account_number_;
}

void Account::SetAccountNumber(int number){
    account_number_  = number;
}

string Account::GetAccountName(){
    return account_name_;
}

void Account::SetAccountName(std::string name){
    account_name_  = name;
}

char Account::GetAccountType(){
    return account_type_;
}
        
void Account::SetAccountType(char type){
    account_type_  = type;
}

long long int Account::GetAccountBalance(){
    return account_balance_;
}

void Account::SetAccountBalance(long long int balance){
    account_balance_  = balance;
}

void Account::ShowAccountStatus(){
    Print(Left,"-----ACCOUNT STATUS-----");
    Print(Left,"\nAccount No.: ",0);
    Print(Left,to_string(account_number_),0);
    Print(Left,"\nAccount Holder Name: ",0);
    Print(Left,account_name_,0);
    Print(Left,"\nAccount Type: ",0);
    Print(Left,string(1,account_type_),0);
    Print(Left,"\nAccount Balance: ",0);
    Print(Left,to_string(account_balance_),0);
}



