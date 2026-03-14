#include "funzioni.hpp"
#include <iostream>
#include <limits>
#include <time.h>

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int get_int(const int min, const int max) {
    while (1) {
        int num;
        if ((std::cin >> num) && num >= min && num <= max) return num;
        std::cout << "Numero non valido! Riprova: ";
        clear_input();    
    }
}

float get_float(const int min, const int max) {
    while (1) {
        int num;
        if ((std::cin >> num) && num >= min && num <= max) return num;
        std::cout << "Numero non valido! Riprova: ";
        clear_input();
    }
}

std::string get_nome() {
    std::string nome;
    while (1) {
        if (std::getline(std::cin, nome) && !nome.empty()) return nome;
        std::cout << "Valore non valido! Riprova: ";
        clear_input();
    }
    return nome;
}
