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
        cout << "4. Film G�ncelle\n";
        cout << "5. Film Sil\n";
        cout << "6. ��k��\n";
        cout << "Se�iminiz: ";
        cin >> secim;

        switch (secim) {
            case 1: filmEkle(dosyaAdi); break;
            case 2: filmListele(dosyaAdi); break;
            case 3: filmAra(dosyaAdi); break;
            case 4: filmGuncelle(dosyaAdi); break;
            case 5: filmSil(dosyaAdi); break;
            case 6: cout << "��k�� yap�l�yor...\n"; break;
            default: cout << "Ge�ersiz se�enek! Tekrar deneyiniz.\n"; break;
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
        throw runtime_error("Sat�r format� hatal�: " + str);
    }

    stringstream ss(str);
    string token;

    if (!getline(ss, token, ',') || !(stringstream(token) >> f.id)) {
        throw runtime_error("Ge�ersiz ID: " + token);
    }

    if (!getline(ss, token, ',')) {
        throw runtime_error("Ge�ersiz Ad: " + token);
    }
    f.ad = token;

    if (!getline(ss, token, ',')) {
        throw runtime_error("Ge�ersiz T�r: " + token);
    }
    f.tur = token;

    if (!getline(ss, token, ',')) {
        throw runtime_error("Ge�ersiz Y�netmen: " + token);
    }
    f.yonetmen = token;

    if (!getline(ss, token, ',') || !(stringstream(token) >> f.sure)) {
        throw runtime_error("Ge�ersiz S�re: " + token);
    }

    return f;
}

void filmEkle(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    ofstream dosya("filmler.txt", ios::app);
    if (!dosya) {
        cout << "Dosya a��lamad�!" << endl;
        return;
    }

    Film f;
    cout << "Film ID: ";
    cin >> f.id;
    cout << "Film Ad�: ";
    cin.ignore();
    getline(cin, f.ad);
    cout << "Film T�r�: ";
    getline(cin, f.tur);
    cout << "Y�netmen: ";
    getline(cin, f.yonetmen);
    cout << "Film S�resi (dakika): ";
    cin >> f.sure;

    dosya << f.toString() << endl;
    dosya.close();
    cout << "Film eklendi!" << endl;
}

void filmListele(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya a��lamad�!" << endl;
        return;
    }

    string line;
    bool veriBulundu = false;

    while (getline(dosya, line)) {
        try {
            Film f = Film::fromString(line);
            cout << "ID: " << f.id << ", Ad: " << f.ad << ", T�r: " << f.tur
                 << ", Y�netmen: " << f.yonetmen << ", S�re: " << f.sure << " dakika" << endl;
            veriBulundu = true;
        } catch (const runtime_error& e) {
            cerr << "Hata: " << e.what() << " - Bu sat�r atlan�yor." << endl;
        }
    }

    if (!veriBulundu) {
        cout << "Hi� film verisi bulunamad�!" << endl;
    }

    dosya.close();
}

void filmAra(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    int arananID;
    cout << "Aramak istedi�iniz film ID'sini girin: ";
    cin >> arananID;

    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya a��lamad�!" << endl;
        return;
    }

    string line;
    bool bulundu = false;
    while (getline(dosya, line)) {
        Film f = Film::fromString(line);
        if (f.id == arananID) {
            cout << "Bulunan Film: ID: " << f.id << ", Ad: " << f.ad << ", T�r: " << f.tur
                 << ", Y�netmen: " << f.yonetmen << ", S�re: " << f.sure << " dakika" << endl;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "ID ile uyumlu film bulunamad�!" << endl;
    }
    dosya.close();
}

void filmGuncelle(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    int guncellenecekID;
    cout << "G�ncellemek istedi�iniz film ID'sini girin: ";
    cin >> guncellenecekID;

    vector<Film> filmler;
    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya a��lamad�!" << endl;
        return;
    }

    string line;
    bool bulundu = false;
    while (getline(dosya, line)) {
        Film f = Film::fromString(line);
        if (f.id == guncellenecekID) {
            cout << "Mevcut Film: ID: " << f.id << ", Ad: " << f.ad << ", T�r: " << f.tur
                 << ", Y�netmen: " << f.yonetmen << ", S�re: " << f.sure << " dakika" << endl;
            cout << "Yeni Film Ad�: ";
            cin.ignore();
            getline(cin, f.ad);
            cout << "Yeni T�r: ";
            getline(cin, f.tur);
            cout << "Yeni Y�netmen: ";
            getline(cin, f.yonetmen);
            cout << "Yeni S�re (dakika): ";
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
        cout << "Film ba�ar�yla g�ncellendi!" << endl;
    } else {
        cout << "ID ile uyumlu film bulunamad�!" << endl;
    }
}

void filmSil(const string& dosyaAdi) {
    setlocale(LC_ALL, "Turkish");
    int silinecekID;
    cout << "Silmek istedi�iniz film ID'sini girin: ";
    cin >> silinecekID;

    vector<Film> filmler;
    ifstream dosya("filmler.txt");
    if (!dosya) {
        cout << "Dosya a��lamad�!" << endl;
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
        cout << "Film ba�ar�yla silindi!" << endl;
    } else {
        cout << "ID ile uyumlu film bulunamad�!" << endl;
    }
}
