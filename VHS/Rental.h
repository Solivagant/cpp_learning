//
// Created by Geraldo Nascimento on 03/08/2024.
//

#ifndef CPP_LEARNING_RENTAL_H
#define CPP_LEARNING_RENTAL_H

#include <string>
#include <vector>
#include <iostream>
#include "VideoClub.h"
namespace VHS {
    class Rental {
    public:
        //TODO what's this const in parameters?
        Rental(int id, const User &user, const Video &video);

        //what's this const after method declaration?
        int getRentalId() const;

        User getRentingUser() const;

        Video getRentedVideo() const;

    private:
        int rentalId;
        User rentingUser;
        Video rentedVideo;
    };
}
#endif //CPP_LEARNING_RENTAL_H
