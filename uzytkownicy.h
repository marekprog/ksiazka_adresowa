#ifndef UZYTKOWNICY_H
#define UZYTKOWNICY_H
#include <vector>
#include <iostream>

using namespace std;

struct uzytkownik{
    int id;
    string nazwa;
    string psswd;
};


class Uzytkownicy
{
    vector<uzytkownik> uzytkownicy;


public:
    Uzytkownicy();
    int dodajUzytkownika();
    bool sprawdzCzyJestUzytkownik(string nazwa);
    int zapiszLogowania();
    void odczytUzytkownikow();
    int logowanie();
    int getSize();
};

#endif // UZYTKOWNICY_H
