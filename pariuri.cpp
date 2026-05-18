#include "pariuri.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ostream>

int Pariuri::nr_pariuri = 0;
Pariuri::Pariuri(const Pariuri& other) : miza(other.miza), vect_pariuri(other.vect_pariuri) {
    nr_pariuri++;
}
Pariuri& Pariuri::operator=(const Pariuri& other) 
{
    swap(const_cast<Pariuri&>(other));
    return *this;
}
void Pariuri::swap(Pariuri& other) noexcept
{
    std::swap(miza, other.miza);
    std::swap(vect_pariuri, other.vect_pariuri);
}

double PariuSimplu::calculeaza_castig() const
{
    if(vect_pariuri.size() != 1)
    {
        return 0;
    }
    if(vect_pariuri[0].vect_actiuni.size() != 1)
    {
        return 0;
    }
    const Actiune& actiune = vect_pariuri[0].vect_actiuni[0];
    if(actiune.tip == echipa)
    {
        if(actiune.alegere == actiune.rezultat)
        {
            return miza * actiune.cota;
        }
    }
    if(actiune.tip == fix)
    {
        if(actiune.alegere == actiune.rezultat)
        {
            return miza * actiune.cota;
        }
    }
    if(actiune.tip == peste)
    {
        if(std::stod(actiune.alegere) > std::stod(actiune.rezultat))
        {
            return miza * actiune.cota;
        }
    }
    if(actiune.tip == sub)
    {
        if(std::stod(actiune.alegere) < std::stod(actiune.rezultat))
        {
            return miza * actiune.cota;
        }
    }
    return 0;
}

double PariuMultiplu::calculeaza_castig() const 
{
    double castig = miza;
    for(const auto& pariu : vect_pariuri)
    {
        for(const auto& actiune : pariu.vect_actiuni)
        {
            if(actiune.tip == echipa)
            {
                if(actiune.alegere != actiune.rezultat)
                {
                    return 0;
                }
                castig *= actiune.cota;
            }
            else if(actiune.tip == fix)
            {
                if(actiune.alegere != actiune.rezultat)
                {
                    return 0;
                }
                castig *= actiune.cota;
            }
            else if(actiune.tip == peste)
            {
                if(std::stod(actiune.alegere) <= std::stod(actiune.rezultat))
                {
                    return 0;
                }
                castig *= actiune.cota;
            }
            else if(actiune.tip == sub)
            {
                if(std::stod(actiune.alegere) >= std::stod(actiune.rezultat))
                {
                    return 0;
                }
                castig *= actiune.cota;
            }
        }
    }
    return castig;
}

double PariuSistem::calculeaza_castig() const 
{
    int n = 0, actiuni = 0;
    double castig = 1;
    for(const auto& pariu : vect_pariuri)
    {
        for(const auto& actiune : pariu.vect_actiuni)
        {
            actiuni++;
            if(actiune.tip == echipa)
            {
                if(actiune.alegere == actiune.rezultat)
                {
                    n++;
                    castig *= actiune.cota;
                }
            }
            else if(actiune.tip == fix)
            {
                if(actiune.alegere == actiune.rezultat)
                {
                    n++;
                    castig *= actiune.cota;
                }
            }
            else if(actiune.tip == peste)
            {
                if(std::stod(actiune.alegere) > std::stod(actiune.rezultat))
                {
                    n++;
                    castig *= actiune.cota;
                }
            }
            else if(actiune.tip == sub)
            {
                if(std::stod(actiune.alegere) < std::stod(actiune.rezultat))
                {
                    n++;
                    castig *= actiune.cota;
                }
            }
        }
    }
    if(n >= k)
    {
        return miza * castig * n / actiuni;
    }
    return 0;
}

Pariuri* PariuSimplu::clone() const 
{
    return new PariuSimplu(*this);
}

Pariuri* PariuMultiplu::clone() const 
{
    return new PariuMultiplu(*this);
}

Pariuri* PariuSistem::clone() const 
{
    return new PariuSistem(*this);
}

void PariuSimplu::afisare(std::ostream& out) const
{
    double castig_total = this->calculeaza_castig();

    out << "miza initiala: " << miza << "\n";
    out << "castig: " << (castig_total - miza) << "\n";
}

void PariuMultiplu::afisare(std::ostream& out) const
{
    double castig_total = this->calculeaza_castig();

    out << "miza initiala: " << miza << "\n";
    out << "castig: " << (castig_total - miza) << "\n";
}

void PariuSistem::afisare(std::ostream& out) const
{
    double castig_total = this->calculeaza_castig();

    out << "miza initiala: " << miza << "\n";
    out << "castig: " << (castig_total - miza) << "\n";
}
