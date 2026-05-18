#ifndef EXCEPTII_H
#define EXCEPTII_H
#include <exception>
#include <string>

class ExceptiePariu : public std::exception {
    private:
        std::string mesaj;
    public:
        ExceptiePariu(const std::string& mesaj) : mesaj(mesaj) {}

        const char* what() const noexcept override {
            return mesaj.c_str();
        }
        ~ExceptiePariu() = default;
};
class varstaInvalida : public ExceptiePariu {
    public:
        varstaInvalida() : ExceptiePariu("Trebuie sa ai peste 18 ani pentru a paria, du-te inapoi la scoala! \n"){}
};
class sumaInvalida : public ExceptiePariu {
    public:
    sumaInvalida() : ExceptiePariu("Nu mai ai bani, alege o suma mai mica! \n"){}
};
class meciInvalid : public ExceptiePariu {
    public:
    meciInvalid() : ExceptiePariu("Nu ai ales un meci valid, alege o echipa care joaca sau egalitate! \n"){}
};
class actiuneInvalida : public ExceptiePariu {
    public:
    actiuneInvalida() : ExceptiePariu("Nu ai ales o actiune valida, alege una dintre actiunile disponibile! \n"){}
};
class sistemInvalid : public ExceptiePariu {
    public:
    sistemInvalid() : ExceptiePariu("Numarul minim de pariuri care trebuie sa iasa nu poate fi mai mare sau egal cu numarul total de pariuri! \n"){}
};
class idInvalid : public ExceptiePariu {
    public:
    idInvalid() : ExceptiePariu("Nu ai ales un id valid, alege un id din lista! \n"){}
};
class alegereInvalida : public ExceptiePariu {
    public:
    alegereInvalida() : ExceptiePariu("Nu ai ales o alegere valida, alege una dintre optiunile disponibile! \n"){}
};
class numarInvalid : public ExceptiePariu {
    public:
    numarInvalid() : ExceptiePariu("Pune un numar mai mare sau egal cu 0! \n"){}
};
class tipInvalid : public ExceptiePariu {
    public:
    tipInvalid() : ExceptiePariu("Nu ai ales un tip valid, alege una dintre optiunile disponibile! \n"){}
};

#endif