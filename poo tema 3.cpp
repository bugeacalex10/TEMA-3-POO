#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <limits>
#include "pariuri.h"
#include "rezultate.h"
#include "exceptii.h"
#include "sabloane.h"

std::ifstream fin("date.in");

void citire_meciuri(std::ifstream& fin,
std::map<int, std::pair<std::string, std::string>>& meciuri, std::map<int, double>& vect_echipa1,
std::map<int, double>& vect_egal, std::map<int, double>& vect_echipa2)
{
    int index = 1;
    std::string cuvant;

    while (fin >> cuvant)
    {
        if (cuvant == "rezultate")
            break;

        std::string echipa1 = cuvant;
        std::string echipa2;
        double cota_echipa1, cota_egal, cota_echipa2;

        fin >> echipa2 >> cota_echipa1 >> cota_egal >> cota_echipa2;

        meciuri[index] = {echipa1, echipa2};
        vect_echipa1[index] = cota_echipa1;
        vect_egal[index] = cota_egal;
        vect_echipa2[index] = cota_echipa2;
        index++;
    }
}

void citire_rezultate(std::ifstream& fin, std::vector<Rezultate>& rezultate, 
std::map<int, std::pair<std::string, std::string>>& meciuri)
{
    int index = 1;
    std::string rezultat_meci;
    int nr_faulturi, nr_cartonase_galbene, nr_cartonase_rosii, nr_cornere;
    while (fin >> rezultat_meci >> nr_faulturi >> nr_cartonase_galbene >> nr_cartonase_rosii >> nr_cornere)
    {
        Rezultate rezultat(index, rezultat_meci, nr_faulturi, nr_cartonase_galbene, nr_cartonase_rosii, nr_cornere);
        rezultate.push_back(rezultat);
        index++;
    }
}

