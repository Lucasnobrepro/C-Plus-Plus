#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include "2_user.h"
#include <map>
#include "0_whatzap.h"
#include <list>

using namespace std;

class Chat{
    string id;
    map<string,User *> users;
    list<string> unread;
public:
    Chat(string id = "") {
        this->id = id;
    }

    bool addUser(User* user){
        users.insert(user,user->id);
    }

    friend class User;
};

#endif // CHAT_H
