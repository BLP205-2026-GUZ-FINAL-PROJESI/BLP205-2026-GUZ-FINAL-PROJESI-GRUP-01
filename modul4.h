#ifndef MODUL4_H
#define MODUL4_H

#include <string>

const int BINA_SAYISI = 6;

// Kampus grafi yapisi (2 boyutlu komsuluk matrisi)
struct KampusGraf {
    std::string binalar[BINA_SAYISI];
    int matris[BINA_SAYISI][BINA_SAYISI];
};

// Graf kurulumu ve listeleme
void kampusGrafOlustur(KampusGraf& g);
void binalariListele(const KampusGraf& g);
void matrisYazdir(const KampusGraf& g);

// Gezinme ve en kisa yol algoritmalari
void bfsGezinme(const KampusGraf& g, int baslangic);
void dfsGezinme(const KampusGraf& g, int baslangic);
void dijkstraEnKisaRota(const KampusGraf& g, int baslangic, int hedef);

#endif
