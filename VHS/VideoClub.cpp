//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include "VideoClub.h"
#include "Rental.h"
#include "Registration.h"

class VideoClub {
public:
    void addUser(const User &user) {
        users.push_back(user);
        std::cout << "User " << user.getUserName() << " added.\n";
    }

    void addVideo(const Video &video) {
        videos.push_back(video);
        std::cout << "Video " << video.getVideoTitle() << " added.\n";
    }

    void registerUser(const User &user) {
        Registration registration(nextRegistrationId++, user);
        registrations.push_back(registration);
        std::cout << "User " << user.getUserName() << " registered with ID " << registration.getRegistrationId() << ".\n";
    }

    void rentVideo(const User &user, const Video &video) {
        Rental rental(nextRentalId++, user, video);
        rentals.push_back(rental);
        std::cout << "User " << user.getUserName() << " rented video " << video.getVideoTitle() << " with Rental ID " << rental.getRentalId() << ".\n";
    }

    void displayUsers() const {
        std::cout << "Users:\n";
        for (const auto &user : users) {
            std::cout << user.getUserId() << ": " << user.getUserName() << "\n";
        }
    }

    void displayVideos() const {
        std::cout << "Videos:\n";
        for (const auto &video : videos) {
            std::cout << video.getVideoId() << ": " << video.getVideoTitle() << " (" << video.getVideoGenre() << ")\n";
        }
    }

    void displayRentals() const {
        std::cout << "Rentals:\n";
        for (const auto &rental : rentals) {
            std::cout << "Rental ID " << rental.getRentalId() << ": " << rental.getRentingUser().getUserName() << " rented " << rental.getRentedVideo().getVideoTitle() << "\n";
        }
    }


};
