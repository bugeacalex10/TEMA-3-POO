#ifndef SABLOANE_H
#define SABLOANE_H

#include "pariuri.h"
#include <vector>
#include <string>

class PariuFactory 
{
public:
    static Pariuri* creeaza(const std::string& tip, double miza, int k = 0)
    {
        if (tip == "simplu")
        {
            return new PariuSimplu(miza);
        }
        if (tip == "multiplu")
        {
            return new PariuMultiplu(miza);
        }
        if (tip == "sistem")
        {
            return new PariuSistem(miza, k);
        }
        return nullptr;
    }
};

template <typename T>
class StatisticiPariuri 
{
    private:
        std::vector<T> valori;

    public:
        void adaugaValoare(const T& valoare) 
        {
            valori.push_back(valoare);
        }

    T suma() const 
    {
        T total = 0;
        for (const auto& valoare : valori) 
        {
            total += valoare;
        }
        return total;
    }

    T maxim() const 
    {
        if (valori.empty())
        {
            return T();
        }
        T maxValoare = valori[0];

        for (const auto& valoare : valori) 
        {
            if (valoare > maxValoare)
            {
                maxValoare = valoare;
            }
        }

        return maxValoare;
    }

    double medie() const 
    {
        if (valori.empty())
        {
            return 0;
        }
        return static_cast<double>(suma()) / valori.size();
    }
};

template <typename T>
T valoareMaiMare(T a, T b) 
{
    return (a > b) ? a : b;
}
template <typename T>
T castigPotential(T miza, T cota)
{
    return miza * cota;
}

inline void demonstrareSabloane() 
{
    Pariuri* p1 = PariuFactory::creeaza("simplu", 100);
    Pariuri* p2 = PariuFactory::creeaza("multiplu", 50);

    delete p1;
    delete p2;

    StatisticiPariuri<int> statisticiGoluri;
    statisticiGoluri.adaugaValoare(2);
    statisticiGoluri.adaugaValoare(3);
    statisticiGoluri.adaugaValoare(1);

    int totalGoluri = statisticiGoluri.suma();
    int maxGoluri = statisticiGoluri.maxim();
    double medieGoluri = statisticiGoluri.medie();

    StatisticiPariuri<double> statisticiCote;
    statisticiCote.adaugaValoare(1.75);
    statisticiCote.adaugaValoare(2.30);
    statisticiCote.adaugaValoare(1.95);

    double sumaCote = statisticiCote.suma();
    double maxCota = statisticiCote.maxim();
    double medieCote = statisticiCote.medie();

    int goluriMaiMulte = valoareMaiMare(2, 4);
    double cotaMaiMare = valoareMaiMare(1.80, 2.15);

    double castig1 = castigPotential(100.0, 1.85);
    int castig2 = castigPotential(50, 2);

    (void)totalGoluri;
    (void)maxGoluri;
    (void)medieGoluri;
    (void)sumaCote;
    (void)maxCota;
    (void)medieCote;
    (void)goluriMaiMulte;
    (void)cotaMaiMare;
}

#endif
