#pragma once

int GRandom(int min, int max)
{
    int val = 0;
    min = max - min;
    max = max - min;
    val = rand() % min + max;
    return val;
}