Pariuri* creeazaPariuSimplu(double &miza, std::map<int, std::pair<std::string, std::string>>& meciuri,
std::vector<std::string> &actiuni, std::vector<Rezultate> &rezultate, std::map<int, double>& vect_echipa1,
std::map<int, double>& vect_egal, std::map<int, double>& vect_echipa2) 
{
    std::cout << "meciurile si cotele disponibile sunt: " << std::endl;
    for(const auto& meci : meciuri)
    {
        std::cout << meci.first << ": " << meci.second.first << " vs " << meci.second.second << std::endl;
        std::cout << "cota echipa 1: " << vect_echipa1[meci.first] << std::endl;
        std::cout << "cota egal: " << vect_egal[meci.first] << std::endl;
        std::cout << "cota echipa 2: " << vect_echipa2[meci.first] << std::endl;
    }
    std::cout << "introdu id-ul meciului pe care vrei sa pariezi: ";
    int id_meci;
    std::cin >> id_meci;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(meciuri.find(id_meci) == meciuri.end())
    {
        throw idInvalid();
    }

    for(const auto& meci : meciuri)
    {
        if(meci.first == id_meci)
        {
            std::cout << "alege una dintre urmatoarele actiuni: " << std::endl;
            for(const auto& actiune : actiuni)
            {
                std::cout << actiune << std::endl;
            }
            std::string actiune_aleasa;
            std::getline(std::cin, actiune_aleasa);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(actiune_aleasa == "rezultat meci")
            {
                std::cout << "alege rezultatul meciului: " << std::endl;
                std::cout << "1. " << meci.second.first << " castiga" << std::endl;
                std::cout << "2. " << "egalitate" << std::endl;
                std::cout << "3. " << meci.second.second << " castiga" << std::endl;

                std::string alegere;
                std::cin >> alegere;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(alegere != meci.second.first && alegere != "egalitate" && alegere != meci.second.second)
                {
                    throw actiuneInvalida();
                }

                PariuSimplu* pariu = new PariuSimplu(miza);
                Actiune actiune;
                actiune.tip = echipa;
                actiune.rezultat = rezultate[id_meci - 1].get_rezultat_meci();
                if(alegere == meci.second.first)
                {
                    actiune.cota = vect_echipa1[id_meci];
                }
                else if (alegere == "egalitate")
                {
                    actiune.cota = vect_egal[id_meci];
                }
                else if(alegere == meci.second.second)
                {
                    actiune.cota = vect_echipa2[id_meci];
                }
                actiune.alegere = alegere;

                PariuMeci pariu_meci;
                pariu_meci.id_meci = id_meci;
                pariu_meci.vect_actiuni.push_back(actiune);

                pariu->adaugaPariuMeci(pariu_meci);
                
                return pariu;
            }
            else if (actiune_aleasa == "numar faulturi")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                for(char &c : alegere)
                {
                    c = tolower(c);
                }
                if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                {
                    throw alegereInvalida();
                }

                std::cout << "introdu numarul de faulturi: ";
                int numar_faulturi;
                std::cin >> numar_faulturi;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(numar_faulturi < 0)
                {
                    throw numarInvalid();
                }

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_faulturi());
                    actiune.alegere = std::to_string(numar_faulturi);
                    actiune.cota = 1 + (numar_faulturi - rezultate[id_meci - 1].get_nr_faulturi()) * 0.25;

                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_faulturi());
                    actiune.alegere = std::to_string(numar_faulturi);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_faulturi() - numar_faulturi) * 0.25;

                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_faulturi());
                    actiune.alegere = std::to_string(numar_faulturi);
                    actiune.cota = 2.5;

                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
            else if (actiune_aleasa == "numar cartonase galbene")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                for(char &c : alegere)
                {
                    c = tolower(c);
                }
                if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                {
                    throw alegereInvalida();
                }

                std::cout << "introdu numarul de cartonase galbene: ";
                int numar_cartonase_galbene;
                std::cin >> numar_cartonase_galbene;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(numar_cartonase_galbene < 0)
                {
                    throw numarInvalid();
                }

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_galbene());
                    actiune.alegere = std::to_string(numar_cartonase_galbene);
                    actiune.cota = 1 + (numar_cartonase_galbene - rezultate[id_meci - 1].get_nr_cartonase_galbene()) * 0.3;

                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_galbene());
                    actiune.alegere = std::to_string(numar_cartonase_galbene);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_cartonase_galbene() - numar_cartonase_galbene) * 0.3;
                   
                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_galbene());
                    actiune.alegere = std::to_string(numar_cartonase_galbene);
                    actiune.cota = 3.0;
                    
                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
            else if (actiune_aleasa == "numar cartonase rosii")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;
                for(char &c : alegere)
                {
                    c = tolower(c);
                }
                if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                {
                    throw alegereInvalida();
                }

                std::cout << "introdu numarul de cartonase rosii: ";
                int numar_cartonase_rosii;
                std::cin >> numar_cartonase_rosii;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(numar_cartonase_rosii < 0)
                {
                    throw numarInvalid();
                }

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_rosii());
                    actiune.alegere = std::to_string(numar_cartonase_rosii);
                    actiune.cota = 1 + (numar_cartonase_rosii - rezultate[id_meci - 1].get_nr_cartonase_rosii()) * 0.5;

                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_rosii());
                    actiune.alegere = std::to_string(numar_cartonase_rosii);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_cartonase_rosii() - numar_cartonase_rosii) * 0.5;

                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_rosii());
                    actiune.alegere = std::to_string(numar_cartonase_rosii);
                    actiune.cota = 4.0;
                    
                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
            else if (actiune_aleasa == "numar cornere")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                for(char &c : alegere)
                {
                    c = tolower(c);
                }
                if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                {
                    throw alegereInvalida();
                }

                std::cout << "introdu numarul de cornere: ";
                int numar_cornere;
                std::cin >> numar_cornere;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(numar_cornere < 0)
                {
                    throw numarInvalid();
                }

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cornere());
                    actiune.alegere = std::to_string(numar_cornere);
                    actiune.cota = 1 + (numar_cornere - rezultate[id_meci - 1].get_nr_cornere()) * 0.25;

                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cornere());
                    actiune.alegere = std::to_string(numar_cornere);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_cornere() - numar_cornere) * 0.25;
                   
                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cornere());
                    actiune.alegere = std::to_string(numar_cornere);
                    actiune.cota = 2.5;
                    
                    PariuMeci pariu_meci;
                    pariu_meci.id_meci = id_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
            else
            {
                throw actiuneInvalida();
            }
        }
    }
    throw idInvalid();
}

