//
// Created by Geraldo Nascimento on 03/08/2024.
//

#include <iostream>
#include <unistd.h>

#ifndef CPP_LEARNING_STDSAMPLE_H
#define CPP_LEARNING_STDSAMPLE_H


class Learning {

public:
    explicit Learning(int secondsToSleep);
    void CoutNoFlush();
    void CoutWithFlush();

private:

    void BitShiftTests();
};


#endif //CPP_LEARNING_STDSAMPLE_H
