// "util.cpp" contains Utility,Display,Input,
// and Account Manipulation Function Definitions

#include <iostream>
#include "util.h"
#include <iomanip>

using namespace std;

//***********Utility functions*************

//Clears the current screen
void ClearScreen(){
    for(int i=0;i<5;i++){
        std::cout<<"\n\n\n\n";
    }
}

//Function to print a message in a formatted manner
void Print(Position pos, std::string s,int spacing,int line_length){
    int spaces = 0;
    switch(pos){
        case Center: spaces = (line_length - s.size())/2; break;
        case Right: spaces = (line_length - s.size()); break;
        case Left: spaces = 0; break;
        case Left_c: spaces = line_length; break;
    }
    for(int i=0;i<spacing;i++)
        std::cout<<"\n";
    if(spaces>0)
        std::cout<<std::string(spaces,' ');
    std::cout<<s;
    return;
}

//Prints a message of any type in a formatted manner
template<typename T> void printElement(T t, const int& width){   
    const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

//Checks if a given string only contains numbers
bool CheckNumber(string number){
    for(int i=0;i<number.size();i++){
        if(!isdigit(number[i]))
            return false;
    }
    return true;
}

//Checks of a given string only contains letters
bool CheckName(string name){
    for(int i=0;i<name.size();i++){
        if(!isalpha(name[i]))
            return false;
    }
    return true;
}

//***********Display functions*************

//Displays the Title Screen
void DisplayTitle(){
    const int line_len = 80;
    string header(line_len,'-');
    Print(Left,header);
    Print(Center,"Banking");
    Print(Center,"Management");
    Print(Center,"System");
    Print(Left,header);
    Print(Left,"MADE BY: Aravindh Shanmuganathan");
    Print(Left,"Press any ENTER to continue");
    getchar();
}

//Displays the Menu Options in Progam
int DisplayMenu(){
    int option_num = 1;
    Print(Left,"MAIN MENU");
    Print(Left,"01. NEW ACCOUNT");
    Print(Left,"02. DEPOSIT AMOUNT");
    Print(Left,"03. WITHDRAW AMOUNT");
    Print(Left,"04. BALANCE ENQUIRY");
    Print(Left,"05. ALL ACCOUNT HOLDER LIST");
    Print(Left,"06. CLOSE AN ACCOUNT");
    Print(Left,"07. MODIFY AN ACCOUNT");
    Print(Left,"08. EXIT");
    while(true){
        Print(Left,"SELECT YOUR OPTION(1-8)");
        char option = getchar();
        getchar();
        if(isdigit(option)){
            option_num = option - '0';
            if(option_num>0 && option_num<9)
                break;      
        }
        Print(Left," Invalid Entry:Chose a number between 1-8",0);
        option_num++;
    }
return option_num;
}


//***********Input functions*************

//Accepts a Valid Account Number
int AccountNumberInput(){
    string acc_number;
    while(true){
        Print(Left,"Enter the Account No. ");
        std::cin>>acc_number;
        if(CheckNumber(acc_number))
            break;
        else
            Print(Left,"Invalid Entry",0);
    }
    return stoi(acc_number);
}

//Prompts and Accepts Valid User Input For Name
string AccountNameInput(std::string message){
    string acc_name;
    while(true){
        Print(Left,message);
        std::cin>>acc_name;
        if(CheckName(acc_name))
            break;
        else
            Print(Left,"Invalid Name",0);
    }
    return acc_name;
}

// Prompts and Accepts Valid User Input For Account Type
char AccountTypeInput(string message){
    char acc_type;
    while(true){
        Print(Left,message);
        std::cin>>acc_type;
        if(toupper(acc_type)=='C' || toupper(acc_type)=='S')
            return toupper(acc_type);
    }    
}

// Prompts and Accepts Valid User Input For Balance
long long int AccountBalanceInput(string message){
    string acc_balance;
    while(true){
        Print(Left,message);
        std::cin>>acc_balance;
        if(CheckNumber(acc_balance))
            break;
        else
            Print(Left,"Invalid Entry",0);
    }
    return stoll(acc_balance,nullptr,10);    
}


//***********Account Manipulation Functions*************

//Returns the index of input account number in the bank_account vector
int AccountAccess(int account_num){
     while(true){
        vector<Account>::iterator itr = find_if(bank_account.begin(), bank_account.end(), [account_num](Account i)
        { 
            return (i.GetAccountNumber() == account_num);
        }); 
        if(itr!=bank_account.end()){
            return itr-bank_account.begin();
        }
        Print(Left,"Account Does Not Exist!",0);
        account_num = AccountNumberInput();
    }
}

//Create a New Account by inputting account details
void CreateNewAccount(){
    Print(Left,"-----NEW ACCOUNT ENTRY FORM-----");
    Account new_acc;
    int account_num;
    while(true){
        account_num = AccountNumberInput();
        auto ptr = account_number_set.insert(account_num);
        if(!ptr.second)
            Print(Left,"Account Number already in use",0);
        else
            break;
    }
    new_acc.SetAccountNumber(account_num);
    new_acc.SetAccountName(AccountNameInput("Enter The Name of the Account Holder: "));
    new_acc.SetAccountType(AccountTypeInput("Enter the Type of the Account (C/S): "));
    while(true){
        string msg = "Enter the Initial Amount: \n\t (>=500 for Savings >=1000 for Checking) :";
        long long int bal = AccountBalanceInput(msg);
        if((bal>=500 && new_acc.GetAccountType()=='S') ||
            (bal>=1000 && new_acc.GetAccountType()=='C'))
        {
            new_acc.SetAccountBalance(bal);
            break;
        }
        else
            Print(Left,"Invalid Amount! Try Again.",0);
    }
    bank_account.push_back(new_acc);
    return;
}

//Accepts User Input for transaction and updates records
void AccountTransaction(string action,int ind){
    bank_account[ind].ShowAccountStatus();
    long long int amount;
    if(action == "WD"){
        while(true){
            amount = AccountBalanceInput("Enter the amount to WITHDRAW: ");
            if(amount<bank_account[ind].GetAccountBalance())
            {
                amount = bank_account[ind].GetAccountBalance() - amount;
                bank_account[ind].SetAccountBalance(amount);
                break;
            }
            Print(Left,"Funds Low!!",1); 
        }       
    }
    else
    {
        amount = AccountBalanceInput("Enter the amount to DEPOSIT: ");
        bank_account[ind].SetAccountBalance(bank_account[ind].GetAccountBalance() + amount);
    }
    bank_account[ind].ShowAccountStatus();
    Print(Center,"Record Updated");
    return;
}

//List all Active Account Holders
void ListAccountHolders(){
    set<int>::iterator itr = account_number_set.begin();
    string header(80,'=');
    const int nameWidth = 30;
    const int numWidth = 20;
    Print(Center,"---ACCOUNT HOLDER LIST---");
    Print(Left,header);
    cout<<endl;
    printElement("A/C No.",numWidth);
    printElement("NAME",nameWidth);
    printElement("TYPE",numWidth);
    printElement("BALANCE",nameWidth);
    Print(Left,header,1);
    cout<<endl;
    while(itr!=account_number_set.end()){
        int ind = (AccountAccess(*itr));
        printElement(bank_account[ind].GetAccountNumber(),numWidth);
        printElement(bank_account[ind].GetAccountName(),nameWidth);
        printElement(bank_account[ind].GetAccountType(),numWidth);
        printElement(bank_account[ind].GetAccountBalance(),nameWidth);
        cout<<endl;
        itr++;
    }
    return;
}

//Accepts User Input for modification of Records
void ModifyAccount(){
    Print(Left,"----MODIFY ACCOUNT----");
    int ind = AccountAccess(AccountNumberInput());
    bank_account[ind].ShowAccountStatus();
    Print(Left,"----Enter the New Details----");
    Print(Left,"Account No. :");
    Print(Left,to_string(bank_account[ind].GetAccountNumber()),0);
    bank_account[ind].SetAccountName(AccountNameInput("Modify Account Holder Name: "));
    bank_account[ind].SetAccountType(AccountTypeInput("Modify Type of Account: "));
    bank_account[ind].SetAccountBalance(AccountBalanceInput("Modify Balance Amount: "));
    bank_account[ind].ShowAccountStatus();
    return;
}