//
//  main.cpp
//  Box to pull
//
//  Created by Кирилл Глебов on 18.03.2021.
//
// "Коробку - тянуть!"
// https://codeforces.com/problemset/problem/1428/A


#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
    int x1, x2, y1, y2, t = 0;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if ((x1 == x2) || (y1 == y2))
        t = abs(x2 - x1) + abs(y2 - y1);
    else
        t = abs(x2 - x1) + abs(y2 - y1) + 2;
    printf("%d", t);
    return 0;
}
