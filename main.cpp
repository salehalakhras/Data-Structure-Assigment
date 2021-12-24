#include"userAccountListType.h"
#include<iostream>
using namespace std;

void addAccounts(int accNum,UserAccountListType &accountList){
    string var;
    cout<<"--Creating a new user account and adding it to the user account list"<<endl;

    for(int i=0;i<accNum;i++){
        UserAccountType *account = new UserAccountType;
        cout<<endl<<"Please enter user's id:"<<endl;
        getline(cin,var);
        account->setUserId(var);
        cout<<endl<<"Please enter user's First Name:"<<endl;
        getline(cin,var);
        account->setFirstName(var);
        cout<<endl<<"Please enter user's Last Name:"<<endl;
        getline(cin,var);
        account->setLastName(var);
        cout<<endl<<"Please enter a password, a valid password should consist of 8-9 characters."<<endl;
        cout<<"The password should consist of letters and one digit and one of the symbols(*,#,$)"<<endl;
        getline(cin,var);
        account->setPassword(var);
        accountList.insertUserAccount(*account);
    }

}

int main(){

    UserAccountListType accountList;
    cout<<"Creating a list and add three accounts and print it.."<<endl;
    addAccounts(3,accountList);
    accountList.print();

    addAccounts(2,accountList);//add an account with invalid password and an account with missing info

    accountList.printInfo_of_UserId("Ahmad_ali");//search for existing id and print it
    accountList.printInfo_of_UserId("Ahmad_omar");//search for non existing id

    accountList.deleteUserAccount("Ahmad_ali");//delete existing id
    accountList.print();//print after deletion
    accountList.deleteUserAccount("Ahmad_omar");//delete non existing id

}