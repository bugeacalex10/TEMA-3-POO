#ifndef REZULTATE_H
#define REZULTATE_H
#include <iostream>
#include <vector>
#include <string>
#include <map>

class Rezultate {
    private:
        int id_meci;
        std::string rezultat_meci;
        int nr_faulturi;
        int nr_cartonase_galbene;
        int nr_cartonase_rosii;
        int nr_cornere;
    public:
        Rezultate(int id_meci = 0, const std::string& rezultat_meci = "", int nr_faulturi = 0, int nr_cartonase_galbene = 0, int nr_cartonase_rosii = 0, int nr_cornere = 0) 
            : id_meci(id_meci), rezultat_meci(rezultat_meci), nr_faulturi(nr_faulturi), nr_cartonase_galbene(nr_cartonase_galbene), nr_cartonase_rosii(nr_cartonase_rosii), nr_cornere(nr_cornere) {}

        int get_id_meci() const { return id_meci; }
        std::string get_rezultat_meci() const { return rezultat_meci; }
        int get_nr_faulturi() const { return nr_faulturi; }
        int get_nr_cartonase_galbene() const { return nr_cartonase_galbene; }
        int get_nr_cartonase_rosii() const { return nr_cartonase_rosii; }
        int get_nr_cornere() const { return nr_cornere; }

        void afisare(std::ostream& out) const {
            out << "ID meci: " << id_meci << "\n";
            out << "Rezultat meci: " << rezultat_meci << "\n";
            out << "Numar faulturi: " << nr_faulturi << "\n";
            out << "Numar cartonase galbene: " << nr_cartonase_galbene << "\n";
            out << "Numar cartonase rosii: " << nr_cartonase_rosii << "\n";
            out << "Numar cornere: " << nr_cornere << "\n";
        }
        ~Rezultate() = default;
};
#endif
