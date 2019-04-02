#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct wpis{

    int id;
    string imie;
    string nazwisko;
    string adres;
    string nrTel;
    string email;
};

struct uzytkownik{
    int id;
    string nazwa;
    string psswd;
}

int wpiszRekord(vector<wpis> *ksiazkaAdresowa){

    wpis nowyRekord;
    if (ksiazkaAdresowa->size()==0)
        nowyRekord.id=1;
    else
        nowyRekord.id=ksiazkaAdresowa->back().id+1;
    cout<<"Wprowadz imie: "<<endl;
    cin>>nowyRekord.imie;
    cout<<"Wprowadz nazwisko: "<<endl;
    cin>>nowyRekord.nazwisko;
    cout<<"Wprowadz adres: "<<endl;
    cin.ignore();
    getline(cin,nowyRekord.adres);
    cout<<"Wprowadz numer telefonu: "<<endl;
    cin.ignore();
    getline(cin,nowyRekord.nrTel);
    cout<<"Wprowadz adres email: "<<endl;
    cin>>nowyRekord.email;
    ksiazkaAdresowa->push_back(nowyRekord);
    system("clear");
    cout<<"Zapisano nowy wpis \n";
    sleep(1);
    system("clear");
    return 0;
}

int zapisDoPliku(vector<wpis> *ksiazkaAdresowa){

    cout<<"Zapisuje do pliku..."<<endl;
    fstream plik;
    plik.open("kontakty.txt",ios::out |ios::trunc);
    for (int i=0; i<ksiazkaAdresowa->size(); i++)
    {
        plik<<ksiazkaAdresowa->at(i).id<<"|"<<ksiazkaAdresowa->at(i).imie
            <<"|"<<ksiazkaAdresowa->at(i).nazwisko<<"|"<<ksiazkaAdresowa->at(i).adres
            <<"|"<<ksiazkaAdresowa->at(i).nrTel<<"|"<<ksiazkaAdresowa->at(i).email<<endl;
    }
    plik.close();
    sleep(1);

    return 0;
}


void odczytPliku(vector<wpis> *ksiazkaAdresowa){

    wpis wczytanyRekord;
    string temp;
    fstream plik;
    plik.open("kontakty.txt",ios::in);
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
        getline(sstr,wczytanyRekord.imie,'|');
        getline(sstr,wczytanyRekord.nazwisko,'|');
        getline(sstr,wczytanyRekord.adres,'|');
        getline(sstr,wczytanyRekord.nrTel,'|');
        getline(sstr,wczytanyRekord.email,'|');
        ksiazkaAdresowa->push_back(wczytanyRekord);
    }
}

int wyswietlWszystkich(vector<wpis> *ksiazkaAdresowa){

    cout.setf(ios::left);
    cout.width(3);
    cout<<"ID";
    cout.width(15);
    cout<<"IMIE";
    cout.width(15);
    cout<<"NAZWISKO";
    cout.width(15);
    cout<<"ADRES";
    cout.width(15);
    cout<<"NR TELEFONU";
    cout.width(15);
    cout<<"ADRES EMAIL"<<endl;

    for(int i=0; i<ksiazkaAdresowa->size(); i++)
    {

        cout.width(3);
        cout<<ksiazkaAdresowa->at(i).id;
        cout.width(15);
        cout<<ksiazkaAdresowa->at(i).imie;
        cout.width(15);
        cout<<ksiazkaAdresowa->at(i).nazwisko;
        cout.width(15);
        cout<<ksiazkaAdresowa->at(i).adres;
        cout.width(15);
        cout<<ksiazkaAdresowa->at(i).nrTel;
        cout.width(15);
        cout<<ksiazkaAdresowa->at(i).email<<endl;
    }
    cout<<"------------------------------"<<endl;
    cout<<"Wcisnij Enter zeby powrocic do glownego menu"<<endl;
    cin.ignore().get();
    return 0;
}
int podajImie(vector<wpis> *ksiazkaAdresowa){
    string imie;
    cout<<"Podaj Imie: ";
    cin>>imie;
    vector<wpis> wybraneImiona;
    for(int i=0; i<ksiazkaAdresowa->size(); i++)
        if(ksiazkaAdresowa->at(i).imie==imie)
            wybraneImiona.push_back(ksiazkaAdresowa->at(i));
    int zwracanie=wyswietlWszystkich(&wybraneImiona);
    return zwracanie;
}
int podajNazwisko(vector<wpis> *ksiazkaAdresowa){

    string nazwisko;
    cout<<"Podaj Nazwisko: ";
    cin>>nazwisko;
    vector<wpis> wybraneNazwiska;
    for(int i=0; i<ksiazkaAdresowa->size(); i++)
        if(ksiazkaAdresowa->at(i).nazwisko==nazwisko)
            wybraneNazwiska.push_back(ksiazkaAdresowa->at(i));
    int zwracanie=wyswietlWszystkich(&wybraneNazwiska);
    return zwracanie;
}

