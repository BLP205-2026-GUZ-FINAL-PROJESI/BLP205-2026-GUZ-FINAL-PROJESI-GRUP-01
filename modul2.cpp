#include "modul2.h"
#include <iostream>

// --- YIGIN (STACK) FONKSIYONLARI ---

void yiginBaslat(YiginDugum*& top) {
    top = nullptr;
}

void yiginPush(YiginDugum*& top, const std::string& aciklama) {
    YiginDugum* yeni = new YiginDugum{aciklama, top};
    top = yeni;
}

bool yiginPop(YiginDugum*& top, std::string& cikarilan) {
    if (top == nullptr) {
        std::cout << "[UYARI] Islem gecmisi yigini bos! Geri alinacak islem yok.\n";
        return false;
    }
    YiginDugum* silinecek = top;
    cikarilan = silinecek->islemAciklamasi;
    top = top->next;
    delete silinecek;
    return true;
}

void yiginPeek(const YiginDugum* top) {
    if (top == nullptr) {
        std::cout << "[BILGI] Islem gecmisi yigini su anda bos.\n";
        return;
    }
    std::cout << "[PEEK / TOP] En son yapilan islem: " << top->islemAciklamasi << "\n";
}

void yiginListele(const YiginDugum* top) {
    if (top == nullptr) {
        std::cout << "[BILGI] Islem gecmisi yigini su anda bos.\n";
        return;
    }
    std::cout << "\n--- ISLEM GECMISI YIGINI (STACK - LIFO) ---\n";
    const YiginDugum* curr = top;
    int sira = 1;
    while (curr != nullptr) {
        std::cout << "  " << sira++ << ". " << curr->islemAciklamasi << "\n";
        curr = curr->next;
    }
}

void yiginTemizle(YiginDugum*& top) {
    while (top != nullptr) {
        YiginDugum* silinecek = top;
        top = top->next;
        delete silinecek;
    }
}

// --- KUYRUK (QUEUE) FONKSIYONLARI ---

void kuyrukBaslat(Kuyruk& q) {
    q.front = nullptr;
    q.rear = nullptr;
}

void kuyrukEnqueue(Kuyruk& q, const std::string& ogrenciNo, const std::string& adSoyad, const std::string& kitapAdi) {
    KuyrukDugum* yeni = new KuyrukDugum{ogrenciNo, adSoyad, kitapAdi, nullptr};
    if (q.rear == nullptr) {
        q.front = yeni;
        q.rear = yeni;
    } else {
        q.rear->next = yeni;
        q.rear = yeni;
    }
}

bool kuyrukDequeue(Kuyruk& q, std::string& cikarilanBilgi) {
    if (q.front == nullptr) {
        std::cout << "[UYARI] Bekleyen ogrenci kuyrugu bos! Hizmet verilecek ogrenci yok.\n";
        return false;
    }
    KuyrukDugum* silinecek = q.front;
    cikarilanBilgi = silinecek->ogrenciNo + " - " + silinecek->adSoyad +
                     " (Talep: " + silinecek->talepEdilenKitap + ")";
    q.front = q.front->next;
    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    delete silinecek;
    return true;
}

void kuyrukListele(const Kuyruk& q) {
    if (q.front == nullptr) {
        std::cout << "[BILGI] Odunc kitap bekleme kuyrugu su anda bos.\n";
        return;
    }
    std::cout << "\n--- BEKLEYEN OGRENCI KUYRUGU (QUEUE - FIFO) ---\n";
    const KuyrukDugum* curr = q.front;
    int sira = 1;
    while (curr != nullptr) {
        std::cout << "  " << sira++ << ". No: " << curr->ogrenciNo
                  << " | Ad-Soyad: " << curr->adSoyad
                  << " | Talep Edilen Kitap: " << curr->talepEdilenKitap << "\n";
        curr = curr->next;
    }
}

void kuyrukTemizle(Kuyruk& q) {
    while (q.front != nullptr) {
        KuyrukDugum* silinecek = q.front;
        q.front = q.front->next;
        delete silinecek;
    }
    q.rear = nullptr;
}
