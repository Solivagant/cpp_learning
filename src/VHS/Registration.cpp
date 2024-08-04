//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include "Registration.h"

Registration::Registration(int id, const User &user) : registrationId(id), registeredUser(user) {}

int Registration::getRegistrationId() const { return registrationId; }

User Registration::getRegisteredUser() const { return registeredUser; }
