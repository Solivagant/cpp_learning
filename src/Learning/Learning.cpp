//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include "Learning.h"

void Learning::CoutNoFlush() {
    for (int i = 0; i < 5; i++) {
        std::cout << ".";
        sleep(1);
    }

    std::cout << "\n";
}

void Learning::CoutWithFlush() {
    for (int i = 0; i < 5; i++) {
        std::cout << "." << std::flush;;
        sleep(1);
    }

    std::cout << "\n";
}

Learning::Learning(int secondsToSleep) {

}

void Learning::BitShiftTests() {
    int bin = 0x0001;

    std::cout << bin << std::endl;

    //bit shift to the left
    //is multiplying by 2;
    bin = bin << 1;
    std::cout << bin << std::endl;
    bin = bin << 2;
    std::cout << bin << std::endl;

    //bit shifting to the right is dividing by 2
    bin = bin >> 4;
    std::cout << bin << std::endl;
}