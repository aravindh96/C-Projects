#ifndef __UTIL_H_INCLUDED__
#define __UTIL_H_INCLUDED__
#include <set>
#include "Account.h"
#include <vector>

// #include <iostream>
//Utility functions

extern std::vector<Account> bank_account;
enum Position{Left,Center,Right,Left_c};
extern std::set<int> account_number_set;
void ClearScreen();

void Print(Position, std::string,int spacing = 2,int line_length = 80); 
template<typename T> void printElement(T ,const int& );
void DisplayTitle();
int DisplayMenu();
bool CheckNumber(std::string);
int AccountNumberInput();
Account AccountAccess(int);
std::string AccountNameInput(std::string);
char AccountTypeInput(std::string);
long long int AccountBalanceInput(std::string);

Account CreateNewAccount(Account);
void AccountTransaction(std::string,Account);
void ListAccountHolders();
    



#endif