#ifndef VERI_YAPILARI_H
#define VERI_YAPILARI_H

#include <iostream>
#include <limits>
#include <string>

// Tum modullerde ortak kullanilan kitap veri yapisi
struct Kitap {
    int id;
    std::string ad;
    std::string yazar;
    int sayfaSayisi;
};

// Kullanicidan guvenli sekilde tam sayi okur (hatali giriste donguye girmez)
inline int tamSayiOku(const std::string& mesaj) {
    int deger;
    while (true) {
        std::cout << mesaj;
        if (std::cin >> deger) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return deger;
        }
        std::cout << "[HATA] Gecersiz sayi girisi! Lutfen bir tam sayi giriniz.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Kullanicidan bos olmayan metin satiri okur
inline std::string metinOku(const std::string& mesaj) {
    std::string satir;
    while (true) {
        std::cout << mesaj;
        std::getline(std::cin, satir);
        // Bastaki ve sondaki bosluklari temizle
        size_t bas = satir.find_first_not_of(" \t\r\n");
        if (bas != std::string::npos) {
            size_t son = satir.find_last_not_of(" \t\r\n");
            return satir.substr(bas, son - bas + 1);
        }
        std::cout << "[HATA] Bos deger girilemez! Lutfen tekrar deneyiniz.\n";
    }
}

#endif
