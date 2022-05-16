#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "picosha2.h"

using namespace std;

extern const char alphanum[];

extern int stringLength;
    
char genRandom();

string genRandomString(int length);


string geraHash(string str);

bool testa(bool condicao, string mensagem);

#endif