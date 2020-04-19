#include <iostream>
#include <stdlib.h>
#include "Account.h"
#include "util.h"
#include <stdio.h>
#include <set>
#include <vector>
// #include <iomanip>

using namespace std;
// Global variable holding the set of all account numbers;
set<int> account_number_set;
vector<Account> bank_account = {};
// template<typename T> void printElement(T , const int& );
int main(){
    

    DisplayTitle();
    ClearScreen();
    int option = 0;
    
    while(option!=8){

        option = DisplayMenu();
        ClearScreen();
        Account active_acc;
        // temp.ShowAccountStatus();

        switch(option){
            case 1:{
                //New Account Form
                Account temp;
                temp = CreateNewAccount(temp);
                bank_account.push_back(temp);
                Print(Left,"\n Your Account Was Created Successfully!");
                break;
            }
            case 2:{
                //Deposit Form
                Account active_acc = AccountAccess(AccountNumberInput());
                // active_acc.ShowAccountStatus();
                AccountTransaction("Deposit",active_acc);
                break;
            }
            case 3:{
                //Withdraw Account
                Account active_acc = AccountAccess(AccountNumberInput());
                // active_acc.ShowAccountStatus();
                AccountTransaction("WD",active_acc);
                break;

            }
            case 4:{
                //Balance Enquiry
                active_acc = AccountAccess(AccountNumberInput());
                active_acc.ShowAccountStatus();
                break;
            }
            case 5:{
                //List All Account Holders
                ListAccountHolders();
                break;

            }
            case 6:{
                //Close An Account
                int acc_num = AccountNumberInput();
                account_number_set.erase(acc_num);
                Print(Center,"Account DELETED!");
                break;

            }
            case 7:{
                //Modify an Account
                Print(Left,"----MODIFY ACCOUNT----");
                int acc_num = AccountNumberInput();
                active_acc = AccountAccess(acc_num);
                active_acc.ShowAccountStatus();
                Print(Left,"----Enter the New Details----");
                Print(Left,"Account No. :");
                Print(Left,to_string(acc_num),0);
                active_acc.SetAccountName(AccountNameInput("Modify Account Holder Name: "));
                active_acc.SetAccountType(AccountTypeInput("Modify Type of Account: "));
                active_acc.SetAccountBalance(AccountBalanceInput("Modify Balance Amount: "));
                break;
            }
            case 8:{
                //Exit
                Print(Center," EXITING PROGRAM!");
            }
        }
        Print(Center,"Hit Enter to Proceed",3);
        getchar();
        // getchar();
    }


    return 0;
    
}