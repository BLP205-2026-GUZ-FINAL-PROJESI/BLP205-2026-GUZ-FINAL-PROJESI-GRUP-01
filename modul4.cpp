#include "modul4.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>

static bool gecerliBinaMi(int indeks) {
    return indeks >= 0 && indeks < BINA_SAYISI;
}

void kampusGrafOlustur(KampusGraf& g) {
    g.binalar[0] = "Merkez Kutuphane";
    g.binalar[1] = "MYO Bilgisayar Lab";
    g.binalar[2] = "Muhendislik Binasi";
    g.binalar[3] = "Ogrenci Isleri";
    g.binalar[4] = "Yemekhane ve Sosyal Alan";
    g.binalar[5] = "Konferans Salonu";

    for (int i = 0; i < BINA_SAYISI; ++i) {
        for (int j = 0; j < BINA_SAYISI; ++j) {
            g.matris[i][j] = 0;
        }
    }

    // Yonsuz agirlikli kampus yurume mesafeleri (metre)
    auto kenarEkle = [&](int u, int v, int mesafe) {
        g.matris[u][v] = mesafe;
        g.matris[v][u] = mesafe;
    };

    kenarEkle(0, 1, 120);
    kenarEkle(0, 2, 200);
    kenarEkle(0, 3, 150);
    kenarEkle(1, 2, 90);
    kenarEkle(1, 4, 180);
    kenarEkle(2, 4, 110);
    kenarEkle(2, 5, 250);
    kenarEkle(3, 4, 130);
    kenarEkle(3, 5, 300);
    kenarEkle(4, 5, 140);
}

void binalariListele(const KampusGraf& g) {
    std::cout << "\n--- KAMPUS BIRIMLERI ---\n";
    for (int i = 0; i < BINA_SAYISI; ++i) {
        std::cout << "  [" << i << "] " << g.binalar[i] << "\n";
    }
}

void matrisYazdir(const KampusGraf& g) {
    binalariListele(g);
    std::cout << "\n--- KAMPUS KOMSULUK MATRISI (METRE, 0 = DOGRUDAN YOL YOK) ---\n    ";
    for (int j = 0; j < BINA_SAYISI; ++j) {
        std::cout << std::setw(6) << j;
    }
    std::cout << "\n    --------------------------------------\n";

    for (int i = 0; i < BINA_SAYISI; ++i) {
        std::cout << "[" << i << "] ";
        for (int j = 0; j < BINA_SAYISI; ++j) {
            std::cout << std::setw(6) << g.matris[i][j];
        }
        std::cout << "  (" << g.binalar[i] << ")\n";
    }
}

void bfsGezinme(const KampusGraf& g, int baslangic) {
    if (!gecerliBinaMi(baslangic)) {
        std::cout << "[HATA] Gecersiz baslangic bina numarasi! (0-" << BINA_SAYISI - 1 << ")\n";
        return;
    }

    bool ziyaret[BINA_SAYISI] = {false};
    std::queue<int> kuyruk;

    ziyaret[baslangic] = true;
    kuyruk.push(baslangic);

    std::cout << "\n--- BFS GEZINMESI (Baslangic: " << g.binalar[baslangic] << ") ---\n  ";
    bool ilk = true;
    while (!kuyruk.empty()) {
        int suAn = kuyruk.front();
        kuyruk.pop();

        if (!ilk) {
            std::cout << " -> ";
        }
        std::cout << "[" << suAn << "] " << g.binalar[suAn];
        ilk = false;

        for (int komsu = 0; komsu < BINA_SAYISI; ++komsu) {
            if (g.matris[suAn][komsu] > 0 && !ziyaret[komsu]) {
                ziyaret[komsu] = true;
                kuyruk.push(komsu);
            }
        }
    }
    std::cout << "\n";
}

static void dfsYardimci(const KampusGraf& g, int suAn, bool ziyaret[], bool& ilk) {
    ziyaret[suAn] = true;
    if (!ilk) {
        std::cout << " -> ";
    }
    std::cout << "[" << suAn << "] " << g.binalar[suAn];
    ilk = false;

    for (int komsu = 0; komsu < BINA_SAYISI; ++komsu) {
        if (g.matris[suAn][komsu] > 0 && !ziyaret[komsu]) {
            dfsYardimci(g, komsu, ziyaret, ilk);
        }
    }
}

void dfsGezinme(const KampusGraf& g, int baslangic) {
    if (!gecerliBinaMi(baslangic)) {
        std::cout << "[HATA] Gecersiz baslangic bina numarasi! (0-" << BINA_SAYISI - 1 << ")\n";
        return;
    }

    bool ziyaret[BINA_SAYISI] = {false};
    bool ilk = true;
    std::cout << "\n--- DFS GEZINMESI (Baslangic: " << g.binalar[baslangic] << ") ---\n  ";
    dfsYardimci(g, baslangic, ziyaret, ilk);
    std::cout << "\n";
}

void dijkstraEnKisaRota(const KampusGraf& g, int baslangic, int hedef) {
    if (!gecerliBinaMi(baslangic) || !gecerliBinaMi(hedef)) {
        std::cout << "[HATA] Gecersiz bina numarasi! (0-" << BINA_SAYISI - 1 << ")\n";
        return;
    }

    if (baslangic == hedef) {
        std::cout << "[BILGI] Baslangic ve hedef ayni birim: " << g.binalar[baslangic]
                  << " (Mesafe: 0 metre)\n";
        return;
    }

    const int SONSUZ = std::numeric_limits<int>::max();
    int mesafe[BINA_SAYISI];
    int onceki[BINA_SAYISI];
    bool islendi[BINA_SAYISI];

    for (int i = 0; i < BINA_SAYISI; ++i) {
        mesafe[i] = SONSUZ;
        onceki[i] = -1;
        islendi[i] = false;
    }
    mesafe[baslangic] = 0;

    for (int adim = 0; adim < BINA_SAYISI - 1; ++adim) {
        int minMesafe = SONSUZ;
        int u = -1;
        for (int i = 0; i < BINA_SAYISI; ++i) {
            if (!islendi[i] && mesafe[i] < minMesafe) {
                minMesafe = mesafe[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }
        islendi[u] = true;

        for (int v = 0; v < BINA_SAYISI; ++v) {
            if (!islendi[v] && g.matris[u][v] > 0 && mesafe[u] != SONSUZ) {
                int yeniMesafe = mesafe[u] + g.matris[u][v];
                if (yeniMesafe < mesafe[v]) {
                    mesafe[v] = yeniMesafe;
                    onceki[v] = u;
                }
            }
        }
    }

    if (mesafe[hedef] == SONSUZ) {
        std::cout << "[UYARI] " << g.binalar[baslangic] << " ile " << g.binalar[hedef]
                  << " arasinda ulasilabilir bir rota yok.\n";
        return;
    }

    // Rotayi geriden topla
    int rota[BINA_SAYISI];
    int rotaUzunlugu = 0;
    for (int curr = hedef; curr != -1; curr = onceki[curr]) {
        rota[rotaUzunlugu++] = curr;
    }

    std::cout << "\n--- DIJKSTRA EN KISA KAMPUS ROTASI ---\n";
    std::cout << "Baslangic : " << g.binalar[baslangic] << "\n";
    std::cout << "Hedef     : " << g.binalar[hedef] << "\n";
    std::cout << "Mesafe    : " << mesafe[hedef] << " metre\n";
    std::cout << "Rota      : ";
    for (int i = rotaUzunlugu - 1; i >= 0; --i) {
        std::cout << "[" << rota[i] << "] " << g.binalar[rota[i]];
        if (i > 0) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n";
}
