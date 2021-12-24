#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<list>
using namespace std;

class UserAccountType{
 protected:
    string userId;
    string encrypted_password;
    string firstName;
    string lastName;
 public:
    UserAccountType();
    UserAccountType(string,string,string,string);
    void setUserId(string);
    void setFirstName(string);
    void setLastName(string);
    void setPassword(string);
    string getUserId();
    bool isCompleteUserAccount();
    string encryptPassword(string);
    void printUserInfo();
    bool isValidPassword(string);
};

//Time Complexity: O(1)
UserAccountType::UserAccountType(){
    userId = "";
    encrypted_password = "";
    firstName = "";
    lastName = "";
}

////Time Complexity: O(n)
UserAccountType::UserAccountType(string id,string pass,string fname,string lname){
    userId = id;
    firstName = fname;
    lastName = lname;
    setPassword(pass);
}

//Time Complexity: O(1)
void UserAccountType::setUserId(string id){
    userId = id;
}

//Time Complexity: O(1)
void UserAccountType::setFirstName(string fname){
    firstName = fname;
}

//Time Complexity: O(1)
void UserAccountType::setLastName(string lname){
    lastName = lname;
}

//Time Complexity: O(n)
void UserAccountType::setPassword(string pass){
    if(isValidPassword(pass))
        encrypted_password = encryptPassword(pass);
    else
        encrypted_password = "";
}

//Time Complexity: O(1)
string UserAccountType::getUserId(){
    return userId;
}

//Time Complexity: O(n)
bool UserAccountType::isCompleteUserAccount(){
    bool complete = true;
    if(userId.compare("") == 0)
        complete = false;
    else if(firstName.compare("") == 0)
            complete = false;
    else if(lastName.compare("") == 0)
            complete = false;
    else if(encrypted_password.compare("") == 0)
            complete = false;

    if(!complete)
        cout<<endl<<"this user account is incomplete and cannot be inserted in the list"<<endl;

    return complete;
}