bool sprawdzCzyJest(vector<wpis> ksiazkaAdresowa,int id){
    bool test= false;
    for(int i=0; i<ksiazkaAdresowa.size(); i++) {
        if(ksiazkaAdresowa.at(i).id==id) {
            test=true;
            break;
        };
    }
    return test;
}

int usunAdresata(vector<wpis> *ksiazkaAdresowa){
    int numerDoUsuniecia,indeksDoUsuniecia;
    while(true) {
        cout<<"Podaj nr ID Adresata: "<<endl;

        cin>>numerDoUsuniecia;
        if(sprawdzCzyJest(*ksiazkaAdresowa,numerDoUsuniecia))
            break;
        else
            cout<<"Nie ma takiego numeru, sprobuj jeszcze raz: "<<endl;
        sleep(1);
    }
    vector<wpis> adresatDoUsuniecia;
    for(int i=0; i<ksiazkaAdresowa->size(); i++) {
        if(ksiazkaAdresowa->at(i).id==numerDoUsuniecia) {
            adresatDoUsuniecia.push_back(ksiazkaAdresowa->at(i));
            indeksDoUsuniecia=i;
        };
    }
    cout<<"Chcesz usunac "<<adresatDoUsuniecia.begin()->imie<<" "<<adresatDoUsuniecia.begin()->nazwisko<<"?"<<endl;

    while(true) {
        cout<<"Wciscnij [t] lub [n]"<<endl;
        char wybor;
        cin>>wybor;
        cout<<"wcisnales: "<<wybor<<endl;
        if(wybor=='t') {
            cout<<"Usunieto: "<<adresatDoUsuniecia.begin()->imie<<" "<<adresatDoUsuniecia.begin()->nazwisko<<endl;
            ksiazkaAdresowa->erase(ksiazkaAdresowa->begin()+indeksDoUsuniecia);
            break;
        }
        if(wybor=='n') {
            cout<<"Nie usuwamy"<<endl;
            break;
        }
        else
            cout<<"sprobuj jeszcze raz"<<endl;
    }
    sleep(1);
    return 0;
}

