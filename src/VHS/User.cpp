//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include "User.h"

    User::User(int id, std::string name) : userId(id), userName(name) {}

    int User::getUserId() const { return userId; }

    std::string User::getUserName() const { return userName; }
