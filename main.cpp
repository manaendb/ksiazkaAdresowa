#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <conio.h> //biblioteka od getch() pobranie znaku bez wciskania enter

using namespace std;

struct Adresat
{
    int id;
    string imie;
    string nazwisko;
    string nrTelefonu;
    string email;
    string adres;
};

enum ImieCzyNazwisko
{
    IMIE, NAZWISKO
};

void zapisywanieDoPliku(Adresat adresat)
{
    fstream plik;
    plik.open("adresaci.txt",ios::out | ios::app);
    plik << adresat.id << "|";
    plik << adresat.imie << "|";
    plik << adresat.nazwisko << "|";
    plik << adresat.nrTelefonu << "|";
    plik << adresat.email << "|";
    plik << adresat.adres << "|" << endl;
    plik.close();
}

string wczytajLinie()
{
    string wejscie;
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = (0);

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() > 0)
        {
            znak = wejscie[0];
			cin.sync();
            break;
        }
	}
    return znak;
}

int wczytajLiczbeCalkowita()
{
    string wejscie;
    int liczba;

    while(true)
    {
        getline(cin, wejscie);

        stringstream myStream(wejscie);

        if (myStream >> liczba)
        {
            break;
        }
        cout << "To nie jest liczba. Wpisz ponownie: ";
    }
    return liczba;
}

void wypisanieWTablicyPozycjiSeparatorowWystepujacychWLiniiTekstu (int tablica[], string liniaTekstu)
{
    size_t pozycjaSeparatoraWLinii = 0;
    for (int i = 0; i < 6; i++)
    {
        pozycjaSeparatoraWLinii = liniaTekstu.find("|", pozycjaSeparatoraWLinii);
        tablica[i] = pozycjaSeparatoraWLinii;
        pozycjaSeparatoraWLinii++;
    }
}

Adresat zamianaLinijkiTekstuZPlikuNaAdresata(int tablica[6], string liniaTekstu)
{
    Adresat adresat;
    adresat.id = atoi(liniaTekstu.substr(0, tablica[0]).c_str());
    adresat.imie = liniaTekstu.substr(tablica[0]+1, tablica[1] - tablica[0] - 1);
    adresat.nazwisko = liniaTekstu.substr(tablica[1]+1, tablica[2] - tablica[1] - 1);
    adresat.nrTelefonu = liniaTekstu.substr(tablica[2]+1, tablica[3] - tablica[2] - 1);
    adresat.email = liniaTekstu.substr(tablica[3]+1, tablica[4] - tablica[3] - 1);
    adresat.adres = liniaTekstu.substr(tablica[4]+1, tablica[5] - tablica[4] - 1);
    return adresat;
}

void odczytZPliku(vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open("adresaci.txt",ios::in);

    if(plik.good()==false)
    {
        return;
    }

    string zapisanyTekstWPojedynczejLiniiWPliku;

    while(getline(plik,zapisanyTekstWPojedynczejLiniiWPliku))
    {
        int tablicaZPozycjamiSeparatoraWLinii[6];
        Adresat adresat;
        wypisanieWTablicyPozycjiSeparatorowWystepujacychWLiniiTekstu(tablicaZPozycjamiSeparatoraWLinii, zapisanyTekstWPojedynczejLiniiWPliku);
        adresat = zamianaLinijkiTekstuZPlikuNaAdresata(tablicaZPozycjamiSeparatoraWLinii, zapisanyTekstWPojedynczejLiniiWPliku);
        adresaci.push_back(adresat);
    }

    plik.close();
}

void rejestracja(vector <Adresat> &adresaci)
{
    Adresat nowyUzytkownik;
    nowyUzytkownik.id = adresaci.empty() ? 1 : adresaci.back().id + 1;

    system("cls");

    cout << "Wprowadz imie (9 - wyjscie do menu glownego bez zapisywania): ";
    nowyUzytkownik.imie = wczytajLinie();
    if (nowyUzytkownik.imie == "9") return;

    cout << "Wprowadz nazwisko (9 - wyjscie do menu glownego bez zapisywania): ";
    nowyUzytkownik.nazwisko = wczytajLinie();
    if (nowyUzytkownik.nazwisko == "9") return;

	for (size_t i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].imie == nowyUzytkownik.imie && adresaci[i].nazwisko == nowyUzytkownik.nazwisko)
        {
            cout << endl << "Osoba o wpisanym imieniu i nazwisku jest juz zapisana w bazie danych" << endl;
            cout << "9 - wyjscie do glownego menu bez zapisywania juz wpisanych danych" << endl;
            cout << "Lub wpisz inne nazwisko: ";
            nowyUzytkownik.nazwisko = wczytajLinie();
            if (nowyUzytkownik.nazwisko == "9") return;
            else i = 0;
        }
    }

    cout << "Wprowadz nrTelefonu (9 - wyjscie do menu glownego bez zapisywania): ";
    nowyUzytkownik.nrTelefonu = wczytajLinie();
    if (nowyUzytkownik.nrTelefonu == "9") return;

    cout << "Wprowadz email (9 - wyjscie do menu glownego bez zapisywania): ";
    nowyUzytkownik.email = wczytajLinie();
    if (nowyUzytkownik.email == "9") return;

    cout << "Wprowadz adres (9 - wyjscie do menu glownego bez zapisywania): ";
    nowyUzytkownik.adres = wczytajLinie();
    if (nowyUzytkownik.adres == "9") return;

    adresaci.push_back(nowyUzytkownik);

    zapisywanieDoPliku(nowyUzytkownik);
}

