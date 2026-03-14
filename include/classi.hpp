#ifndef CLASSI_HPP
#define CLASSI_HPP
#include <string>
#include <vector>

extern const int GIORNO_FINALE;

class Prodotto{
private:
    std::string nome;
    float prezzo_acquisto;
    float prezzo_vendita;
    int quantita;
public:
    Prodotto(std::string nw_nome, float nw_prezzo_acquisto, float nw_prezzo_vendita, int nw_quantita);

    // --- gets -------------------------
    std::string get_nome() const;
    float get_prezzo_acquisto() const;
    float get_prezzo_vendita() const;
    int get_quantita() const;

    void comprato(int comprati);
    void set_quantita(int nw_quantita);
};

class Mercato {
private:
    std::string nome;
    float saldo;
    int giorno;
    std::vector<Prodotto> prodotti;
    std::vector<Prodotto> magazzino;
    std::string ordinamento;

    int clienti_tot = 0;
    float ricavo_tot = 0;
    float spesa_tot = 0;
    float profitto_tot = 0;

public:
    Mercato(std::string nw_nome);

    void carica_prodotti(const std::string& filename);
    // --- gets ------------------------
    std::string get_nome() const;
    float get_saldo() const;
    int get_giorno() const;

    // --- funzioni --------------------
    void aggiungi_prodotto(std::string nw_nome, float nw_prezzo_acquisto, float nw_prezzo_vendita, int nw_quantita);
    void passa_giorno();
    void venduto();
    void mostra_prodotti();
    void mostra_magazzino();
    int estrazione_clienti();
    float compra_prodotti();
    float vendi_prodotti(int clienti);

    // --- ordinamento magazzino ----------------
    void ordina_magazzino_nome();
    void ordina_magazzino_prezzo_acquisto();
    void ordina_magazzino_prezzo_vendita();
    void ordina_magazzino_quantita();

    // --- Restock prodotti -----------------------
    void restock_prodotti();

    // --- end game ---------------------------
    void end_game();

};

#endif