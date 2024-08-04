//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include <iostream>
#include <unistd.h>

#ifndef CPP_LEARNING_STDSAMPLE_H
#define CPP_LEARNING_STDSAMPLE_H


class StdSample {

public:
    explicit StdSample(int secondsToSleep);
    void CoutNoFlush();
    void CoutWithFlush();

private:

};


#endif //CPP_LEARNING_STDSAMPLE_H
