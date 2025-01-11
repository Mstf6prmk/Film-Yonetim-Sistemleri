#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <locale.h>
#include <stdexcept> 
#include <algorithm> 

using namespace std;

struct Film {
    int id;
    string ad;
    string tur;
    string yonetmen;
    int sure;

    string toString() const;
    static Film fromString(const string& str);
};

void filmEkle(const string& dosyaAdi);
void filmListele(const string& dosyaAdi);
void filmAra(const string& dosyaAdi);
void filmGuncelle(const string& dosyaAdi);
void filmSil(const string& dosyaAdi);

int main() {
    setlocale(LC_ALL, "Turkish");

    string dosyaAdi = "filmler.txt";
    int secim;

    do {
        cout << "\n--- SINEMA OTOMASYONU ---\n";
        cout << "1. Film Ekle\n";
        cout << "2. Filmleri Listele\n";
        cout << "3. Film Ara\n";
        cout << "4. Film Güncelle\n";
        cout << "5. Film Sil\n";
        cout << "6. Çýkýþ\n";
        cout << "Seçiminiz: ";
        cin >> secim;

        switch (secim) {
            case 1: filmEkle(dosyaAdi); break;
            case 2: filmListele(dosyaAdi); break;
            case 3: filmAra(dosyaAdi); break;
            case 4: filmGuncelle(dosyaAdi); break;
            case 5: filmSil(dosyaAdi); break;
            case 6: cout << "Çýkýþ yapýlýyor...\n"; break;
            default: cout << "Geçersiz seçenek! Tekrar deneyiniz.\n"; break;
        }
    } while (secim != 6);

    return 0;
}

string Film::toString() const {
    stringstream ss;
    ss << id << "," << ad << "," << tur << "," << yonetmen << "," << sure;
    return ss.str();
}

Film Film::fromString(const string& str) {
    Film f;
    if (count(str.begin(), str.end(), ',') != 4) {
        throw runtime_error("Satýr formatý hatalý: " + str);
    }

    stringstream ss(str);
    string token;

    if (!getline(ss, token, ',') || !(stringstream(token) >> f.id)) {
        throw runtime_error("Geçersiz ID: " + token);
    }

    if (!getline(ss, token, ',')) {
        throw runtime_error("Geçersiz Ad: " + token);
    }
    f.ad = token;

    if (!getline(ss, token, ',')) {
        throw runtime_error("Geçersiz Tür: " + token);
    }
    f.tur = token;

    if (!getline(ss, token, ',')) {
        throw runtime_error("Geçersiz Yönetmen: " + token);
    }
    f.yonetmen = token;

    if (!getline(ss, token, ',') || !(stringstream(token) >> f.sure)) {
        throw runtime_error("Geçersiz Süre: " + token);
    }

    return f;
}

void filmEkle(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    ofstream dosya("filmler.txt", ios::app);
    if (!dosya) {
        cout << "Dosya açýlamadý!" << endl;
        return;
    }

    Film f;
    cout << "Film ID: ";
    cin >> f.id;
    cout << "Film Adý: ";
    cin.ignore();
    getline(cin, f.ad);
    cout << "Film Türü: ";
    getline(cin, f.tur);
    cout << "Yönetmen: ";
    getline(cin, f.yonetmen);
    cout << "Film Süresi (dakika): ";
    cin >> f.sure;

    dosya << f.toString() << endl;
    dosya.close();
    cout << "Film eklendi!" << endl;
}

void filmListele(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya açýlamadý!" << endl;
        return;
    }

    string line;
    bool veriBulundu = false;

    while (getline(dosya, line)) {
        try {
            Film f = Film::fromString(line);
            cout << "ID: " << f.id << ", Ad: " << f.ad << ", Tür: " << f.tur
                 << ", Yönetmen: " << f.yonetmen << ", Süre: " << f.sure << " dakika" << endl;
            veriBulundu = true;
        } catch (const runtime_error& e) {
            cerr << "Hata: " << e.what() << " - Bu satýr atlanýyor." << endl;
        }
    }

    if (!veriBulundu) {
        cout << "Hiç film verisi bulunamadý!" << endl;
    }

    dosya.close();
}

void filmAra(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    int arananID;
    cout << "Aramak istediðiniz film ID'sini girin: ";
    cin >> arananID;

    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya açýlamadý!" << endl;
        return;
    }

    string line;
    bool bulundu = false;
    while (getline(dosya, line)) {
        Film f = Film::fromString(line);
        if (f.id == arananID) {
            cout << "Bulunan Film: ID: " << f.id << ", Ad: " << f.ad << ", Tür: " << f.tur
                 << ", Yönetmen: " << f.yonetmen << ", Süre: " << f.sure << " dakika" << endl;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "ID ile uyumlu film bulunamadý!" << endl;
    }
    dosya.close();
}

void filmGuncelle(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    int guncellenecekID;
    cout << "Güncellemek istediðiniz film ID'sini girin: ";
    cin >> guncellenecekID;

    vector<Film> filmler;
    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya açýlamadý!" << endl;
        return;
    }

    string line;
    bool bulundu = false;
    while (getline(dosya, line)) {
        Film f = Film::fromString(line);
        if (f.id == guncellenecekID) {
            cout << "Mevcut Film: ID: " << f.id << ", Ad: " << f.ad << ", Tür: " << f.tur
                 << ", Yönetmen: " << f.yonetmen << ", Süre: " << f.sure << " dakika" << endl;
            cout << "Yeni Film Adý: ";
            cin.ignore();
            getline(cin, f.ad);
            cout << "Yeni Tür: ";
            getline(cin, f.tur);
            cout << "Yeni Yönetmen: ";
            getline(cin, f.yonetmen);
            cout << "Yeni Süre (dakika): ";
            cin >> f.sure;
            bulundu = true;
        }
        filmler.push_back(f);
    }

    dosya.close();

    if (bulundu) {
        ofstream dosyaYaz("filmler.txt", ios::trunc);
        for (size_t i = 0; i < filmler.size(); ++i) {
            dosyaYaz << filmler[i].toString() << endl;
        }
        dosyaYaz.close();
        cout << "Film baþarýyla güncellendi!" << endl;
    } else {
        cout << "ID ile uyumlu film bulunamadý!" << endl;
    }
}

void filmSil(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    int silinecekID;
    cout << "Silmek istediðiniz film ID'sini girin: ";
    cin >> silinecekID;

    vector<Film> filmler;
    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya açýlamadý!" << endl;
        return;
    }

    string line;
    bool bulundu = false;
    while (getline(dosya, line)) {
        Film f = Film::fromString(line);
        if (f.id != silinecekID) {
            filmler.push_back(f);
        } else {
            bulundu = true;
        }
    }

    dosya.close();

    if (bulundu) {
        ofstream dosyaYaz("filmler.txt", ios::trunc);
        for (size_t i = 0; i < filmler.size(); ++i) {
            dosyaYaz << filmler[i].toString() << endl;
        }
        dosyaYaz.close();
        cout << "Film baþarýyla silindi!" << endl;
    } else {
        cout << "ID ile uyumlu film bulunamadý!" << endl;
    }
}
