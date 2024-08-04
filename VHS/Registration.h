//
// Created by Geraldo Nascimento on 03/08/2024.
//

#ifndef CPP_LEARNING_REGISTRATION_H
#define CPP_LEARNING_REGISTRATION_H

#include "Rental.h"
#include <string>
#include <vector>
#include <iostream>
namespace VHS {
    class Registration {
    public:
        Registration(int id, const User &user);
        int getRegistrationId() const;
        User getRegisteredUser() const;

    private:
        int registrationId;
        User registeredUser;
    };
}

#endif //CPP_LEARNING_REGISTRATION_H
