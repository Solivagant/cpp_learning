#include "Rental.h"
#include "Registration.h"
#include "User.h"
#include "Video.h"

class VideoClub {
public:
    void addUser(const User &user);
    void addVideo(const Video &video);
    void registerUser(const User &user);
    void rentVideo(const User &user, const Video &video);
    void displayUsers() const;
    void displayVideos() const;
    void displayRentals() const;
private:
    std::vector<User> users;
    std::vector<Video> videos;
    std::vector<Registration> registrations;
    std::vector<Rental> rentals;
    int nextRegistrationId = 1;
    int nextRentalId = 1;
};