Pariuri* creeazaPariuMultiplu(double &miza, std::map<int, std::pair<std::string, std::string>>& meciuri,
std::vector<std::string> &actiuni, std::vector<Rezultate> &rezultate, std::map<int, double>& vect_echipa1,
std::map<int, double>& vect_egal, std::map<int,double>& vect_echipa2)
{
    std::cout << "meciurile si cotele disponibile sunt: " << std::endl;
    for(const auto& meci:meciuri)
    {
        std::cout << meci.first << ": " << meci.second.first << " vs " << meci.second.second << std::endl;
        std::cout << "cota echipa 1: " << vect_echipa1[meci.first] << std::endl;
        std::cout << "cota egal: " << vect_egal[meci.first] << std::endl;
        std::cout << "cota echipa 2: " << vect_echipa2[meci.first] << std::endl;
    }
    std::cout << "introdu numarul de meciuri pe care vrei sa pariezi: " << std::endl;
    int nr_meciuri;
    std::cin >> nr_meciuri;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "introdu id-urile meciurilor pe care vrei sa pariezi: " << std::endl;
    std::vector<int> id_meciuri(nr_meciuri);
    for(int ind = 0; ind < nr_meciuri; ind++)
    {
        std::cin >> id_meciuri[ind];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(meciuri.find(id_meciuri[ind]) == meciuri.end())
        {
            throw idInvalid();
        }
    }

    PariuMultiplu* pariu = new PariuMultiplu(miza);
    for(const auto& meci:meciuri)
    {
        for(int ind = 0; ind < nr_meciuri; ind++)
        {
            if(meci.first == id_meciuri[ind])
            {
                std::cout << "alege una sau mai multe dintre urmatoarele actiuni pentru "
                 << meci.second.first << " vs " << meci.second.second << " si scrie 'gata' cand ai terminat: " << std::endl;
                for(const auto& actiune: actiuni)
                {
                    std::cout << actiune << std::endl;
                }
                std::vector<std::string> actiuni_alese;
                std::string actiune_aleasa;
                while(std::getline(std::cin, actiune_aleasa))
                {
                    if(actiune_aleasa == "gata")
                    {
                        break;
                    }
                    actiuni_alese.push_back(actiune_aleasa);
                }
                PariuMeci pariu_meci;
                pariu_meci.id_meci = id_meciuri[ind];
                for(const auto& actiune_aleasa : actiuni_alese)
                {
                    Actiune actiune;
                    if(actiune_aleasa == "rezultat meci")
                    {
                        std::cout << "alege rezultatul meciului: " << std::endl;
                        std::cout << "1. " << meci.second.first << " castiga" << std::endl;
                        std::cout << "2. " << "egalitate" << std::endl;
                        std::cout << "3. " << meci.second.second << " castiga" << std::endl;
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(alegere != meci.second.first && alegere != "egalitate" && alegere != meci.second.second)
                        {
                            throw meciInvalid();
                        }
                        actiune.tip = echipa;
                        actiune.rezultat = rezultate[id_meciuri[ind] - 1].get_rezultat_meci();
                        actiune.alegere = alegere;
                        if(alegere == meci.second.first)
                        {
                            actiune.cota = vect_echipa1[id_meciuri[ind]];
                        }
                        else if (alegere == "egalitate")
                        {
                            actiune.cota = vect_egal[id_meciuri[ind]];
                        }
                        else if(alegere == meci.second.second)
                        {
                            actiune.cota = vect_echipa2[id_meciuri[ind]];
                        }
                    }
                    else if (actiune_aleasa == "numar faulturi")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de faulturi: ";
                        int numar_faulturi;
                        std::cin >> numar_faulturi;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(numar_faulturi < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_faulturi());
                        actiune.alegere = std::to_string(numar_faulturi);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_faulturi - rezultate[id_meciuri[ind] - 1].get_nr_faulturi()) * 0.25;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_faulturi() - numar_faulturi) * 0.25;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 2.5;
                        }
                    }
                    else if(actiune_aleasa == "numar cartonase galbene")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de cartonase galbene: ";
                        int numar_cartonase_galbene;
                        std::cin >> numar_cartonase_galbene;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(numar_cartonase_galbene < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_cartonase_galbene());
                        actiune.alegere = std::to_string(numar_cartonase_galbene);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_cartonase_galbene - rezultate[id_meciuri[ind] - 1].get_nr_cartonase_galbene()) * 0.3;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_cartonase_galbene() - numar_cartonase_galbene) * 0.3;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 3.0;
                        }
                    } 
                    else if (actiune_aleasa == "numar cartonase rosii")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de cartonase rosii: ";
                        int numar_cartonase_rosii;
                        std::cin >> numar_cartonase_rosii;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(numar_cartonase_rosii < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_cartonase_rosii());
                        actiune.alegere = std::to_string(numar_cartonase_rosii);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_cartonase_rosii - rezultate[id_meciuri[ind] - 1].get_nr_cartonase_rosii()) * 0.5;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_cartonase_rosii() - numar_cartonase_rosii) * 0.5;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 4.0;
                        }
                    }
                    else if(actiune_aleasa == "numar cornere")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de cornere: ";
                        int numar_cornere;
                        std::cin >> numar_cornere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if(numar_cornere < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_cornere());
                        actiune.alegere = std::to_string(numar_cornere);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_cornere - rezultate[id_meciuri[ind] - 1].get_nr_cornere()) * 0.25;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_cornere() - numar_cornere) * 0.25;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 2.5;
                        }
                    }
                    else
                    {
                        throw actiuneInvalida();
                    }
                    pariu_meci.vect_actiuni.push_back(actiune);
                }
                pariu->adaugaPariuMeci(pariu_meci);
            }
        }
    }
    return pariu;
}