//Time Complexity: O(n)
string UserAccountType::encryptPassword(string pass){
    list<char> list1;
    int passLength = pass.length();
    //Step 1: insert the password into the list
    for(int i=0;i<passLength;i++){
        list1.push_back(pass[i]);
    }
    //Step 2: swap the first and the last characters
    char temp;
    temp = list1.front();
    list1.pop_front();
    list1.push_front(list1.back());
    list1.pop_back();
    list1.push_back(temp);
    //Step 3: encryption 
    /*
        I used the stack for this operation because the last char wont change and every char will change based on the next char
        so we need to push the last char in the stack and then use the top function to access it so that we can change
        the previous character based on it and then push that character into stack and so on and lastly transfer
        the characters from the stack back into the list, the data structre that can do all of that easily is the stack 
        and that's why I chose it.
        I could have used a queue for this operation but it will make things harder since I need to reverse the queue before 
        inserting it back into the list.
    */
    stack<char> stack1;
    int nextCharAscii;
    int charAscii;
    //save the list's last character ascii number
    nextCharAscii = static_cast<int>(list1.back());
    //push the last character into the stack
    stack1.push(list1.back());
    //remove the last character from the list
    list1.pop_back();
    //while the list is not empty iterate through the list and encrypt each character then push them into the stack
    while(!(list1.empty())){
        //save the list's last character ascii number
        charAscii = static_cast<int>(list1.back());
        //add the least significant digit of the next character's ascii number to the current character ascii number
        charAscii += (nextCharAscii % 10);
        //push the encrypted character into the stack
        stack1.push(static_cast<char>(charAscii));
        //save the list's last character ascii code to use it in the next iteration
        nextCharAscii = static_cast<int>(list1.back());
        //pop the list's last character
        list1.pop_back();
    }
    //now we have a stack filled with the encrypted password
    //push the encrypted password back to the list
    while(!(stack1.empty())){
        //insert the top character of the stack to the list
        list1.push_back(stack1.top());
        //pop the top character from the stack
        stack1.pop();
    }

    //Step 4: reverse even positioned characters in the list

    /*
      I chose both the stack and the queue in this step because i needed two data structres that are kind of the opposite of each other
      because the third and the fourth character to get poped from the list need to be accessed and poped in a opposite order from the other characters
      so either we chose a stack for the 3rd and 4th characters and a queue for the rest or we chose a queue for the 3rd and 4th character
      and a stack for the rest.
    */
    /*
        Algorithim explanation:
        Suppose we have a password that is [1,A,2,B,3,C,4,D] and we need to encrypt it to be [4,A,3,B,2,C,1,D]
        first since the algorthim is different if the password length is odd or even we need to convert the list
        from being odd to be even to make things easier.

        Step 1: if the list is odd push a rubbish value to the end of the list and remove it later else skip this step
        [1,A,2,B,3,C,4,D] became [1,A,2,B,3,C,4,D]
        [1,A,2,B,3,C,4] became [1,A,2,B,3,C,4,@] "@" is the rubbish character

        Step 2: 1- push the list's last char into the stack 
                   the list [1,A,2,B,3,C,4,D] became [1,A,2,B,3,C,4]
                   the stack became [D]
                2- push the list's first char into the stack
                   the list [1,A,2,B,3,C,4] became [A,2,B,3,C,4]
                   the stack became [D,1]
                3- push the list's first char into a queue
                   the list [A,2,B,3,C,4] became [2,B,3,C,4]
                   the queue became [A]
                4- push the list's last char into the queue
                   the list [2,B,3,C,4] became [2,B,3,C]
                   the queue became [A,4]
                5- push the rest of the list into the stack in this order (last,first,first,last,last,first,first..)
                   after finishing we will have and empty list and a stack[D,1,C,2,B,3] and a queue [A,4]
                6- push the queue elements into the stack
                    the stack is now [D,1,C,2,B,3,A,4]
                7- lastly push the stack back into the list 
                    the list will be [4,A,3,B,2,C,1,D] and thats what we need
    */
    queue<char> queue1;
    bool odd = false;
    //if the password length is odd push a rubbish character to the end of it to make it even
    if(passLength % 2){
        list1.push_back('#');
        passLength++;
        odd = true;
    }
    //iterate through the list
    for(int i=0;i<passLength;i++){
        //the 3rd and 4th characters need to be pushed in a queue
        if(i == 2){
            queue1.push(list1.front());
            list1.pop_front();
            queue1.push(list1.back());
            list1.pop_back();
            i++;
            }
        else{//the rest of the character are pushed into a stack in this order(last,first,first,last,last,first,first...)
            if(i % 4 == 1 || i % 4 == 2){
                stack1.push(list1.front());
                list1.pop_front();
            }
            else{
                stack1.push(list1.back());
                list1.pop_back();
            }
        }
    }
    //push the queue into the stack
    while (!(queue1.empty())){
        stack1.push(queue1.front());
        queue1.pop();
    }
    //push the stack back into the list
    while(!(stack1.empty())){
        list1.push_back(stack1.top());
        stack1.pop();
    }

    //remove the added character if the list is odd
    if(odd){
        list1.pop_back();
    }

    string encryptedPass;
    //convert the list into a string to return it
    while(!(list1.empty())){
        encryptedPass += list1.front();
        list1.pop_front();
    }

    //return the encrypted password
    return encryptedPass;
}

//Time Complexity: O(1)
void UserAccountType::printUserInfo(){
    cout<<"________________(User Info)______________"<<endl;
    cout<<"User ID:  "<<userId<<endl;
    cout<<"First Name:  "<<firstName<<endl;
    cout<<"Last Name:  "<<lastName<<endl;
    cout<<"Encrypted Password:  "<<encrypted_password<<endl;
}

//Time Complexity: O(n)
bool UserAccountType::isValidPassword(string pass){
    bool valid = true;
    int symbol = 0;
    int digit = 0;
    int letter = 0;
    for(int i=0;i<pass.length();i++){
        if(pass[i] == '*' || pass[i] == '#' || pass[i] == '$')
            symbol++;
        if(isdigit(pass[i]))
            digit++;
        if(isalpha(pass[i]))
            letter++;
    }
    if(pass.length() < 6 && pass.length() > 8)
        valid = false;
    else if(symbol != 1)
        valid = false;
    else if(digit != 1)
        valid = false;
    else if(letter != (pass.length()-2))//since we only count 3 symbols we need to make sure that the rest of the password is only letters
        valid = false;

    if(!valid)
        cout<<"!!!!!! Invalid Password !!!!!!!,  Your password will be set to \"\""<<endl;

    return valid;
}

