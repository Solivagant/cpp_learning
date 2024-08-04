//
// Created by Geraldo Nascimento on 03/08/2024.
//
#include "Rental.h"

namespace VHS {
    Rental::Rental(int id, const User &user, const Video &video) : rentalId(id), rentingUser(user),
                                                                   rentedVideo(video) {}

    int Rental::getRentalId() const { return rentalId; }

    User Rental::getRentingUser() const { return rentingUser; }

    Video Rental::getRentedVideo() const { return rentedVideo; }
}