//
//  main.cpp
//  write_string
//
//  Created by Кирилл Глебов on 09.05.2021.
//
//  Задача: выписать строки из файла в порядке увеличения длины строки, причем если длина строк одинакова -
//  выписать их в лексикографическом убывании

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc/malloc.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define V vector

bool cmp(char* s1, char* s2) // компаратор, принимает 2 парам., возвращает результат сравнения
{
    return strcmp(s1,s2) >= 0;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    map<size_t, V<char*>> myMap;
    map<size_t, V<char*>>::iterator it; // итератор для нашей карты
    V<char*>::iterator jt; // итератор для вектора
    V<char*> map_element;
    size_t len_of_ss;
    char *ss;
    FILE *in;
    if ((in = fopen("/Users/kirillglebov/Documents/Xcode/write_string/write_string/write_string/string_for_code.txt", "r"))==NULL)
    {
        printf("Файл string_for_code не открыт!");
        exit(1);
    }
    ss = (char*) malloc (176*sizeof(char)); // выделение памяти для хранения строки из файла
    while(fgets(ss, 176, in))
    {
        len_of_ss = strlen(ss); // считаем длину строки
        myMap[len_of_ss].push_back(ss); // создаем элемент карты с ключом len_of_ss, элементом - вектором строк. Кладем строку в конец вектора
        ss = (char*) malloc (176*sizeof(char)); // выделяем память для хранения очередной строки из файла
    }
    printf("Список строк по установленным правилам:\n");
    for(it = myMap.begin(); it != myMap.end(); it++)
    {
        sort(it->second.begin(), it->second.end(), cmp); // сортировка элементов вектора, находящихся в одном ключе
        for(jt = it->second.begin(); jt != it->second.end(); jt++)
            printf("%lu - %s", it->first, *jt);
    }
    return 0;
}
