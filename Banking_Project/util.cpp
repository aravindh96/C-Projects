
#include <iostream>
#include "util.h"
#include <iomanip>

//Utility functions

// enum Position{Left,Center,Right};
using namespace std;
extern std::set<int> account_number_set;
// extern vector<Account> bank_account;
void ClearScreen(){
    for(int i=0;i<5;i++){
        std::cout<<"\n\n\n\n";
    }
}

void Print(Position pos, std::string s,int spacing,int line_length){
    int spaces = 0;
    switch(pos)
    {
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

template<typename T> void printElement(T t, const int& width)
{   
    const char separator    = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

void DisplayTitle(){
    const int line_len = 80;
    string header(line_len,'-');
    
    // Print(Center,myacc.account_name);
    Print(Left,header);
    Print(Center,"Banking");
    Print(Center,"Management");
    Print(Center,"System");
    Print(Left,header);

    Print(Left,"MADE BY: Aravindh Shanmuganathan");
    Print(Left,"Press any ENTER to continue");
    getchar();
}

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

    while(true)
    {
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

bool CheckNumber(string number){
    for(int i=0;i<number.size();i++){
        if(!isdigit(number[i]))
            return false;
    }
    return true;
}

bool CheckName(string name){
    for(int i=0;i<name.size();i++){
        if(!isalpha(name[i]))
            return false;
    }
    return true;
}

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

Account AccountAccess(int account_num){
     while(true){
        vector<Account>::iterator itr = find_if(bank_account.begin(), bank_account.end(), [account_num](Account i)
        { 
            return (i.GetAccountNumber() == account_num);
        }); 
        if(itr!=bank_account.end()){
            return *itr;
        }
        Print(Left,"Account Does Not Exist!",0);
        account_num = AccountNumberInput();
    }
}

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

char AccountTypeInput(string message){
    char acc_type;
    while(true){
        Print(Left,message);
        std::cin>>acc_type;
        if(toupper(acc_type)=='C' || toupper(acc_type)=='S')
            return toupper(acc_type);
    }    
}

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

Account CreateNewAccount(Account new_acc){
    Print(Left,"-----NEW ACCOUNT ENTRY FORM-----");
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
    return new_acc;


}

void AccountTransaction(string action,Account active_acc){
    active_acc.ShowAccountStatus();
    long long int amount;
    if(action == "WD"){
        while(true){
            amount = AccountBalanceInput("Enter the amount to WITHDRAW: ");
            if(amount<active_acc.GetAccountBalance())
                {
                    active_acc.SetAccountBalance(active_acc.GetAccountBalance() - amount);
                    break;
                }
            Print(Left,"Funds Low!!",1); 
        }
    active_acc.ShowAccountStatus();         
    }
    else
    {
        amount = AccountBalanceInput("Enter the amount to DEPOSIT: ");
        active_acc.SetAccountBalance(active_acc.GetAccountBalance() + amount);
    }
    Print(Center,"Record Updated");
}


void ListAccountHolders(){
    set<int>::iterator itr = account_number_set.begin();
    string header(80,'=');
    const int nameWidth = 30;
    const int numWidth = 20;
    Print(Center,"ACCOUNT HOLDER LIST");
    Print(Left,header);
    cout<<endl;
    printElement("A/C No.",numWidth);
    printElement("NAME",nameWidth);
    printElement("TYPE",numWidth);
    printElement("BALANCE",nameWidth);
    cout<<endl;
    Print(Left,header,1);
    cout<<endl;
    Account active_acc;
    while(itr!=account_number_set.end()){
        active_acc = (AccountAccess(*itr));
        printElement(active_acc.GetAccountNumber(),numWidth);
        printElement(active_acc.GetAccountName(),nameWidth);
        printElement(active_acc.GetAccountType(),numWidth);
        printElement(active_acc.GetAccountBalance(),nameWidth);
        cout<<endl;
        itr++;
    }
}