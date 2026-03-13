#ifndef FUNZIONI_HPP
#define FUNZIONI_HPP
#include <string>

void clear_screen();
void clear_input();
int get_int(const int min, const int max);
float get_float(const int min, const int max);
std::string get_nome();
int estrazione_clienti(int giorno);

#endif