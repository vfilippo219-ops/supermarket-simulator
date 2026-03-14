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
    std::string categoria;
public:
    Prodotto(std::string nw_nome, float nw_prezzo_acquisto, float nw_prezzo_vendita, int nw_quantita, std::string nw_categoria);

    // --- gets -------------------------
    std::string get_nome() const;
    float get_prezzo_acquisto() const;
    float get_prezzo_vendita() const;
    int get_quantita() const;
    std::string get_categoria() const;

    void comprato(int comprati);
    void set_quantita(int nw_quantita);
};

class Mercato {
private:
    std::string nome;
    float saldo;
    int giorno;
    std::vector<Prodotto> prodotti;
    std::vector<std::string> categorie;

    std::vector<Prodotto> magazzino;
    std::string ordinamento_magazzino;
    std::string ordinamento_prodotti;

    int clienti_tot = 0;
    float ricavo_tot = 0;
    float spesa_tot = 0;
    float profitto_tot = 0;
    std::vector<Prodotto> prodotti_venduti;

public:
    Mercato(std::string nw_nome);

    // --- carica da file --------------------------------------------
    void carica_prodotti(const std::string& filename);
    void carica_categorie_prodotti(const std::string& filename);
    
    // --- gets ------------------------
    std::string get_nome() const;
    float get_saldo() const;
    int get_giorno() const;

    // --- funzioni --------------------
    void aggiungi_prodotto(std::string nw_nome, float nw_prezzo_acquisto, float nw_prezzo_vendita, int nw_quantita, std::string nw_categoria);
    void passa_giorno();
    void venduto();
    void mostra_prodotti();
    void mostra_magazzino();
    int estrazione_clienti();
    float compra_prodotti();
    float vendi_prodotti(int clienti);
    void mostra_prodotti_venduti();

    // --- ordinamento prodotti ---------------------
    void ordina_prodotti_nome();
    void ordina_prodotti_prezzo_acquisto();
    void ordina_prodotti_prezzo_vendita();
    void ordina_prodotti_quantita();
    void ordina_prodotti_categoria();

    // --- ordinamento magazzino ----------------
    void ordina_magazzino_nome();
    void ordina_magazzino_prezzo_acquisto();
    void ordina_magazzino_prezzo_vendita();
    void ordina_magazzino_quantita();
    void ordina_magazzino_categoria();

    // --- Restock prodotti -----------------------
    void restock_prodotti();

    // --- end game ---------------------------
    void end_game();

};

#endif