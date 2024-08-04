//
// Created by Geraldo Nascimento on 03/08/2024.
//
#include <iostream>

// this is an include guard below
// prevents types, statics and enums from being defined again,
// when the file is included multiple tiems
#ifndef CPP_LEARNING_VIDEO_H
#define CPP_LEARNING_VIDEO_H

    class Video {
    public:
        Video(int id, std::string title, std::string genre);
        int getVideoId() const;

        std::string getVideoTitle() const { return videoTitle; }

        std::string getVideoGenre() const { return videoGenre; }

    private:
        int videoId;
        std::string videoTitle;
        std::string videoGenre;
    };

#endif //CPP_LEARNING_VIDEO_H
