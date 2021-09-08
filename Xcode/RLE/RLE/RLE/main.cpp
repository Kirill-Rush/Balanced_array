//
//  main.cpp
//  RLE
//  Данная программа "сжимает" строку методом RLE. То есть вместо повторяющихся друг за другом букв пишется
//  данная буква и количество повторений
//
//  Created by Кирилл Глебов on 08.09.2021.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::string str, new_str;
    int len_of_str, count = 1;
    char now_word;
    
    std::cin >> str;
    len_of_str = (int)str.size();
    now_word = str[0];
    for(int i = 1; i < len_of_str; i++)
    {
        if(str[i] == now_word)
            count++;
        else
        {
            (count == 1) ? (new_str += now_word) : (new_str += now_word + std::to_string(count));
            now_word = str[i];
            count = 1;
        }
    }
    new_str += now_word + std::to_string(count);
    std::cout << new_str << std::endl;
    return 0;
}
