//
// Created by Geraldo Nascimento on 09/08/2024.
//

#include "PlayerData.h"

//PlayerData::PlayerData() {
////    rxcpp::subjects::subject<int> subject;
////    auto simpleObservable = subject.get_observable();
////
////    simpleObservable.subscribe([](int i) {
////        std::cout << "SIMPLE OBSERVABLE " << i << "\n";
////    });
////
////    auto simpleSubscriber = subject.get_subscriber();
////    simpleSubscriber.on_next(10);
////    simpleSubscriber.on_next(12);

//}

void PlayerData::UpdatePosition(Vector2 position)
{
    positionSubscriber.on_next(position);
}

bool PlayerData::IsDead() {
    return health <= 0;
}

int PlayerData::GetHealth() const {
    return health;
}

void PlayerData::SetHealth(int health) {
    this->health = health;
    if (IsDead()) {
        SetXP(0);
        level = 1;
    }
}

float PlayerData::GetMaxHealth() {
    return maxHealth;
}

int PlayerData::GetXP() const {
    return xp;
}

void PlayerData::SetXP(int xp) {
    this->xp = xp;
    if (xp >= GetXPToNextLevel()) {
        this->xp = 0;
        level++;
    }
}

int PlayerData::GetXPToNextLevel() {
    return xpPerLevel + level * 20 + level * 3;
}

int PlayerData::GetLevel() {
    return level;
}

rxcpp::observable<Vector2>* PlayerData::GetPositionObservable() {
    return &observable;
}