void wypiszAdresataNaEkranie(Adresat adresat)
{
    cout << "Id: " << adresat.id << endl;
    cout << "Imie: " << adresat.imie << endl;
    cout << "Nazwisko: " << adresat.nazwisko << endl;
    cout << "Nr telefonu: " << adresat.nrTelefonu << endl;
    cout << "Adres email: " << adresat.email << endl;
    cout << "Adres zamieszkania: " << adresat.adres << endl << endl;
}

void wypiszOsobeWgImieniaLubNazwiska(vector <Adresat> adresaci, ImieCzyNazwisko imieCzyNazwisko)
{
    string imieLubNazwisko = "";
    string opis = imieCzyNazwisko == IMIE ? "imie" : "nazwisko";

    system("cls");

	while (imieLubNazwisko != "9")
    {
        if (opis == "imie") cout << "Wyswietlanie zapisanych Adresatow wg imienia" << endl << endl;
        else cout << "Wyswietlanie zapisanych Adresatow wg nazwiska" << endl << endl;
        cout << "Podaj " << opis << " (lub wcisnij 9 aby wyjsc do glownego menu): ";
        imieLubNazwisko = wczytajLinie();

		if (imieLubNazwisko == "9") return;

        system("cls");
        bool czyJestTakieImieLubNazwisko = false;

        for (Adresat adresat : adresaci)
        {
            if (adresat.imie == imieLubNazwisko && imieCzyNazwisko == IMIE)
            {
                wypiszAdresataNaEkranie(adresat);
                czyJestTakieImieLubNazwisko = true;
            }
            if (adresat.nazwisko == imieLubNazwisko && imieCzyNazwisko == NAZWISKO)
            {
                wypiszAdresataNaEkranie(adresat);
                czyJestTakieImieLubNazwisko = true;
            }
        }

        if (!czyJestTakieImieLubNazwisko) cout << "Nie ma osoby o takim " << opis << " w bazie danych" << endl << endl;
    }
}

void wypiszWszystkichAdresatow(vector <Adresat> adresaci)
{
    for (Adresat adresat : adresaci)
    {
        wypiszAdresataNaEkranie(adresat);
    }
}

void wypiszWszystkieOsobyZBazy(vector <Adresat> adresaci)
{
    string wyjscieDoMenuGlownego;
    system("cls");
    wyjscieDoMenuGlownego = "";

    while (wyjscieDoMenuGlownego != "9")
    {
        system("cls");
        cout << "Wyswietlanie wszystkich osob z bazy danych :" << endl << endl;

        if (adresaci.empty()) cout << "Nie ma zapisanych Adresatow w bazie danych" << endl << endl;
        else wypiszWszystkichAdresatow(adresaci);

        cout << "9. Wyjscie do glownego menu: ";
        wyjscieDoMenuGlownego = wczytajZnak();
    }
}

void przepisanieWszystkichAdresatowDoPliku(vector <Adresat> adresaci)
{
    fstream plik;
    plik.open("adresaci.txt",ios::out);
    for (Adresat adresat : adresaci)
    {
        plik << adresat.id << "|";
        plik << adresat.imie << "|";
        plik << adresat.nazwisko << "|";
        plik << adresat.nrTelefonu << "|";
        plik << adresat.email << "|";
        plik << adresat.adres << "|" << endl;
    }

    plik.close();
}