Pariuri* creeazaPariuSistem(double &miza, int k, std::map<int, std::pair<std::string, std::string>>& meciuri,
std::vector<std::string> &actiuni, std::vector<Rezultate> &rezultate, std::map<int, double>& vect_echipa1,
std::map<int, double>& vect_egal, std::map<int, double>& vect_echipa2)
{
    std::cout << "meciurile si cotele disponibile sunt: " << std::endl;
    for(const auto& meci:meciuri)
    {
        std::cout << meci.first << ": " << meci.second.first << " vs " << meci.second.second << std::endl;
        std::cout << "cota echipa 1: " << vect_echipa1[meci.first] << std::endl;
        std::cout << "cota egal: " << vect_egal[meci.first] << std::endl;
        std::cout << "cota echipa 2: " << vect_echipa2[meci.first] << std::endl;
    
    }
    std::cout << "introdu numarul de meciuri pe care vrei sa pariezi si sa fie mai mare decat " << k << ": " << std::endl;
    int nr_meciuri;
    std::cin >> nr_meciuri;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(nr_meciuri <= k)
    {
        throw sistemInvalid();
    }

    std::cout << "introdu id-urile meciurilor pe care vrei sa pariezi: " << std::endl;
    std::vector<int> id_meciuri(nr_meciuri);
    for(int ind = 0; ind < nr_meciuri; ind++)
    {
        std::cin >> id_meciuri[ind];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(meciuri.find(id_meciuri[ind]) == meciuri.end())
        {
            throw idInvalid();
        }
    }
    
    PariuSistem* pariu = new PariuSistem(miza, k);
    for(const auto& meci:meciuri)
    {
        for(int ind = 0; ind < nr_meciuri; ind++)
        {
            if(meci.first == id_meciuri[ind])
            {
                std::cout << "alege una sau mai multe dintre urmatoarele actiuni pentru "
                << meci.second.first << " vs " << meci.second.second << " si scrie 'gata' cand ai terminat: " << std::endl;
                for(const auto& actiune: actiuni)
                {
                    std::cout << actiune << std::endl;
                }
                std::vector<std::string> actiuni_alese;
                std::string actiune_aleasa;
                while(std::getline(std::cin, actiune_aleasa))
                {
                    if(actiune_aleasa == "gata")
                    {
                        break;
                    }
                    actiuni_alese.push_back(actiune_aleasa);
                }
                PariuMeci pariu_meci;
                pariu_meci.id_meci = id_meciuri[ind];
                for(const auto& actiune_aleasa : actiuni_alese)
                {
                    Actiune actiune;
                    if(actiune_aleasa == "rezultat meci")
                    {
                        std::cout << "alege rezultatul meciului: " << std::endl;
                        std::cout << "1. " << meci.second.first << " castiga" << std::endl;
                        std::cout << "2. " << "egalitate" << std::endl;
                        std::cout << "3. " << meci.second.second << " castiga" << std::endl;
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(alegere != meci.second.first && alegere != "egalitate" && alegere != meci.second.second)
                        {
                            throw meciInvalid();
                        }
                        actiune.tip = echipa;
                        actiune.rezultat = rezultate[id_meciuri[ind] - 1].get_rezultat_meci();
                        actiune.alegere = alegere;
                        if(alegere == meci.second.first)
                        {
                            actiune.cota = vect_echipa1[id_meciuri[ind]];
                        }
                        else if (alegere == "egalitate")
                        {
                            actiune.cota = vect_egal[id_meciuri[ind]];
                        }
                        else if(alegere == meci.second.second)
                        {
                            actiune.cota = vect_echipa2[id_meciuri[ind]];
                        }
                    }
                    else if (actiune_aleasa == "numar faulturi")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de faulturi: ";
                        int numar_faulturi;
                        std::cin >> numar_faulturi;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(numar_faulturi < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_faulturi());
                        actiune.alegere = std::to_string(numar_faulturi);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_faulturi - rezultate[id_meciuri[ind] - 1].get_nr_faulturi()) * 0.25;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_faulturi() - numar_faulturi) * 0.25;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 2.5;
                        }
                    }
                    else if(actiune_aleasa == "numar cartonase galbene")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de cartonase galbene: ";
                        int numar_cartonase_galbene;
                        std::cin >> numar_cartonase_galbene;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(numar_cartonase_galbene < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_cartonase_galbene());
                        actiune.alegere = std::to_string(numar_cartonase_galbene);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_cartonase_galbene - rezultate[id_meciuri[ind] - 1].get_nr_cartonase_galbene()) * 0.3;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_cartonase_galbene() - numar_cartonase_galbene) * 0.3;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 3.0;
                        }
                    } 
                    else if (actiune_aleasa == "numar cartonase rosii")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de cartonase rosii: ";
                        int numar_cartonase_rosii;
                        std::cin >> numar_cartonase_rosii;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(numar_cartonase_rosii < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_cartonase_rosii());
                        actiune.alegere = std::to_string(numar_cartonase_rosii);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_cartonase_rosii - rezultate[id_meciuri[ind] - 1].get_nr_cartonase_rosii()) * 0.5;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_cartonase_rosii() - numar_cartonase_rosii) * 0.5;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 4.0;
                        }
                    }
                    else if(actiune_aleasa == "numar cornere")
                    {
                        std::cout << "alege metoda de pariere: " << std::endl;
                        std::cout << "1.peste" << std::endl;
                        std::cout << "2.sub" << std::endl;
                        std::cout << "3.fix" << std::endl;
                        std::cout << "introdu alegerea ta: ";
                        std::string alegere;
                        std::cin >> alegere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        for(char &c : alegere)
                        {
                            c = tolower(c);
                        }
                        if(alegere != "peste" && alegere != "sub" && alegere != "fix")
                        {
                            throw alegereInvalida();
                        }

                        std::cout << "introdu numarul de cornere: ";
                        int numar_cornere;
                        std::cin >> numar_cornere;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(numar_cornere < 0)
                        {
                            throw numarInvalid();
                        }

                        actiune.rezultat = std::to_string(rezultate[id_meciuri[ind] - 1].get_nr_cornere());
                        actiune.alegere = std::to_string(numar_cornere);
                        if (alegere == "peste")
                        {
                            actiune.tip = peste;
                            actiune.cota = 1 + (numar_cornere - rezultate[id_meciuri[ind] - 1].get_nr_cornere()) * 0.25;
                        }
                        else if (alegere == "sub")
                        {
                            actiune.tip = sub;
                            actiune.cota = 1 + (rezultate[id_meciuri[ind] - 1].get_nr_cornere() - numar_cornere) * 0.25;
                        }
                        else if (alegere == "fix")
                        {
                            actiune.tip = fix;
                            actiune.cota = 2.5;
                        }
                    }
                    else
                    {
                        throw actiuneInvalida();
                    }
                    pariu_meci.vect_actiuni.push_back(actiune);
                }
                pariu->adaugaPariuMeci(pariu_meci);
            }
        }
    }
    return pariu;
}

