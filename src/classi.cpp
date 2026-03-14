#include "classi.hpp"
#include "funzioni.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <algorithm>

// --- Prodotto ----------------------------------
Prodotto::Prodotto(std::string nw_nome, float nw_prezzo_acquisto, float nw_prezzo_vendita, int nw_quantita, std::string nw_categoria)
    : nome(nw_nome), prezzo_acquisto(nw_prezzo_acquisto), prezzo_vendita(nw_prezzo_vendita), quantita(nw_quantita), categoria(nw_categoria) {}

// --- gets ---------------------------
    
std::string Prodotto::get_nome() const {
    return nome;
}

float Prodotto::get_prezzo_acquisto() const {
    return prezzo_acquisto;
}

float Prodotto::get_prezzo_vendita() const {
    return prezzo_vendita;
}

int Prodotto::get_quantita() const {
    return quantita;
}

std::string Prodotto::get_categoria() const {
    return categoria;
}

void Prodotto::comprato(int comprati) {
    quantita -= comprati;
}

void Prodotto::set_quantita(int nw_quantita) {
    quantita = nw_quantita;
}
// ------------------------------------------------

// ==== Mercato ==================================
Mercato::Mercato(std::string nw_nome) : nome(nw_nome), saldo(100), giorno(1) {}

// --- carica prodotti da file -------------------------------
void Mercato::carica_prodotti(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Errore: file " << filename << " non trovato!\n";
        system("pause");
        return;
    }

    std::string riga;
    while (std::getline(in, riga)) {
        std::stringstream ss(riga);
        std::string nome, categoria, tmp;
        float prezzo_acquisto, prezzo_vendita;
        int quantita;

        std::getline(ss, nome, ';');
        std::getline(ss, tmp, ';'); prezzo_acquisto = std::stof(tmp);
        std::getline(ss, tmp, ';'); prezzo_vendita = std::stof(tmp);
        std::getline(ss, tmp, ';'); quantita = std::stof(tmp);
        std::getline(ss, categoria);

        aggiungi_prodotto(nome, prezzo_acquisto, prezzo_vendita, quantita, categoria);
        
    }
    in.close();
}

// --- carica categorie da file ------------------------------
void Mercato::carica_categorie_prodotti(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Errore: file '" << filename << "' non trovato!\n";
        return;
    }

    std::string cat;
    while (std::getline(in, cat)) {
        categorie.push_back(cat);
    }
    in.close();
}

std::string Mercato::get_nome() const {
    return nome;
}

float Mercato::get_saldo() const {
    return saldo;
}

int Mercato::get_giorno() const {
    return giorno;
}

// --------------------

void Mercato::aggiungi_prodotto(std::string nw_nome, float nw_prezzo_acquisto, float nw_prezzo_vendita, int nw_quantita, std::string nw_categoria) {
    Prodotto prodotto = {nw_nome, nw_prezzo_acquisto, nw_prezzo_vendita, nw_quantita, nw_categoria};
    prodotti.push_back(prodotto);
}

void Mercato::passa_giorno() {
    giorno += 1;
}

void Mercato::mostra_prodotti() {
    std::cout << "----- Ordinamento per '" << ordinamento_prodotti << "' -----\n\n";
    for (size_t i = 0; i < prodotti.size(); i++) {
        std::cout << i + 1 
                  << ". " << prodotti[i].get_nome()
                  << " | Acquisto: (" << prodotti[i].get_prezzo_acquisto() << "€)"
                  << " | Vendita: (" << prodotti[i].get_prezzo_vendita() << "€)" 
                  << " | Quantita: '" << prodotti[i].get_quantita() << "'"
                  << " | '" << prodotti[i].get_categoria() << "'" << std::endl;
    }
}

