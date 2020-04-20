//util.h contains global variables & utility,
// display, input and account manipulation function declarations
#ifndef __UTIL_H_INCLUDED__
#define __UTIL_H_INCLUDED__
#include <set>
#include "Account.h"
#include <vector>

//Global Variables
extern std::vector<Account> bank_account;
enum Position{Left,Center,Right,Left_c};
extern std::set<int> account_number_set;

//Utility Functions
void ClearScreen();
void Print(Position, std::string,int spacing = 2,int line_length = 80); 
template<typename T> void printElement(T ,const int& );
bool CheckNumber(std::string);
bool CheckName(std::string);

//Display and Input Functions
void DisplayTitle();
int DisplayMenu();
int AccountNumberInput();
std::string AccountNameInput(std::string);
char AccountTypeInput(std::string);
long long int AccountBalanceInput(std::string);

//Account Manipulation Functions
int AccountAccess(int);
void CreateNewAccount();
void AccountTransaction(std::string,int ind);
void ListAccountHolders();
void ModifyAccount();

#endif