int main()
{
    std::vector<std::string> actiuni = {"rezultat meci", "numar faulturi", "numar cartonase galbene",
    "numar cartonase rosii", "numar cornere"};
    
    std::map<int, double> vect_echipa1;
    std::map<int, double> vect_egal;
    std::map<int, double> vect_echipa2;

    std::map<int, std::pair<std::string, std::string>> meciuri;
    std::string linie;
    fin >> linie;
    if(linie == "meciuri")
    {   
        citire_meciuri(fin, meciuri, vect_echipa1, vect_egal, vect_echipa2);
    }
    std::vector<Rezultate> rezultate;
    citire_rezultate(fin,rezultate, meciuri);
    
    std::cout << "introdu numele prenumele si varsta: ";
    std::string nume, prenume;
    int varsta;

    std::cin >> nume >> prenume >> varsta;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try
    {
         if(varsta < 18)
        {
            throw varstaInvalida();
        }
    }
    catch(varstaInvalida& e)
    {
        std::cout << e.what() << std::endl;
        return 0;
    }

    std::cout << "introdu suma pe care vrei sa o pariezi: ";
    double suma;

    std::cin >> suma;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "introdu numarul de pariuri pe care vrei sa le faci: ";
    int nr_pariuri;

    std::cin >> nr_pariuri;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Pariuri*> vect_pariuri;

    for(int ind = 0; ind < nr_pariuri; ind++)
    {
        std::cout << "introdu tipul pariului (simplu, multiplu sau sistem) pentru pariul " << ind + 1 <<": ";
        std::string tip_pariu;

        std::cin >> tip_pariu;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(char &c : tip_pariu)
        {
            c = tolower(c);
        }
        try
        {
            if(tip_pariu != "simplu" && tip_pariu != "multiplu" && tip_pariu != "sistem")
            {
                throw tipInvalid();
            }
        }
        catch(tipInvalid& e)
        {
            std::cout << e.what() << std::endl;
            ind--;
            continue;
        }

        std::cout << "introdu suma pe care vrei sa o pui pe acest pariu: ";
        double miza;
        std::cin >> miza;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        try
        {
            if(miza > suma)
            {
                throw sumaInvalida();
            }
        }
        catch(sumaInvalida& e)
        {
            std::cout << e.what() << std::endl;
            ind--;
            continue;
        }

        if(tip_pariu == "simplu")
        {
            try
            {
                Pariuri* pariu = creeazaPariuSimplu(miza, meciuri, actiuni, rezultate, vect_echipa1, vect_egal, vect_echipa2);
                vect_pariuri.push_back(pariu);
                suma -= miza;
            }
            catch (idInvalid& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (actiuneInvalida& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (alegereInvalida& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (numarInvalid& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
        }
        else if(tip_pariu == "multiplu")
        {
            try
            {
                Pariuri* pariu = creeazaPariuMultiplu(miza, meciuri, actiuni, rezultate, vect_echipa1, vect_egal, vect_echipa2);
                vect_pariuri.push_back(pariu);
                suma -= miza;
            }
            catch (idInvalid& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (actiuneInvalida& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (alegereInvalida& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (numarInvalid& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
        }
        else if(tip_pariu == "sistem")
        {
            std::cout << "introdu numarul minim de pariuri care trebuie sa iasa: ";
            int k;
            std::cin >> k;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            try
            {
                Pariuri* pariu = creeazaPariuSistem(miza, k, meciuri, actiuni, rezultate, vect_echipa1, vect_egal, vect_echipa2);
                vect_pariuri.push_back(pariu);
                suma -= miza;
            }
            catch (idInvalid& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (actiuneInvalida& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (alegereInvalida& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (numarInvalid& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
            catch (sistemInvalid& e)
            {
                std::cout << e.what() << std::endl;
                ind--;
                continue;
            }
        }
    }

    std::cout << "profiturile tale sunt: " << std::endl;
    for (const auto& pariu : vect_pariuri)
    {
        if(auto s = dynamic_cast<PariuSimplu*>(pariu))
        {
            std::cout << "pariu simplu ";
        }
        else if(auto m = dynamic_cast<PariuMultiplu*>(pariu))
        {
            std::cout << "pariu multiplu ";
        }
        else if(auto s = dynamic_cast<PariuSistem*>(pariu))
        {
            std::cout << "pariu sistem ";
        }
        std::cout << "pe meciul sau meciurile: " << std::endl;
        for(const auto& pariu_meci : pariu->get_vect_pariu_meci())
        {
            std::cout << "meciul: " << meciuri[pariu_meci.get_id_meci()].first << " vs " << meciuri[pariu_meci.get_id_meci()].second << std::endl;
        }
        pariu->afisare(std::cout);
    }
    std::cout << "banii ramasi nepariat: " << suma << std::endl;
    return 0;
}