void usuwanieAdresataWedlugNrId(vector <Adresat> &adresaci)
{
    int nrIdAdresata;
    string wyjscieDoMenuGlownego = "";
    char wybor;
    bool czyZnalezionoNrId = false;

    while (wyjscieDoMenuGlownego != "9")
    {
        system("cls");
        if (adresaci.empty())
        {
            cout << "Baza adresatow jest pusta. Nie ma czego usuwac!" << endl;
            cout << "9. Wyjscie do glownego menu" << endl;
            wyjscieDoMenuGlownego = wczytajZnak();
        }
        else
        {
            cout << "Podaj nr Id adresata do usuniecia: " ;
            nrIdAdresata = wczytajLiczbeCalkowita();
            for (size_t i = 0; i < adresaci.size(); i++)
            {
                if (adresaci[i].id == nrIdAdresata)
                {
                    czyZnalezionoNrId = true;
                    cout << "Czy na pewno chcesz usunac adresata? (macisnij 't'): ";
                    wybor = wczytajZnak();
                    if (wybor == 't')
                    {
                        adresaci.erase(adresaci.begin() + i);
                        przepisanieWszystkichAdresatowDoPliku(adresaci);
                    }
                }
            }
            if (!czyZnalezionoNrId)
            {
                cout << endl << "Nie znaleziono nr Id o podanym nr" << endl << endl;
            }
            cout << "9. Wyjscie do glownego menu (kazdy inny klawisz - ponowne wpisanie nr Id do usuniecia): ";
            wyjscieDoMenuGlownego = wczytajZnak();
        }
    }
}

void wyswietlenieMenuEdycjiAdresata(vector <Adresat> &adresaci, int pozycjaAdresataWVectorze)
{
    char wybor;
    while(1)
    {
        system("cls");
        cout << "1. Zmiana imienia" << endl;
        cout << "2. Zmiana nazwiska" << endl;
        cout << "3. Zmiana nr telefonu" << endl;
        cout << "4. Zmiana email" << endl;
        cout << "5. Zmiana adresu" << endl;
        cout << "6. Powrot do menu wyboru edycji" << endl;
        cout << "Wybierz opcje: ";
        wybor = wczytajZnak();

        switch (wybor)
        {
        case '1':
        {
            cout << "Wprowadz nowe imie: ";
            adresaci[pozycjaAdresataWVectorze].imie = wczytajLinie();
            break;
        }
        case '2':
        {
            cout << "Wprowadz nowe nazwisko: ";
            adresaci[pozycjaAdresataWVectorze].nazwisko = wczytajLinie();
            break;
        }
        case '3':
        {
            cout << "Wprowadz nowy nr telefonu: ";
            adresaci[pozycjaAdresataWVectorze].nrTelefonu = wczytajLinie();
            break;
        }
        case '4':
        {
            cout << "Wprowadz nowy email: ";
            adresaci[pozycjaAdresataWVectorze].email = wczytajLinie();
            break;
        }
        case '5':
        {
            cout << "Wprowadz nowy adres: ";
            adresaci[pozycjaAdresataWVectorze].adres = wczytajLinie();
            break;
        }
        case '6':
        {
            przepisanieWszystkichAdresatowDoPliku(adresaci);
            return;
        }
        default:
        {
            cout << endl << "Nie ma takiej opcji w menu" << endl;
            getch();
        }
        }
    }
}

void edycjaAdresataPoPodaniuNrId(vector <Adresat> &adresaci)
{
    int nrIdAdresata;
    string wyjscieDoMenuGlownego = "";
    bool czyZnalezionoNrId = false;

    while (wyjscieDoMenuGlownego != "9")
    {
        system("cls");

        if (adresaci.empty())
        {
            cout << "Baza adresatow jest pusta. Dodaj najpierw adresata przed edycja!" << endl;
            cout << "9. Wyjscie do glownego menu" << endl;
            wyjscieDoMenuGlownego = wczytajZnak();
        }

        else
        {
            cout << "Podaj nr Id adresata do edycji: " ;
            nrIdAdresata = wczytajLiczbeCalkowita();
            for (size_t i = 0; i < adresaci.size(); i++)
            {
                if (adresaci[i].id == nrIdAdresata)
                {
                    czyZnalezionoNrId = true;
                    wyswietlenieMenuEdycjiAdresata(adresaci, i);
                    system("cls");
                }
            }
            if (!czyZnalezionoNrId)
            {
                cout << endl << "Nie znaleziono nr Id o podanym nr" << endl << endl;
            }
            cout << "9. Wyjscie do glownego menu (kazdy inny klawisz - ponowne wpisanie nr Id do edycji): ";
            wyjscieDoMenuGlownego = wczytajZnak();
        }
    }
}

int main()
{
    vector <Adresat> adresaci;
    char wybor;

    odczytZPliku(adresaci);

    while(1)
    {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietlanie wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Wybierz opcje: ";
        wybor = wczytajZnak();

        switch (wybor)
        {
        case '1': rejestracja(adresaci); break;
        case '2': wypiszOsobeWgImieniaLubNazwiska(adresaci, IMIE); break;
        case '3': wypiszOsobeWgImieniaLubNazwiska(adresaci, NAZWISKO); break;
        case '4': wypiszWszystkieOsobyZBazy(adresaci); break;
        case '5': usuwanieAdresataWedlugNrId(adresaci); break;
        case '6': edycjaAdresataPoPodaniuNrId(adresaci); break;
        case '9': exit(0); break;
        default: cout << endl << "Nie ma takiej opcji w menu" << endl; getch(); break;
        }
    }
    return 0;
}
