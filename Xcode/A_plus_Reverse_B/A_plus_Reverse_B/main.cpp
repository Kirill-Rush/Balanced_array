//
//  main.cpp
//  A_plus_Reverse_B
//  Заданы числа a и b. Вычислите сумму чисел a и зеркального отображения b. Зеркальное отображение числа — это число, состоящее из тех же цифр в обратном порядке. Например, зеркальное отображение числа 230 — 32, а числа 0 — 0.
//  Created by Кирилл Глебов on 12.09.2021.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    long a, b, result;
    char b_char[15], b_reverse[15];
    int b_length;
    
    scanf("%ld %ld", &a, &b);
    sprintf(b_char, "%ld", b);
    b_length = (int)strlen(b_char);
    for(int i = 0; i < b_length; i++)
        b_reverse[i] = b_char[b_length - i - 1];
    result = atol(b_reverse) + a;
    printf("%ld", result);
    return 0;
}