void Mercato::mostra_magazzino() {
    if (magazzino.empty()) {
        std::cout << "\nMagazzino vuoto!\n\n";
        system("pause");
        return;
    }
    std::cout << "\n----- Ordinamento per '" << ordinamento_magazzino << "' -----\n";
    for (size_t i = 0; i < magazzino.size(); i++) {
        std::cout << i + 1
                  << ". " << magazzino[i].get_nome()
                  << " | Acquisto: (" << magazzino[i].get_prezzo_acquisto() << "€)"
                  << " | Vendita: (" << magazzino[i].get_prezzo_vendita() << "€)"
                  << " | Quantita: '" << magazzino[i].get_quantita() << "'"
                  << " | '" << magazzino[i].get_categoria() << "'" << std::endl;
    }
    std::cout << std::endl;
    system("pause");
}

int Mercato::estrazione_clienti() {
    int clienti = giorno + (rand() % giorno);
    if (clienti == 0) clienti = 1;
    clienti_tot += clienti;
    return clienti;
}

float Mercato::compra_prodotti() {
    float spesa_totale = 0;
    while (1) {
        std::cout << "Saldo: " << saldo << "€" << std::endl;
        mostra_prodotti();
        std::cout << "\n0. Esci" << std::endl
                  << "Scegli: ";
        int scelta = get_int(0, prodotti.size());
        scelta--;
        if (scelta == -1) break;
        else {
            if (saldo < prodotti[scelta].get_prezzo_acquisto()) {
                std::cout << "Saldo non disponibile!\n";
                continue;
            }
            std::cout << "\nInserire numero prodotti da comprare: ";
            int comprati = get_int(0, prodotti[scelta].get_quantita());

            float spesa = prodotti[scelta].get_prezzo_acquisto() * comprati;
            
            if (saldo < spesa) {
                std::cout << "Saldo non disponibile!\n";
                continue;
            }
            spesa_totale += spesa;
            std::cout << "\n" << comprati << " '" << prodotti[scelta].get_nome() << "' comprati per (" << spesa << "€)!\n"
                      << "─────────────────────────────────────────────\n\n";

            // cerca prodotto in magazzino
            bool trovato = false;
            for (auto &p : magazzino) {
                if (p.get_nome() == prodotti[scelta].get_nome()) {
                    p.set_quantita(p.get_quantita() + comprati);
                    trovato = true;
                    break;
                }
            }
            if (!trovato) {
                Prodotto in_magazzino = {prodotti[scelta].get_nome(),
                                         prodotti[scelta].get_prezzo_acquisto(),
                                         prodotti[scelta].get_prezzo_vendita(),
                                         comprati,
                                         prodotti[scelta].get_categoria()};
                magazzino.push_back(in_magazzino);
            }
            prodotti[scelta].comprato(comprati);
            saldo -= spesa;
        }
    }
    spesa_tot += spesa_totale;
    return spesa_totale;
}

float Mercato::vendi_prodotti(int clienti) {
    float ricavo = 0;
    if (magazzino.empty()) {
        std::cout << "\nMagazzino vuoto! La gente è andata a casa!\n";
        return 0;
    }
    for (int i = 0; i < clienti; i++) {
        int prodotto_acquistato = rand() % magazzino.size();
        if (magazzino[prodotto_acquistato].get_quantita() <= 0) continue;

        int acquistati = rand() % giorno + 1;
        if (acquistati > magazzino[prodotto_acquistato].get_quantita()) acquistati = magazzino[prodotto_acquistato].get_quantita();
        ricavo += (magazzino[prodotto_acquistato].get_prezzo_vendita() * acquistati);
        magazzino[prodotto_acquistato].comprato(acquistati);
    }
    saldo += ricavo;
    ricavo_tot += ricavo;
    return ricavo;
}

// --- ordinamento prodotti ----------------------------------
void Mercato::ordina_prodotti_nome() {
    ordinamento_prodotti = "NOME";
    std::sort(prodotti.begin(), prodotti.end(), [](const Prodotto &a, const Prodotto &b) {
        std::string p1 = a.get_nome();
        std::string p2 = b.get_nome();

        std::transform(p1.begin(), p1.end(), p1.begin(), ::tolower);
        std::transform(p2.begin(), p2.end(), p2.begin(), ::tolower);

        return p1 < p2;
    });
}

void Mercato::ordina_prodotti_prezzo_acquisto() {
    ordinamento_prodotti = "PREZZO DI ACQUISTO";
    std::sort(prodotti.begin(), prodotti.end(), [](const Prodotto &a, const Prodotto &b) {
        return a.get_prezzo_acquisto() > b.get_prezzo_acquisto();
    });
}

