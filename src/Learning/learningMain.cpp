#include <iostream>
#include "Learning.h"
#include "../VHS/VideoClub.h"

void IterateArray();
void CoutTests();
void DoubleArrowOperator();
void RunVideoClub();

//int main() {
//    CoutTests();
//    IterateArray();
//    DoubleArrowOperator();
//    RunVideoClub();
//    return 0;
//}

void RunVideoClub() {
    VideoClub club;

    User user1(1, "Alice");
    User user2(2, "Bob");

    Video video1(1, "Inception", "Sci-Fi");
    Video video2(2, "The Godfather", "Crime");

    club.addUser(user1);
    club.addUser(user2);

    club.addVideo(video1);
    club.addVideo(video2);

    club.registerUser(user1);
    club.registerUser(user2);

    club.rentVideo(user1, video1);
    club.rentVideo(user2, video2);

    club.displayUsers();
    club.displayVideos();
    club.displayRentals();
}

void DoubleArrowOperator() {
    int numbers[10];
    for (int i = 0; i < 10; ++i) {
        numbers[i] = 10 >> 1;
    }
    for (int number: numbers) {
        std::cout << number << std::endl;
    }
}

void CoutTests() {
    Learning sample(10);
    Learning *samplePointer = &sample;
    sample.CoutWithFlush();
    sample.CoutNoFlush();
    samplePointer->CoutNoFlush();
}

void IterateArray() {
    int numbers[10];
    for (int i = 0; i < 10; ++i) {
        numbers[i] = i;
    }
    for (int number: numbers) {
        std::cout << number;
    }
    std::cout << std::endl;

}
