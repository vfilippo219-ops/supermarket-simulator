#include "classi.hpp"
#include "funzioni.hpp"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>

const int GIORNO_FINALE = 30;

#define FILE_PRODOTTI "/files/prodotti_supermarket.txt"
#define FILE_CATEGORIE_PRODOTTI "/files/categorie_prodotti_supermarket.txt"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::string root = (argc > 1) ? argv[1] : ".";
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Benvenuto a supermarket simulator!" << std::endl
              << "Inserisci il nome del negozio: ";
    std::string nome_negozio = get_nome();
    Mercato mercato(nome_negozio);
    mercato.carica_prodotti(root + FILE_PRODOTTI);
    mercato.carica_categorie_prodotti(root + FILE_CATEGORIE_PRODOTTI);
    mercato.ordina_prodotti_categoria();
    mercato.ordina_magazzino_nome();

    while (mercato.get_giorno() <= GIORNO_FINALE) {
        float spesa, ricavo, profitto;
        clear_screen();
        std::cout << "───────────────────────────────────────\n"
                  << "------- " << nome_negozio << "'s Menù -------\n"
                  << "Giorno: " << mercato.get_giorno() << " | Saldo: " << mercato.get_saldo() << "€" << std::endl
                  << "1. Acquista" << std::endl
                  << "2. Apri" << std::endl
                  << "3. Mostra magazzino" << std::endl
                  << "4. Mostra prodotti" << std::endl
                  << "5. Cambia ordinamento magazzino" << std::endl
                  << "6. Cambia ordinamento prodotti" << std::endl
                  << "0. Esci" << std::endl
                  << "Scegli: ";
        int scelta = get_int(0, 6);

        switch (scelta) {
        case 0:
            std::cout << "\nGrazie per aver giocato!\n";
            system("pause");
            return 0;
        case 1:
            clear_screen();
            std::cout << "──────── Acquisto prodotti ────────\n";
            spesa = mercato.compra_prodotti();
            break;
        case 2:
        {
            clear_screen();
            int clienti = mercato.estrazione_clienti();
            ricavo = mercato.vendi_prodotti(clienti);
            profitto = ricavo - spesa;
            std::cout << "───── Recap giorno '" << mercato.get_giorno() << "' ─────\n"
                      << "Clienti: " << clienti << std::endl
                      << "Ricavo: " << ricavo << "€" << std::endl
                      << "Spesa: " << spesa << "€" << std::endl
                      << "Profitto: " << profitto << "€" << std::endl
                      << "Saldo: " << mercato.get_saldo() << "€" << std::endl;
            spesa=0;ricavo=0;profitto=0;

            std::cout << "\nPremi un tasto per passare al giorno successivo!\n";
            clear_input();
            getchar();
            mercato.passa_giorno();
            mercato.restock_prodotti();
            break;
        }
        case 3:
            clear_screen();
            std::cout << "────────────── MAGAZZINO ──────────────\n";
            mercato.mostra_magazzino();
            break;
        case 4:
            clear_screen();
            std::cout << "────────────── PRODOTTI ──────────────\n";
            mercato.mostra_prodotti();
            std::cout << std::endl;
            system("pause");
            break;
        case 5:
        {
            clear_screen();
            std::cout << "──── Scegli ordinamento magazzino ────\n"
                      << "1. Per nome" << std::endl
                      << "2. Per prezzo di acquisto" << std::endl
                      << "3. Per prezzo di vendita" << std::endl
                      << "4. Per quantità" << std::endl
                      << "5. Per categoria" << std::endl
                      << "0. Esci" << std::endl
                      << "Scegli: ";
            int ordinamento = get_int(0, 5);

            switch (ordinamento) {
            case 0:
                break;
            case 1:
                mercato.ordina_magazzino_nome();
                break;
            case 2:
                mercato.ordina_magazzino_prezzo_acquisto();
                break;
            case 3:
                mercato.ordina_magazzino_prezzo_vendita();
                break;
            case 4:
                mercato.ordina_magazzino_quantita();
                break;
            case 5:
                mercato.ordina_magazzino_categoria();
                break;
            }
            if (ordinamento == 0) break;
            
            clear_screen();
            mercato.mostra_magazzino();
            break;
        }
        case 6:
        {
            clear_screen();
            std::cout << "────── Scegli ordinamento prodotti ──────\n"
                      << "1. Per nome" << std::endl
                      << "2. Per prezzo di acquisto" << std::endl
                      << "3. Per prezzo di vendita" << std::endl
                      << "4. Per quantità" << std::endl
                      << "5. Per categoria" << std::endl
                      << "0. Esci" << std::endl
                      << "Scegli: ";
            int ordinamento = get_int(0, 5);

            switch (ordinamento) {
            case 0:
                break;
            case 1:
                mercato.ordina_prodotti_nome();
                break;
            case 2:
                mercato.ordina_prodotti_prezzo_acquisto();
                break;
            case 3:
                mercato.ordina_prodotti_prezzo_vendita();
                break;
            case 4:
                mercato.ordina_prodotti_quantita();
                break;
            case 5:
                mercato.ordina_prodotti_categoria();
                break;
            }
            if (ordinamento == 0) break;

            clear_screen();
            mercato.mostra_prodotti();
            std::cout << std::endl;
            system("pause");
            break;
        }
        }
    }
    mercato.end_game();
    return 0;
}