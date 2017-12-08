#ifndef USER_H
#define USER_H

#include <iostream>
#include <list>
#include "0_whatzap.h"
#include "1_chat.h"
#include <map>

class Chat;

using namespace std;

class User{

    string id;
    list<Chat*> chats;
public:
    User(string id){
        this->id = id;
    }

    list<string> getChats(){
        list<string> res;
        for(auto *elem : chats)
            res.push_front(elem->id);

        return res;
    }

    void invite(string idChat, User* user){
        for(auto *elem : chats){
            if(elem->id == idChat)

        }



    }
};

#endif // USER_H