int edycjaAdresata(vector<wpis> *ksiazkaAdresowa){
    int id;
    while(true) {
        cout<<"Podaj nr ID: "<<endl;
        cin>>id;
        if(sprawdzCzyJest(*ksiazkaAdresowa,id))
            break;
        else
            cout<<"Nie ma takiego numeru, sprobuj jeszcze raz: "<<endl;
        sleep(1);
    }
    system("clear");
    vector<wpis> adresatDoEdycji;
    int indeksDoEdycji;
    for(int i=0; i<ksiazkaAdresowa->size(); i++) {
        if(ksiazkaAdresowa->at(i).id==id) {
            adresatDoEdycji.push_back(ksiazkaAdresowa->at(i));
            indeksDoEdycji=i;
        };
    }


    int wybor=0;
    while(wybor==0) {
        cout<<"Wpis do Edycji: "<<ksiazkaAdresowa->at(indeksDoEdycji).imie<<" "
            <<ksiazkaAdresowa->at(indeksDoEdycji).nazwisko<<" "<<ksiazkaAdresowa->at(indeksDoEdycji).adres
            <<" "<<ksiazkaAdresowa->at(indeksDoEdycji).nrTel<<" "<<ksiazkaAdresowa->at(indeksDoEdycji).email<<endl;
        cout<<"Wybierz atrybut do edycji: "<<endl;
        cout<<"1. Imie"<<endl;
        cout<<"2. Nazwisko"<<endl;
        cout<<"3. Adres"<<endl;
        cout<<"4. Numer telefonu"<<endl;
        cout<<"5. Adres email"<<endl;
        cout<<"6. Powrot do glownego menu"<<endl;
        cin>>wybor;

        switch (wybor) {
        case 1:
            system("clear");
            cout<<"Wprowadz nowe imie:"<<endl;
            cin>>ksiazkaAdresowa->at(indeksDoEdycji).imie;
            wybor=0;
            break;
        case 2:
            system("clear");
            cout<<"Wprowadz nowe nazwisko:"<<endl;
            cin>>ksiazkaAdresowa->at(indeksDoEdycji).nazwisko;
            wybor=0;
            break;
        case 3:
            system("clear");
            cout<<"Wprowadz nowy adres:"<<endl;
            cin>>ksiazkaAdresowa->at(indeksDoEdycji).adres;
            wybor=0;
            break;
        case 4:
            system("clear");
            cout<<"Wprowadz nowy numer telefonu:"<<endl;
            cin>>ksiazkaAdresowa->at(indeksDoEdycji).nrTel;
            wybor=0;
            break;
        case 5:
            system("clear");
            cout<<"Wprowadz nowy adres email:"<<endl;
            cin>>ksiazkaAdresowa->at(indeksDoEdycji).email;
            wybor=0;
            break;
        case 6:
            return 0;
        default:
            system("clear");
            wybor=0;
            break;
        }
    }
    return 0;
}

int main()
{
    vector<wpis> ksiazkaAdresowa;
    odczytPliku(&ksiazkaAdresowa);
    int wybor=0;
    while(wybor==0)

    {
        system("clear");
        //MENU GLOWNE
        cout<<"KSIAZKA ADRESOWA"<<endl;
        cout<<"-----------------------"<<endl;
        cout<<"ilosc wpisow w ksiazce: "<<ksiazkaAdresowa.size()<<endl;
        cout<<"-----------------------"<<endl;
        cout<<"Wybierz akcje: "<<endl;
        cout<<"1. Dodaj adresata."<<endl;
        cout<<"2. Wyszukaj po imieniu."<<endl;
        cout<<"3. Wyszukaj po nazwisku."<<endl;
        cout<<"4. Wyswietl wszystkich adresatów."<<endl;
        cout<<"5. Usuń adresata."<<endl;
        cout<<"6. Edytuj adresata."<<endl;
        cout<<"7. Zakoncz program."<<endl;
        cout<<"Twoj wybor: "<<endl;
        cin>>wybor;
        switch (wybor) {
        case 1:
            system("clear");
            wybor=wpiszRekord(&ksiazkaAdresowa);
            wybor=zapisDoPliku(&ksiazkaAdresowa);
            break;
        case 2:
            system("clear");
            wybor=podajImie(&ksiazkaAdresowa);
            break;
        case 3:
            system("clear");
            wybor=podajNazwisko(&ksiazkaAdresowa);
            break;
        case 4:
            system("clear");
            wybor=wyswietlWszystkich(&ksiazkaAdresowa);
            break;
        case 5:
            system("clear");
            wybor=usunAdresata(&ksiazkaAdresowa);
            wybor=zapisDoPliku(&ksiazkaAdresowa);
            break;
        case 6:
            system("clear");
            wybor=edycjaAdresata(&ksiazkaAdresowa);
            wybor=zapisDoPliku(&ksiazkaAdresowa);
            break;
        case 7:
            system("clear");
            cout<<"goodbye!!!"<<endl;
            sleep(1);
            exit(0);
            break;
        default:
            system("clear");
            wybor=0;
            break;
        }
    }
    return 0;
}
