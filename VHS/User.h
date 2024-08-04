//
// Created by Geraldo Nascimento on 03/08/2024.
//
#include <iostream>

#ifndef CPP_LEARNING_USER_H
#define CPP_LEARNING_USER_H
namespace VHS {
    class User {
    public:
        User(int id, std::string name);
        int getUserId() const;
        std::string getUserName() const;

    private:
        int userId;
        std::string userName;
    };
}
#endif //CPP_LEARNING_USER_H
