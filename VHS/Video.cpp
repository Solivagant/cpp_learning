//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include "Video.h"
namespace VHS {
    Video::Video(int id, std::string title, std::string genre) : videoId(id), videoTitle(title), videoGenre(genre) {}

    int Video::getVideoId() const { return videoId; }
}