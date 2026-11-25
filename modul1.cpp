#include "modul1.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

void katalogBaslat(KitapKatalog& katalog) {
    katalog.head = nullptr;
    katalog.tail = nullptr;
}

bool kitapIdVarMi(const KitapKatalog& katalog, int id) {
    KitapDugum* curr = katalog.head;
    while (curr != nullptr) {
        if (curr->veri.id == id) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int katalogSayisi(const KitapKatalog& katalog) {
    int sayac = 0;
    KitapDugum* curr = katalog.head;
    while (curr != nullptr) {
        sayac++;
        curr = curr->next;
    }
    return sayac;
}

bool kitapBasaEkle(KitapKatalog& katalog, const Kitap& kitap) {
    if (kitap.sayfaSayisi <= 0) {
        std::cout << "[HATA] Sayfa sayisi 0'dan buyuk olmalidir.\n";
        return false;
    }
    if (kitapIdVarMi(katalog, kitap.id)) {
        std::cout << "[HATA] ID " << kitap.id << " zaten katalogda mevcut!\n";
        return false;
    }

    KitapDugum* yeni = new KitapDugum{kitap, nullptr, katalog.head};
    if (katalog.head == nullptr) {
        katalog.head = yeni;
        katalog.tail = yeni;
    } else {
        katalog.head->prev = yeni;
        katalog.head = yeni;
    }
    return true;
}

bool kitapSonaEkle(KitapKatalog& katalog, const Kitap& kitap) {
    if (kitap.sayfaSayisi <= 0) {
        std::cout << "[HATA] Sayfa sayisi 0'dan buyuk olmalidir.\n";
        return false;
    }
    if (kitapIdVarMi(katalog, kitap.id)) {
        std::cout << "[HATA] ID " << kitap.id << " zaten katalogda mevcut!\n";
        return false;
    }

    KitapDugum* yeni = new KitapDugum{kitap, katalog.tail, nullptr};
    if (katalog.tail == nullptr) {
        katalog.head = yeni;
        katalog.tail = yeni;
    } else {
        katalog.tail->next = yeni;
        katalog.tail = yeni;
    }
    return true;
}

bool kitapArayaEkle(KitapKatalog& katalog, int hedefId, const Kitap& kitap) {
    if (katalog.head == nullptr) {
        std::cout << "[UYARI] Katalog bos oldugu icin hedef ID bulunamadi.\n";
        return false;
    }
    if (kitap.sayfaSayisi <= 0) {
        std::cout << "[HATA] Sayfa sayisi 0'dan buyuk olmalidir.\n";
        return false;
    }
    if (kitapIdVarMi(katalog, kitap.id)) {
        std::cout << "[HATA] ID " << kitap.id << " zaten katalogda mevcut!\n";
        return false;
    }

    KitapDugum* hedef = katalog.head;
    while (hedef != nullptr && hedef->veri.id != hedefId) {
        hedef = hedef->next;
    }

    if (hedef == nullptr) {
        std::cout << "[HATA] Hedef kitap ID (" << hedefId << ") bulunamadi!\n";
        return false;
    }

    // Hedef ilk dugumse basa ekle
    if (hedef == katalog.head) {
        return kitapBasaEkle(katalog, kitap);
    }

    KitapDugum* yeni = new KitapDugum{kitap, hedef->prev, hedef};
    hedef->prev->next = yeni;
    hedef->prev = yeni;
    return true;
}

bool kitapSil(KitapKatalog& katalog, int id) {
    if (katalog.head == nullptr) {
        std::cout << "[UYARI] Katalog bos, silinecek kitap yok.\n";
        return false;
    }

    KitapDugum* curr = katalog.head;
    while (curr != nullptr && curr->veri.id != id) {
        curr = curr->next;
    }

    if (curr == nullptr) {
        std::cout << "[HATA] ID " << id << " katalogda bulunamadi!\n";
        return false;
    }

    if (curr == katalog.head && curr == katalog.tail) {
        katalog.head = nullptr;
        katalog.tail = nullptr;
    } else if (curr == katalog.head) {
        katalog.head = curr->next;
        katalog.head->prev = nullptr;
    } else if (curr == katalog.tail) {
        katalog.tail = curr->prev;
        katalog.tail->next = nullptr;
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    delete curr;
    return true;
}

static void kitapSatirYazdir(const Kitap& k) {
    std::cout << "  ID: " << std::setw(4) << k.id
              << " | Ad: " << std::setw(28) << std::left << k.ad
              << " | Yazar: " << std::setw(20) << std::left << k.yazar
              << std::right << " | Sayfa: " << k.sayfaSayisi << "\n";
}

void ileriListele(const KitapKatalog& katalog) {
    if (katalog.head == nullptr) {
        std::cout << "[BILGI] Kitap katalogu su anda bos.\n";
        return;
    }
    std::cout << "\n--- KITAPLAR (BASTAN SONA - next) ---\n";
    KitapDugum* curr = katalog.head;
    while (curr != nullptr) {
        kitapSatirYazdir(curr->veri);
        curr = curr->next;
    }
}

void geriListele(const KitapKatalog& katalog) {
    if (katalog.tail == nullptr) {
        std::cout << "[BILGI] Kitap katalogu su anda bos.\n";
        return;
    }
    std::cout << "\n--- KITAPLAR (SONDAN BASA - prev) ---\n";
    KitapDugum* curr = katalog.tail;
    while (curr != nullptr) {
        kitapSatirYazdir(curr->veri);
        curr = curr->prev;
    }
}

void katalogAnaliz(const KitapKatalog& katalog, int sayfaEsigi) {
    if (katalog.head == nullptr) {
        std::cout << "[BILGI] Katalog bos oldugu icin analiz yapilamiyor.\n";
        return;
    }

    int toplamKitap = 0;
    long long toplamSayfa = 0;
    KitapDugum* minDugum = katalog.head;
    KitapDugum* maxDugum = katalog.head;

    KitapDugum* curr = katalog.head;
    while (curr != nullptr) {
        toplamKitap++;
        toplamSayfa += curr->veri.sayfaSayisi;
        if (curr->veri.sayfaSayisi < minDugum->veri.sayfaSayisi) {
            minDugum = curr;
        }
        if (curr->veri.sayfaSayisi > maxDugum->veri.sayfaSayisi) {
            maxDugum = curr;
        }
        curr = curr->next;
    }

    double ortalama = static_cast<double>(toplamSayfa) / toplamKitap;

    std::cout << "\n--- KATALOG ISTATISTIK ANALIZI ---\n";
    std::cout << "Toplam Kitap Sayisi   : " << toplamKitap << "\n";
    std::cout << "Toplam Sayfa Sayisi   : " << toplamSayfa << "\n";
    std::cout << "Ortalama Sayfa Sayisi : " << std::fixed << std::setprecision(2) << ortalama << "\n";
    std::cout << "En Az Sayfali Kitap   : " << minDugum->veri.ad
              << " (" << minDugum->veri.sayfaSayisi << " sayfa)\n";
    std::cout << "En Cok Sayfali Kitap  : " << maxDugum->veri.ad
              << " (" << maxDugum->veri.sayfaSayisi << " sayfa)\n";

    std::cout << "\nSayfa Esigini (" << sayfaEsigi << ") Asan Kitaplar:\n";
    bool esikBulundu = false;
    curr = katalog.head;
    while (curr != nullptr) {
        if (curr->veri.sayfaSayisi > sayfaEsigi) {
            kitapSatirYazdir(curr->veri);
            esikBulundu = true;
        }
        curr = curr->next;
    }
    if (!esikBulundu) {
        std::cout << "  [BILGI] Bu esigi asan kitap bulunamadi.\n";
    }
}

void duyuruEkle(DuyuruDugum*& duyuruHead, const std::string& mesaj) {
    DuyuruDugum* yeni = new DuyuruDugum{mesaj, nullptr};
    if (duyuruHead == nullptr) {
        yeni->next = yeni;
        duyuruHead = yeni;
        return;
    }

    // Dairesel listenin son dugumunu bul
    DuyuruDugum* son = duyuruHead;
    while (son->next != duyuruHead) {
        son = son->next;
    }
    son->next = yeni;
    yeni->next = duyuruHead;
}

void duyuruListele(const DuyuruDugum* duyuruHead) {
    if (duyuruHead == nullptr) {
        std::cout << "[BILGI] Duyuru panosu su anda bos.\n";
        return;
    }

    std::cout << "\n--- DUYURU PANOSU (TEK YONLU DAIRESEL LISTE - 1 TAM TUR) ---\n";
    const DuyuruDugum* curr = duyuruHead;
    int sira = 1;
    do {
        std::cout << "  " << sira++ << ". " << curr->mesaj << "\n";
        curr = curr->next;
    } while (curr != duyuruHead);
    std::cout << "[BILGI] Baslangic dugumune geri donuldu (tam tur tamamlandi).\n";
}

bool katalogDosyayaYaz(const KitapKatalog& katalog, const std::string& dosyaAdi) {
    if (katalog.head == nullptr) {
        std::cout << "[UYARI] Katalog bos, dosyaya yazilacak kayit yok.\n";
        return false;
    }

    std::ofstream dosya(dosyaAdi.c_str());
    if (!dosya.is_open()) {
        std::cout << "[HATA] Dosya yazma icin acilamadi: " << dosyaAdi << "\n";
        return false;
    }

    KitapDugum* curr = katalog.head;
    int yazilan = 0;
    while (curr != nullptr) {
        dosya << curr->veri.id << "|"
              << curr->veri.ad << "|"
              << curr->veri.yazar << "|"
              << curr->veri.sayfaSayisi << "\n";
        yazilan++;
        curr = curr->next;
    }
    dosya.close();
    std::cout << "[OK] " << yazilan << " kitap kaydi '" << dosyaAdi << "' dosyasina yazildi.\n";
    return true;
}

bool katalogDosyadanOkuVeGoster(const std::string& dosyaAdi) {
    std::ifstream dosya(dosyaAdi.c_str());
    if (!dosya.is_open()) {
        std::cout << "[HATA] Dosya okuma icin acilamadi: " << dosyaAdi << "\n";
        return false;
    }

    std::cout << "\n--- DOSYADAN OKUNAN KATALOG KAYITLARI (" << dosyaAdi << ") ---\n";
    std::string satir;
    int okunan = 0;
    while (std::getline(dosya, satir)) {
        if (satir.empty()) {
            continue;
        }
        std::stringstream ss(satir);
        std::string idStr, ad, yazar, sayfaStr;
        if (std::getline(ss, idStr, '|') &&
            std::getline(ss, ad, '|') &&
            std::getline(ss, yazar, '|') &&
            std::getline(ss, sayfaStr, '|')) {
            okunan++;
            std::cout << "  ID: " << std::setw(4) << idStr
                      << " | Ad: " << std::setw(28) << std::left << ad
                      << " | Yazar: " << std::setw(20) << std::left << yazar
                      << std::right << " | Sayfa: " << sayfaStr << "\n";
        }
    }
    dosya.close();

    if (okunan == 0) {
        std::cout << "  [BILGI] Dosyada gecerli kayit bulunamadi.\n";
    } else {
        std::cout << "[OK] Toplam " << okunan << " satir dosyadan okundu.\n";
    }
    return true;
}

Kitap* katalogDiziyeAktar(const KitapKatalog& katalog, int& boyut) {
    boyut = katalogSayisi(katalog);
    if (boyut == 0) {
        return nullptr;
    }

    Kitap* dizi = new Kitap[boyut];
    KitapDugum* curr = katalog.head;
    int i = 0;
    while (curr != nullptr) {
        dizi[i++] = curr->veri;
        curr = curr->next;
    }
    return dizi;
}

void kitapListesiTemizle(KitapKatalog& katalog) {
    KitapDugum* curr = katalog.head;
    while (curr != nullptr) {
        KitapDugum* silinecek = curr;
        curr = curr->next;
        delete silinecek;
    }
    katalog.head = nullptr;
    katalog.tail = nullptr;
}

void duyuruListesiTemizle(DuyuruDugum*& duyuruHead) {
    if (duyuruHead == nullptr) {
        return;
    }
    DuyuruDugum* curr = duyuruHead->next;
    while (curr != duyuruHead) {
        DuyuruDugum* silinecek = curr;
        curr = curr->next;
        delete silinecek;
    }
    delete duyuruHead;
    duyuruHead = nullptr;
}
