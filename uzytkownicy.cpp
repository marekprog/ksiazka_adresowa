#include "uzytkownicy.h"
#include <fstream>
#include <sstream>
#include <unistd.h>


using namespace std;

Uzytkownicy::Uzytkownicy()
{
}

bool Uzytkownicy::sprawdzCzyJestUzytkownik(string nazwa)
{
    bool test= false;
    for(int i=0; i<uzytkownicy.size(); i++) {
        if(uzytkownicy.at(i).nazwa==nazwa) {
            test=true;
            break;
        };
    }
    return test;
}

int Uzytkownicy::zapiszLogowania()
{
    cout<<"Zapisuje nowego uzytkownika..."<<endl;
    fstream plik;
    plik.open("uzytkownicy.txt",ios::out);
    for (int i=0; i<uzytkownicy.size(); i++)
    {
        plik<<uzytkownicy.at(i).id<<"|"<<uzytkownicy.at(i).nazwa
            <<"|"<<uzytkownicy.at(i).psswd<<endl;
    }
    plik.close();
    sleep(1);

    return 0;
}

void Uzytkownicy::odczytUzytkownikow()
{
    uzytkownik wczytanyRekord;
    string temp;
    fstream plik;
    plik.open("uzytkownicy.txt",ios::in);
    if(plik.good()==false)
    {
        cout<<"Nie udalo sie zaimportowac kontaktow"<<endl;
        sleep(1);
    }
    string linia;
    while(getline(plik,linia))
    {
        stringstream sstr(linia);
        getline(sstr,temp,'|');
        wczytanyRekord.id=stoi(temp);
        getline(sstr,wczytanyRekord.nazwa,'|');
        getline(sstr,wczytanyRekord.psswd,'|');
        uzytkownicy.push_back(wczytanyRekord);
    }
}

int Uzytkownicy::logowanie()
{
    int iloscProb{3};
    bool test=false;
    int index=0;
    string login,haslo{""};
    while(!test && iloscProb>0){
        system("clear");
        cout<<"Pozostalo prob: "<<iloscProb<<endl;
        cout<<"Podaj login "<<endl;
        cin>>login;
        cout<<"Podaj haslo "<<endl;
        cin>>haslo;
        for (int i =0;i<uzytkownicy.size();i++){
            if (login==uzytkownicy.at(i).nazwa){
                if (haslo==uzytkownicy.at(i).psswd){
                    test=test||true;
                    index=uzytkownicy.at(i).id;
                }
            }
        }
        iloscProb--;

    }
    return index;
}

int Uzytkownicy::dodajUzytkownika()
{
    uzytkownik nowyRekord;
    if (uzytkownicy.size()==0)
        nowyRekord.id=1;
    else
        nowyRekord.id=uzytkownicy.back().id+1;
    do{
        cout<<"Wprowadz nazwe: "<<endl;
        cin>>nowyRekord.nazwa;
        if(sprawdzCzyJestUzytkownik(nowyRekord.nazwa))
            cout<<"nazwa zajeta, sprobuj jeszcze raz. "<<endl;
    }while(sprawdzCzyJestUzytkownik(nowyRekord.nazwa));
    cout<<"Wprowadz haslo: "<<endl;
    cin>>nowyRekord.psswd;
    uzytkownicy.push_back(nowyRekord);
    system("clear");
    cout<<"Zapisano nowego uzytkownika \n";
    sleep(1);
    system("clear");
    return 0;
}

int Uzytkownicy::getSize()
{
    return uzytkownicy.size();
}
