//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include "StdSample.h"

void StdSample::CoutNoFlush() {
    for (int i = 0; i < 5; i++) {
        std::cout << ".";
        sleep(1);
    }

    std::cout << "\n";
}

void StdSample::CoutWithFlush() {
    for (int i = 0; i < 5; i++) {
        std::cout << "." << std::flush;;
        sleep(1);
    }

    std::cout << "\n";
}

StdSample::StdSample(int secondsToSleep) {

}