class UserAccountNode{
 public:
    UserAccountType user_account;
    UserAccountNode *link;
};

class UserAccountListType {
    UserAccountNode *first;
    UserAccountNode *last;
    int counter;
 public:
    UserAccountListType();
    ~UserAccountListType();
    void destroyList();
    void print();
    bool isUserIdExist(string);
    void insertUserAccount(UserAccountType);
    void deleteUserAccount(string);
    void printInfo_of_UserId(string);
};

//Time Complexity: O(1)
UserAccountListType::UserAccountListType(){
    first = NULL;
    last = NULL;
    counter = 0;
}

//Time Complexity: O(n)
UserAccountListType::~UserAccountListType(){
    destroyList();
}

//Time Complexity: O(n)
void UserAccountListType::destroyList(){
    //create temporary node to avoid memory leaks
    UserAccountNode *temp = new UserAccountNode;
    while(first != NULL){
        temp = first;
        first = first->link;
        delete temp;
    }
    last = NULL;
    counter = 0;
}

//Time Complexity: O(n)
void UserAccountListType::print(){
    UserAccountNode *current = new UserAccountNode;
    current = first;
    int count = 1;
    cout<<endl<<"*********The contents of the user account list"<<endl;
    while(current != NULL){
        if(count > 1)
            cout<<endl<<"________________________________________"<<endl;
        cout<<"userAccount # "<<count<<":"<<endl;
        current->user_account.printUserInfo();
        current = current->link;
        count++;
    }
}

//Time Complexity: O(n^2)
bool UserAccountListType::isUserIdExist(string id){
    bool exist = false;
    UserAccountNode *current = new UserAccountNode;
    current = first;
    while(current != NULL){
        if(current->user_account.getUserId().compare(id) == 0){
            exist = true;
            break;
        }
        current = current->link;
    }

    return exist;
}

//Time Complexity: O(n^2)
void UserAccountListType::insertUserAccount(UserAccountType newItem){
    //if the account is complete and there is no user id in the list with the same name
    if(newItem.isCompleteUserAccount() && !isUserIdExist(newItem.getUserId())){
            UserAccountNode *newNode = new UserAccountNode;
            newNode->user_account = newItem;
            newNode->link = NULL;
            //if the list is empty
            if(first == NULL){
                first = newNode;
                last = newNode;
                counter++;
            }
            //if the list have some items in it
            else{
            last->link = newNode;
            last = newNode;
            last->link = NULL;
            counter++;
            }
        }
}

//Time Complexity: O(n^2)
void UserAccountListType::deleteUserAccount(string id){
    UserAccountNode *current = new UserAccountNode;
    UserAccountNode *trailCurrent = new UserAccountNode;
    cout<<"deleting from the list the account node of the user "<<id<<endl;
    bool found;
    current = first;
    //the list is empty
    if(first == NULL)
        cout<<"Cannot delete from an empty list"<<endl;
    else if(first->user_account.getUserId().compare(id) == 0){ // the node to be deleted is the first node
            current = first;
            first = first->link;
            delete current;
            counter--;
    }
    else { // the node to be deleted is somewhere in the list
        current = first;
        while(current != NULL){
            if(current->user_account.getUserId().compare(id) == 0)
            {
                found = true;
                trailCurrent->link = current->link;
                //the node to be deleted is the last node
                if(last == current){
                    last = trailCurrent;
                }
                delete current;
                counter--;
            }
            trailCurrent = current;
            current = current->link;
        }
            if(!found)
                cout<<"The user "<<id<<" is not in the list to get deleted"<<endl;
    }
}

//Time Complexity: O(n^2)
void UserAccountListType::printInfo_of_UserId(string id){
    UserAccountNode *current;
    current = first;
    cout<<"________________________________"<<endl;
    cout<<"***************************"<<endl;
    cout<<"Searching the list for the user account "<<id<<endl;
    if(this->isUserIdExist(id)){
        while(current != NULL){
            if(current->user_account.getUserId().compare(id) == 0){
                current->user_account.printUserInfo();
        }
            current = current->link;
        }
    }
    else
     cout<<"The user "<<id<<" cannot be found"<<endl;
}