void Mercato::ordina_prodotti_prezzo_vendita() {
    ordinamento_prodotti = "PREZZO DI VENDITA";
    std::sort(prodotti.begin(), prodotti.end(), [](const Prodotto &a, const Prodotto &b) {
        return a.get_prezzo_vendita() > b.get_prezzo_vendita();
    });
}

void Mercato::ordina_prodotti_quantita() {
    ordinamento_prodotti = "QUANTITA";
    std::sort(prodotti.begin(), prodotti.end(), [](const Prodotto &a, const Prodotto &b) {
        return a.get_quantita() > b.get_quantita();
    });
}

void Mercato::ordina_prodotti_categoria() {
    ordinamento_prodotti = "CATEGORIA";
    std::sort(prodotti.begin(), prodotti.end(), [](const Prodotto &a, const Prodotto &b) {
        std::string p1 = a.get_categoria();
        std::string p2 = b.get_categoria();

        std::transform(p1.begin(), p1.end(), p1.begin(), ::tolower);
        std::transform(p2.begin(), p2.end(), p2.begin(), ::tolower);

        return p1 < p2;
    });
}

// --- ordinamento magazzino ------------------------------------
void Mercato::ordina_magazzino_nome() {
    ordinamento_magazzino = "NOME";
    std::sort(magazzino.begin(), magazzino.end(), [](const Prodotto &a, const Prodotto &b) {
        std::string p1 = a.get_nome();
        std::string p2 = b.get_nome();

        std::transform(p1.begin(), p1.end(), p1.begin(), ::tolower);
        std::transform(p2.begin(), p2.end(), p2.begin(), ::tolower);
        
        return p1 < p2;
    });
}

void Mercato::ordina_magazzino_prezzo_acquisto() {
    ordinamento_magazzino = "PREZZO DI ACQUISTO";
    std::sort(magazzino.begin(), magazzino.end(), [](const Prodotto &a, const Prodotto &b) {
        return a.get_prezzo_acquisto() > b.get_prezzo_acquisto();
    });
}

void Mercato::ordina_magazzino_prezzo_vendita() {
    ordinamento_magazzino = "PREZZO DI VENDITA";
    std::sort(magazzino.begin(), magazzino.end(), [](const Prodotto &a, const Prodotto &b) {
        return a.get_prezzo_vendita() > b.get_prezzo_vendita();
    });
}

void Mercato::ordina_magazzino_quantita() {
    ordinamento_magazzino = "QUANTITÀ";
    std::sort(magazzino.begin(), magazzino.end(), [](const Prodotto &a, const Prodotto &b) {
        return a.get_quantita() > b.get_quantita();
    });
}

void Mercato::ordina_magazzino_categoria() {
    ordinamento_magazzino = "CATEGORIA";
    std::sort(magazzino.begin(), magazzino.end(), [](const Prodotto &a, const Prodotto &b) {
        std::string p1 = a.get_categoria();
        std::string p2 = b.get_categoria();

        std::transform(p1.begin(), p1.end(), p1.begin(), ::tolower);
        std::transform(p2.begin(), p2.end(), p2.begin(), ::tolower);

        return p1 < p2;
    });
}

// ---- Restock prodotti -------------------------------
void Mercato::restock_prodotti() {
    int restock = rand() % giorno + 1;
    for (auto &p : prodotti) {
        p.set_quantita(p.get_quantita() + restock);
    }
}

// --- end game ----------------------
void Mercato::end_game() {
    clear_screen();
    profitto_tot = ricavo_tot - spesa_tot;
    std::cout << "\nComplimenti!!! Hai superato '" << GIORNO_FINALE << "' giorni!\n"
              << "\nSaldo: " << saldo << std::endl 
              << "Clienti totali: " << clienti_tot << std::endl
              << "Ricavo totale: " << ricavo_tot << std::endl
              << "Spesa totale: " << spesa_tot << std::endl
              << "Profitto totale: " << profitto_tot << std::endl;
    system("pause");
}
