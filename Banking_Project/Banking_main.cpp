//Main File containing Logic for Banking System

#include <iostream>
#include <stdlib.h>
#include "Account.h"
#include "util.h"
#include <stdio.h>
#include <set>
#include <vector>

using namespace std;

// Global variable holding the set of all account numbers;
set<int> account_number_set;
vector<Account> bank_account = {};

int main(){
    
    DisplayTitle();
    ClearScreen();
    int option = 0;
    
    //Looping through Switch Case Statement until Exit command
    while(option!=8){
        option = DisplayMenu();
        ClearScreen();
        switch(option){
            case 1:{
                //New Account Form
                CreateNewAccount();
                Print(Left,"\n Your Account Was Created Successfully!");
                break;
            }
            case 2:{
                //Deposit Form
                int ind = AccountAccess(AccountNumberInput());
                AccountTransaction("Deposit",ind);
                break;
            }
            case 3:{
                //Withdraw Account
                int ind = AccountAccess(AccountNumberInput());
                AccountTransaction("WD",ind);
                break;
            }
            case 4:{
                //Balance Enquiry
                int ind = AccountAccess(AccountNumberInput());
                bank_account[ind].ShowAccountStatus();
                break;
            }
            case 5:{
                //List All Account Holders
                ListAccountHolders();
                break;
            }
            case 6:{
                //Close An Account
                int ind = AccountAccess(AccountNumberInput());
                account_number_set.erase(bank_account[ind].GetAccountNumber());
                bank_account.erase(bank_account.begin() + ind);
                Print(Center,"Account DELETED!");
                break;
            }
            case 7:{
                //Modify an Account
                ModifyAccount();
                break;
            }
            case 8:{
                //Exit
                Print(Center," EXITING PROGRAM!");
            }
        }
        Print(Center,"Hit Enter to Proceed",3);
        getchar();
        getchar();
    }
    return 0;  
}