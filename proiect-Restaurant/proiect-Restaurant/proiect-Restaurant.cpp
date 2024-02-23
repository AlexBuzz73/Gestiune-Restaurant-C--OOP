#include <iostream>
#include <string>
using namespace std;

class Ingredient {
    const int id;
    char* denumire = nullptr;
    static int nrIngrediente;
public:
    Ingredient() :id(++nrIngrediente), denumire(nullptr) {}
    Ingredient(const char* denumire) :id(++nrIngrediente)
    {
        if (denumire != nullptr && strlen(denumire) >= 2) {//de ex pot adauga 'ou'
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
        else {
            this->denumire = nullptr;
        }
    }

    Ingredient(const Ingredient& i) :id(++nrIngrediente)
    {
        if (i.denumire != nullptr && strlen(i.denumire) >= 2) {//de ex pot adauga 'ou'
            this->denumire = new char[strlen(i.denumire) + 1];
            strcpy(this->denumire, i.denumire);
        }
        else {
            this->denumire = nullptr;
        }
    }

    Ingredient& operator=(const Ingredient& i)
    {
        if (this != &i)
        {
            delete[] this->denumire;
            this->denumire = nullptr;

            if (i.denumire != nullptr && strlen(i.denumire) >= 2) {//de ex pot adauga 'ou'
                this->denumire = new char[strlen(i.denumire) + 1];
                strcpy(this->denumire, i.denumire);
            }
            else {
                this->denumire = nullptr;
            }
        }
        return *this;
    }

    void setDenumire(const char* denumire)
    {
        if (denumire != nullptr && strlen(denumire) >= 2)
        {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
        else throw exception("\nNumele trebuie sa aiba cel putin 2 caractere.");
    }
    const char* getDenumire()
    {
        if (denumire != nullptr && strlen(denumire) >= 2)
            return this->denumire;
        else return nullptr;
    }

    const int getId()
    {
        return this->id;
    }

    friend istream& operator>>(istream& in, Ingredient& i)
    {
        delete[] i.denumire;
        i.denumire = nullptr;

        cout << "\nIntroduceti denumirea ingredientului:";
        string buffer;
        getline(in, buffer);
        i.denumire = new char[buffer.length() + 1];
        strcpy(i.denumire, buffer.data());
        return in;
    }

    friend ostream& operator<<(ostream& out, Ingredient& i)
    {
        out << "\n--------------------------------";
        out << "\nId:" << i.id;
        out << "\nDenumire:";
        if (i.denumire != nullptr) {
            out << i.denumire;
        }
        else out << "-";
        out << "\n--------------------------------";

        return out;
    }

    friend bool operator==(string denumire, const Ingredient& i)
    {
        if (denumire == i.denumire)
            return true;
        return false;
    }

    ~Ingredient() {
        delete[] this->denumire;
        this->denumire = nullptr;
    }

};
int Ingredient::nrIngrediente = 0;

class Stoc2 {
    float stocIngredient;
public:
    float getStocIngredient()
    {
        if (this->stocIngredient > 0)
            return this->stocIngredient;
    }
    void setStocIngredient(float valoare)
    {
        if (valoare > 0)
            this->stocIngredient = valoare;
    }

    Stoc2(float stocIngredient) :stocIngredient(stocIngredient) {}

    Stoc2(const Stoc2& s) {
        this->stocIngredient = s.stocIngredient;
    }

    Stoc2 operator=(const Stoc2& s)
    {
        if (this != &s)
        {
            this->stocIngredient = s.stocIngredient;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Stoc2& s)
    {
        out << "\nStocul ingredientului:" << s.stocIngredient;
        return out;
    }

    bool operator>(float valoare)
    {
        if (this->stocIngredient > valoare)return true;
        else return false;
    }

    bool operator<(float valoare)
    {
        if (this->stocIngredient < valoare)return true;
        return false;

    }

    Stoc2 operator+=(float stocDeAdaugat)
    {
        if (stocDeAdaugat > 0)
        {
            this->stocIngredient += stocDeAdaugat;
            return *this;
        }
        else throw exception("\nValoare negativa.");
    }

    Stoc2 operator-=(float stocDeScazut)
    {
        if (this->stocIngredient > 0)
        {
            if (this->stocIngredient - stocDeScazut >= 0)
            {
                this->stocIngredient -= stocDeScazut;
                return *this;
            }
            else throw exception("\nScadere invalida.");
        }
    }

    bool operator<=(float valoare)
    {
        if (valoare > 0)
        {
            if (this->stocIngredient <= valoare)return true;
            return false;
        }
    }


    /*Stoc2 operator+(float stocDeAdaugat)
    {
        if (stocDeAdaugat > 0)
        {
            Stoc2 copie = *this;
            copie.stocIngredient += stocDeAdaugat;
            return copie;
        }
        else throw exception("\nValoare negativa.");
    }*/
    ~Stoc2() {}
};

class Reteta {
    int nrIngrediente = 0;
    Ingredient** listaIngrediente = nullptr;
    float* listaCantitati = nullptr;
    float durata = 0;

public:
    //getter setter

    void setIngrediente(const Ingredient** listaIngrediente, const float* listaCantitati, int nrIngrediente)
    {
        if (this->listaCantitati != nullptr && this->listaIngrediente != nullptr && this->nrIngrediente > 0)
        {
            delete[] this->listaCantitati;
            this->listaCantitati = nullptr;
            delete[] this->listaIngrediente;
            this->listaIngrediente = nullptr;
            this->nrIngrediente = nrIngrediente;

            this->listaCantitati = new float[this->nrIngrediente];
            this->listaIngrediente = new Ingredient * [this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++)
            {
                this->listaCantitati[i] = listaCantitati[i];
                this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
            }
        }
    }
    Ingredient** getListaIngrediente() const
    {
        if (this->listaIngrediente != nullptr)
            return this->listaIngrediente;
    }
    Ingredient getDenumireIngredient(int index)
    {
        if (index >= 0 && index < this->nrIngrediente)
            return this->listaIngrediente[index]->getDenumire();

    }
    const float* getListaCantitati()
    {
        if (this->listaCantitati != nullptr)
            return this->listaCantitati;
    }

    int getNrIngrediente()
    {
        if (this->nrIngrediente > 0)
            return this->nrIngrediente;
    }

    float getCantitateReteta(int index)
    {
        if (index >= 0 && index < this->nrIngrediente)
            return this->listaCantitati[index];
    }

    void setDurata(float durata)
    {
        if (durata > 0)
            this->durata = durata;

    }
    float getDurata()
    {
        if (this->durata > 0)
            return this->durata;
    }

    Reteta() {}

    Reteta(int nrIngrediente, Ingredient** listaIngrediente, float* listaCantitati, float durata)
    {
        if (nrIngrediente > 0 && listaIngrediente != nullptr && listaCantitati != nullptr)
        {
            this->nrIngrediente = nrIngrediente;
            this->listaIngrediente = new Ingredient * [this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++)
            {
                this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
            }

            this->listaCantitati = new float[this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++)
                this->listaCantitati[i] = listaCantitati[i];
        }

        if (durata > 0)this->durata = durata;
    }

    Reteta(const Reteta& r)
    {
        if (r.nrIngrediente > 0 && r.listaIngrediente != nullptr && r.listaCantitati != nullptr)
        {
            this->nrIngrediente = r.nrIngrediente;
            this->listaIngrediente = new Ingredient * [this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++)
            {
                this->listaIngrediente[i] = new Ingredient(*r.listaIngrediente[i]);
            }

            this->listaCantitati = new float[this->nrIngrediente];
            for (int i = 0; i < this->nrIngrediente; i++)
                this->listaCantitati[i] = r.listaCantitati[i];
        }
        if (r.durata > 0)this->durata = r.durata;
    }

    Reteta& operator=(const Reteta& r)
    {
        if (this != &r)
        {
            if (r.nrIngrediente > 0 && r.listaIngrediente != nullptr && r.listaCantitati != nullptr)
            {
                this->nrIngrediente = r.nrIngrediente;
                this->listaIngrediente = new Ingredient * [this->nrIngrediente];
                for (int i = 0; i < this->nrIngrediente; i++)
                {
                    this->listaIngrediente[i] = new Ingredient(*r.listaIngrediente[i]);
                }

                this->listaCantitati = new float[this->nrIngrediente];
                for (int i = 0; i < this->nrIngrediente; i++)
                    this->listaCantitati[i] = r.listaCantitati[i];
            }
            if (r.durata > 0)this->durata = r.durata;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Reteta& r)
    {
        //out << "\n----------------";
        out << "\nIngrediente: ";
        if (r.nrIngrediente > 0 && r.listaCantitati != nullptr && r.listaIngrediente != nullptr)
        {
            for (int i = 0; i < r.nrIngrediente; i++)
            {
                const char* denumire = r.listaIngrediente[i]->getDenumire();
                if (denumire != nullptr)
                    out << denumire << " " << r.listaCantitati[i] << "g; ";
            }
        }
        else out << "-";
        out << "\nDurata:" << r.durata;
        //out << "\n----------------";
        return out;
    }

    friend istream& operator>>(istream& in, Reteta& r)
    {
        for (int i = 0; i < r.nrIngrediente; i++)
        {
            delete[] r.listaIngrediente[i];
            r.listaIngrediente[i] = nullptr;
        }
        r.listaIngrediente = nullptr;
        delete[] r.listaCantitati;
        r.listaCantitati = nullptr;

        cout << "\nIntroduceti nr ingrediente:";
        in >> r.nrIngrediente;
        in.ignore();

        if (r.nrIngrediente > 0)
        {
            cout << "\nIntroduceti denumire ingredient si cantitatea necesara:";
            r.listaCantitati = new float[r.nrIngrediente];
            r.listaIngrediente = new Ingredient * [r.nrIngrediente];
            for (int i = 0; i < r.nrIngrediente; i++)
            {
                cout << "\nDenumire ingredient " << i + 1 << ":";
                string buffer;
                getline(in, buffer);
                r.listaIngrediente[i] = new Ingredient(buffer.data());
                cout << "\nCantitate necesara ingredient " << i + 1 << ":";
                in >> r.listaCantitati[i];
                in.ignore();
            }
        }
        else {
            r.nrIngrediente = 0;
            r.listaCantitati = nullptr;
            r.listaIngrediente = nullptr;
        }

        cout << "\nIntroduceti durata:";
        in >> r.durata;

        return in;
    }

    void adaugaIngredient(Ingredient* ingredient, float cantitate) {
        if (cantitate > 0)
        {
            Ingredient** newListaIngrediente = new Ingredient * [nrIngrediente + 1];
            float* newListaCantitati = new float[nrIngrediente + 1];

            for (int i = 0; i < nrIngrediente; i++) {
                newListaIngrediente[i] = listaIngrediente[i];
                newListaCantitati[i] = listaCantitati[i];
            }

            newListaIngrediente[nrIngrediente] = ingredient;
            newListaCantitati[nrIngrediente] = cantitate;

            delete[] listaIngrediente;
            delete[] listaCantitati;
            nrIngrediente++;

            listaIngrediente = newListaIngrediente;
            listaCantitati = newListaCantitati;

        }
        else throw exception("\nCantitatea trebuie sa fie mai mare decat 0.");
    }

    explicit operator float()
    {
        float suma = 0;
        for (int i = 0; i < this->nrIngrediente; i++)
            suma += this->listaCantitati[i];
        return suma;
    }

    Ingredient* operator[](int index)
    {
        if (index >= 0 && index < this->nrIngrediente)
            return this->listaIngrediente[index];
    }
    ~Reteta()
    {
        //for (int i = 0; i < this->nrIngrediente; i++)
        //{
        //    delete[] this->listaIngrediente[i];
        //    this->listaIngrediente[i] = nullptr;
        //}
        //nu mai adaug asta fiindca deja se distrug ingredientele de la destructorul clasei ingredient?
        delete[] this->listaIngrediente;
        this->listaIngrediente = nullptr;
        delete[] this->listaCantitati;
        this->listaCantitati = nullptr;
    }
};

class Preparat {
    const int id;
    char* denumire = nullptr;
    float cantitate = 0;
    float pret = 0;
    Reteta reteta;
    static int nrPreparate;
    static int cantitateMinima;

public:
    //getter setter
    static void setCantitateMinima(int cantitateMinima)
    {
        if (cantitateMinima > 0)
            Preparat::cantitateMinima = cantitateMinima;
    }
    static int getCantitateMinima()
    {
        if (Preparat::cantitateMinima > 0)
            return Preparat::cantitateMinima;
    }
    void setDenumire(const char* denumire)
    {
        if (denumire != nullptr && strlen(denumire) >= 2)
        {
            delete[] this->denumire;
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
    }
    const char* getDenumire()
    {
        if (denumire != nullptr && strlen(denumire) >= 2)
            return this->denumire;
    }


    void setCantitate(float cantitate)
    {
        if (cantitate > Preparat::cantitateMinima)
            this->cantitate = cantitate;
    }
    float getCantitate()
    {
        if (this->cantitate > 0)
            return this->cantitate;
    }

    void setPret(float pret)
    {
        if (pret > 0)this->pret = pret;
    }
    float getPret()
    {
        if (this->pret > 0)
            return this->pret;
    }

    const int getId()
    {
        return this->id;
    }

    const Reteta& getReteta() const
    {
        return reteta;
    }
    float getCantitateReteta(int index)
    {
        if (index >= 0 && index < reteta.getNrIngrediente())
            return reteta.getCantitateReteta(index);
    }

    Preparat() :id(++nrPreparate) {}

    Preparat(const char* denumire, float cantitate, float pret, Reteta reteta)
        :id(++nrPreparate) {
        if (denumire != nullptr)
        {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }

        if (cantitate > 0)
            this->cantitate = cantitate;

        if (pret > 0)
            this->pret = pret;
        // if (reteta.getDurata() != 0 && reteta.getNrIngrediente()!=0)
        this->reteta = reteta;
    }
    Preparat(const Preparat& p) :id(++nrPreparate)
    {
        if (p.denumire != nullptr)
        {
            this->denumire = new char[strlen(p.denumire) + 1];
            strcpy(this->denumire, p.denumire);
        }

        if (p.cantitate > 0)
            this->cantitate = p.cantitate;

        if (p.pret > 0)
            this->pret = p.pret;
        //if(reteta.getDurata() != 0 && reteta.getNrIngrediente() != 0)
        this->reteta = p.reteta;
    }

    Preparat& operator=(const Preparat& p)
    {
        if (this != &p)
        {
            delete[] this->denumire;
            this->denumire = nullptr;

            if (p.denumire != nullptr)
            {
                this->denumire = new char[strlen(p.denumire) + 1];
                strcpy(this->denumire, p.denumire);
            }
            else this->denumire = nullptr;

            if (p.cantitate > 0)
                this->cantitate = p.cantitate;
            else this->cantitate = 0;
            if (p.pret > 0)
                this->pret = p.pret;
            else this->pret = 0;

            //if (reteta.getDurata() != 0 && reteta.getNrIngrediente() != 0)
            this->reteta = p.reteta;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Preparat& p)
    {
        out << "\n----------------------------------------------------------------------------";
        out << "\nId preparat:" << p.id;
        out << "\nDenumire preparat:";
        if (p.denumire != nullptr) out << p.denumire;
        else out << "-";
        out << "\nCantitate:" << p.cantitate << "g";
        out << "\nPret:" << p.pret << " lei";
        out << p.reteta;
        out << "\n----------------------------------------------------------------------------";
        return out;
    }

    friend istream& operator>>(istream& in, Preparat& p)
    {
        delete[] p.denumire;
        p.denumire = nullptr;

        do {
            cout << "\nIntroduceti denumirea preparatului:";
            string buffer;
            getline(in, buffer);

            bool valid = true;
            for (char ch : buffer)
            {
                if (isalpha(ch) == false && isspace(ch) == false) {
                    valid = false;
                    break;
                }
            }

            if (valid == false) {
                cout << "\nDenumirea trebuie sa contina doar litere si spatii.Introduceti din nou.";
            }
            else {
                p.denumire = new char[buffer.length() + 1];
                strcpy(p.denumire, buffer.data());
            }

        } while (p.denumire == nullptr);

        do {
            cout << "\nIntroduceti cantitatea preparatului:";
            in >> p.cantitate;

            if (p.cantitate < Preparat::cantitateMinima)
                cout << "\nCantitatea trebuie sa fie cel putin 100 grame. Introduceti din nou o valoare.";
        } while (p.cantitate < Preparat::cantitateMinima);

        do {
            cout << "\nIntroduceti pretul preparatului:";
            in >> p.pret;

            if (p.pret < 2)
                cout << "\nPretul trebuie sa fie cel putin 2 lei. Introduceti din nou o valoare.";
        } while (p.pret < 2);

        cout << "\nIntroduceti reteta:";
        in >> p.reteta;

        return in;
    }

    bool operator==(const char* numePreparat)
    {
        if (this->denumire != nullptr && numePreparat != nullptr)
        {
            if (strcmp(this->denumire, numePreparat) == 0)return true;
            return false;
        }
        else throw exception("\nNu toate ingredientele au denumire.");
    }

    friend bool operator==(const char* denumire, const Preparat& p)
    {
        if (p.denumire != nullptr)
        {
            if (strcmp(p.denumire, denumire) == 0)return true;
            return false;
        }
        else throw exception("\nNu exista denumire.");
    }

    explicit operator float()
    {
        if (this->pret > 0)return this->pret;
        return 0;
    }

    ~Preparat()
    {
        delete[] this->denumire;
        this->denumire = nullptr;
    }
};

int Preparat::nrPreparate = 0;
int Preparat::cantitateMinima = 100;

class Comanda {
    const int idComanda;
    Preparat** listaPreparate = nullptr;
    int* nrPortii = nullptr;
    int nrPreparate = 0;
    static int nrComenzii;

public:
    Comanda() :idComanda(++nrComenzii) {}

    //>> si <<
    Preparat** getPreparateComanda()
    {
        if (this->listaPreparate != nullptr)
            return this->listaPreparate;
    }
    int* getNrPortii()
    {
        if (this->nrPortii != nullptr)
            return this->nrPortii;
    }
    int getNrPortie(int index)
    {
        if (index > 0 && index < this->nrPreparate)
            return this->nrPortii[index];
    }
    int getNrPreparate()
    {
        if (this->nrPreparate > 0)
            return this->nrPreparate;
    }

    Comanda(Preparat** listaPreparate, int* nrPortii, int nrPreparate)
        :idComanda(++nrComenzii) {
        if (listaPreparate != nullptr && nrPortii != nullptr && nrPreparate != 0)
        {
            this->nrPreparate = nrPreparate;
            this->listaPreparate = new Preparat * [this->nrPreparate];
            for (int i = 0; i < this->nrPreparate; i++)
                this->listaPreparate[i] = new Preparat(*listaPreparate[i]);
            this->nrPortii = new int[this->nrPreparate];
            for (int i = 0; i < this->nrPreparate; i++)
                this->nrPortii[i] = nrPortii[i];
        }
        else {
            this->nrPreparate = 0;
            this->listaPreparate = nullptr;
            this->nrPortii = nullptr;
        }
    }
    Comanda(const Comanda& c) :idComanda(++nrComenzii)
    {
        if (c.listaPreparate != nullptr && c.nrPortii != nullptr && c.nrPreparate != 0)
        {
            this->nrPreparate = c.nrPreparate;
            this->listaPreparate = new Preparat * [this->nrPreparate];
            for (int i = 0; i < this->nrPreparate; i++)
                this->listaPreparate[i] = new Preparat(*c.listaPreparate[i]);
            this->nrPortii = new int[this->nrPreparate];
            for (int i = 0; i < this->nrPreparate; i++)
                this->nrPortii[i] = c.nrPortii[i];
        }
        else {
            this->nrPreparate = 0;
            this->listaPreparate = nullptr;
            this->nrPortii = nullptr;
        }
    }

    Comanda& operator=(const Comanda& c)
    {
        if (this != &c)
        {
            for (int i = 0; i < this->nrPreparate; i++)
                delete this->listaPreparate[i];
            delete[] this->listaPreparate;
            this->listaPreparate = nullptr;
            delete[] this->nrPortii;
            this->nrPortii = nullptr;

            if (c.listaPreparate != nullptr && c.nrPortii != nullptr && c.nrPreparate != 0)
            {
                this->nrPreparate = c.nrPreparate;
                this->listaPreparate = new Preparat * [this->nrPreparate];
                for (int i = 0; i < this->nrPreparate; i++)
                    this->listaPreparate[i] = new Preparat(*c.listaPreparate[i]);
                this->nrPortii = new int[this->nrPreparate];
                for (int i = 0; i < this->nrPreparate; i++)
                    this->nrPortii[i] = c.nrPortii[i];
            }
            else {
                this->nrPreparate = 0;
                this->listaPreparate = nullptr;
                this->nrPortii = nullptr;
            }
        }
        return *this;
    }
    void adaugaPreparat(Preparat* preparat, int nrPortii)
    {
        if (nrPortii > 0)
        {
            for (int i = 0; i < this->nrPreparate; i++)
            {
                if (strcmp(this->listaPreparate[i]->getDenumire(), preparat->getDenumire()) == 0)
                {
                    this->nrPortii[i] += nrPortii;
                    return;
                }
            }

            Preparat** copie1 = new Preparat * [this->nrPreparate + 1];
            int* copie2 = new int[this->nrPreparate + 1];

            for (int i = 0; i < this->nrPreparate; i++)
            {
                copie1[i] = this->listaPreparate[i];
                copie2[i] = this->nrPortii[i];
            }

            copie1[this->nrPreparate] = preparat;
            copie2[this->nrPreparate] = nrPortii;

            delete[] this->listaPreparate;
            delete[] this->nrPortii;

            this->nrPreparate++;
            this->listaPreparate = copie1;
            this->nrPortii = copie2;
        }
        else throw exception("\nNumarul de portii nu poate fi mai mic decat 1.");
    }

    friend istream& operator>>(istream& in, Comanda& c)
    {
        cout << "\nIntroduceti nr de preparate dorite:";
        in >> c.nrPreparate;
        if (c.nrPreparate > 0)
        {
            c.listaPreparate = new Preparat * [c.nrPreparate];
            c.nrPortii = new int[c.nrPreparate];
            for (int i = 0; i < c.nrPreparate; i++)
            {
                cout << "\nIntroduceti denumirea preparatului dorit " << i + 1 << ":";
                string buffer;
                in.ignore();
                getline(in, buffer);
                c.listaPreparate[i] = new Preparat(buffer.data(), 0, 0, Reteta());
                cout << "\nCate portii doriti? ";
                in >> c.nrPortii[i];
            }
        }
        else {
            c.nrPreparate = 0;
            c.listaPreparate = nullptr;
            c.nrPortii = 0;
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Comanda& c)
    {
        out << "\n-------------------------------------";
        //out << "\nId comanda:" << c.idComanda;
        out << "\nPreparate comandate si portiile lor:";
        if (c.nrPreparate > 0 && c.listaPreparate != nullptr && c.nrPortii != nullptr)
        {
            for (int i = 0; i < c.nrPreparate; i++)
            {
                out << "\nPreparat " << i + 1 << ":" << c.listaPreparate[i]->getDenumire() << "   Nr portii:" << c.nrPortii[i];
            }
        }
        else out << "-";
        out << "\n";
        return out;
    }

    void afisareComanda()
    {
        //cout << "\nComanda " << this->idComanda << "- Detalii:\n";
        float sumaTotala = 0;
        for (int i = 0; i < this->nrPreparate; i++)
        {
            cout << "Preparat: " << this->listaPreparate[i]->getDenumire() << "\n";
            cout << "Numar portii: " << this->nrPortii[i] << "\n";
            cout << "Cost total preparat: " << listaPreparate[i]->getPret() * this->nrPortii[i];
            sumaTotala += this->listaPreparate[i]->getPret() * this->nrPortii[i];
            cout << "\n--------------------------------------------------------\n";
        }

        cout << "Cost total comanda: " << sumaTotala;
        cout << "\n--------------------------------------------------------\n";
    }

    ~Comanda()
    {
        /*for (int i = 0; i < this->nrPreparate; i++)
             delete this->listaPreparate[i];*/
        delete[] this->listaPreparate;
        this->listaPreparate = nullptr;
        delete[] this->nrPortii;
        this->nrPortii = nullptr;
    }
};

int Comanda::nrComenzii = 0;

class Restaurant {

    static Ingredient** listaIngrediente;
    static Stoc2** listaStocuri;
    static int nrIngrediente;
    static Reteta** listaRetete;
    static Preparat** listaPreparate;
    static int nrPreparate;
    Comanda** listaComenzi = nullptr;
    int nrComenzi = 0;
    int idComandaCurenta = 1;
public:
    Restaurant() {
        this->listaComenzi = nullptr;
        this->nrComenzi = 0;
        this->idComandaCurenta = 1;
    }

    ~Restaurant() {
        for (int i = 0; i < this->nrComenzi; i++)
            delete listaComenzi[i];
        delete[] listaComenzi;
    }
    static void adaugaIngredientRestaurant(Ingredient* ingredient, Stoc2* stoc)
    {
        if (stoc != nullptr && *stoc > 0)
        {
            Ingredient** copieListaIngrediente = new Ingredient * [nrIngrediente + 1];
            Stoc2** copieListaStocuri = new Stoc2 * [nrIngrediente + 1];

            for (int i = 0; i < nrIngrediente; i++)
            {
                copieListaIngrediente[i] = listaIngrediente[i];
                copieListaStocuri[i] = listaStocuri[i];
            }

            copieListaIngrediente[nrIngrediente] = ingredient;
            copieListaStocuri[nrIngrediente] = new Stoc2(*stoc);

            delete[] Restaurant::listaIngrediente;
            delete[]Restaurant::listaStocuri;

            Restaurant::nrIngrediente++;
            Restaurant::listaIngrediente = copieListaIngrediente;
            Restaurant::listaStocuri = copieListaStocuri;

        }
        else throw exception("\nValoare invalida.");
    }

    static void adaugaPreparatRestaurant(Preparat* preparat, Reteta* reteta)
    {
        Preparat** copieListaPreparate = new Preparat * [Restaurant::nrPreparate + 1];
        Reteta** copieListaRetete = new Reteta * [Restaurant::nrPreparate + 1];

        for (int i = 0; i < Restaurant::nrPreparate; i++)
        {
            copieListaPreparate[i] = listaPreparate[i];
            copieListaRetete[i] = listaRetete[i];
        }

        copieListaPreparate[Restaurant::nrPreparate] = preparat;
        copieListaRetete[Restaurant::nrPreparate] = reteta;

        delete[] Restaurant::listaPreparate;
        delete[]Restaurant::listaRetete;

        Restaurant::nrPreparate++;
        Restaurant::listaPreparate = copieListaPreparate;
        Restaurant::listaRetete = copieListaRetete;
    }

    /* static void adaugaComanda(Comanda* comanda)
     {
         listaComenzi[nrComenzi] =comanda;
         nrComenzi++;
     }*/
    static int getNrIngred()
    {
        return Restaurant::nrIngrediente;
    }
    static int getNrPreparate()
    {
        return Restaurant::nrPreparate;
    }
    void afisareListaIngrediente()
    {

        if (Restaurant::listaIngrediente != nullptr && Restaurant::listaStocuri != nullptr)
        {
            for (int i = 0; i < Restaurant::nrIngrediente; i++)
            {
                cout << "\nIngredientul " << Restaurant::listaIngrediente[i]->getId() << ":";
                cout << Restaurant::listaIngrediente[i]->getDenumire();
                cout << "\tStoc:" << Restaurant::listaStocuri[i]->getStocIngredient();
            }
        }
        else cout << "\nNu exista ingrediente.";
    }

    void afisareRetete()
    {
        for (int i = 0; i < nrPreparate; i++)
        {
            cout << "\n------------------------------------------------------------------";
            cout << "\nReteta " << i + 1 << ":";
            cout << *listaRetete[i];
        }
    }

    void afisareProduseMeniu()
    {
        if (Restaurant::listaPreparate != nullptr && Restaurant::listaRetete != nullptr)
        {
            for (int i = 0; i < Restaurant::nrPreparate; i++)
            {
                cout << "\n----------------------------------------------------------------";
                cout << "\nPreparatul " << Restaurant::listaPreparate[i]->getId() << ":";
                cout << Restaurant::listaPreparate[i]->getDenumire();
                cout << "\nCantitate:" << Restaurant::listaPreparate[i]->getCantitate();
                cout << "\nPret:" << Restaurant::listaPreparate[i]->getPret();
                cout << "\nIngrediente:";
                Reteta* retetaPreparat = Restaurant::listaRetete[i];
                if (retetaPreparat != nullptr)
                {
                    Ingredient** ingredientePreparat = Restaurant::listaRetete[i]->getListaIngrediente();
                    if (ingredientePreparat != nullptr)
                    {
                        for (int j = 0; j < retetaPreparat->getNrIngrediente(); j++)
                            cout << ingredientePreparat[j]->getDenumire() << "; ";
                    }
                }
            }
        }
        else cout << "\nNu exista produse.";
    }
    int cautaIngred(string denumire)
    {
        for (int i = 0; i < nrIngrediente; i++)
        {
            if (denumire == listaIngrediente[i]->getDenumire())
                return i;
        }
        return -1;
    }
    int cautaPreparat(string denumire)
    {
        for (int i = 0; i < Restaurant::nrPreparate; i++)
        {
            if (denumire == listaPreparate[i]->getDenumire())
                return i;
        }
        return -1;
    }

    void adaugaComanda(Comanda* comanda)
    {
        Comanda** copie = new Comanda * [nrComenzi + 1];
        for (int i = 0; i < this->nrComenzi; i++)
            copie[i] = this->listaComenzi[i];

        copie[nrComenzi] = comanda;

        delete[] this->listaComenzi;
        nrComenzi++;
        this->listaComenzi = copie;
    }

    bool verificaStoc(Reteta* reteta, int nrPortii)
    {
        if (reteta != nullptr) {
            bool existaStoc = true;
            Ingredient** copieIngrediente = reteta->getListaIngrediente();
            for (int i = 0; i < reteta->getNrIngrediente(); i++)
            {
                int indexIngred = cautaIngred(copieIngrediente[i]->getDenumire());
                if (*listaStocuri[indexIngred] < nrPortii * reteta->getCantitateReteta(i) && indexIngred != -1)
                {
                    cout << "\nStoc insuficient pentru ingredientul " << listaIngrediente[indexIngred]->getDenumire();
                    //cout << "\nStocul pentru ingred " << listaIngrediente[indexIngred]->getDenumire() << " este:";
                    //cout << *listaStocuri[indexIngred];
                    existaStoc = false;
                }
            }

            if (existaStoc)
            {
                for (int i = 0; i < reteta->getNrIngrediente(); i++)
                {
                    int indexIngred = cautaIngred(copieIngrediente[i]->getDenumire());
                    *listaStocuri[indexIngred] -= nrPortii * reteta->getCantitateReteta(i);
                }
                return true;
            }

        }

        return false;
    }

    void adaugaProdusLaComanda()
    {
        Comanda comanda;
        string raspuns;
        string denumire;
        int nrPortii;

        Comanda** copie = new Comanda * [nrComenzi + 1];
        for (int i = 0; i < nrComenzi; i++)
            copie[i] = listaComenzi[i];
        delete[] listaComenzi;
        listaComenzi = copie;

        do {
            cout << "\nIntroduceti denumirea preparatului dorit:";
            getline(cin, denumire);

            int indexPreparat = cautaPreparat(denumire);

            if (indexPreparat != -1)
            {
                do {
                    cout << "\nCate portii doriti?";
                    cin >> nrPortii;
                    if (nrPortii < 1)
                    {
                        cout << "\nNumarul trebuie sa fie cel putin 1.";
                    }
                } while (nrPortii < 1);

                if (verificaStoc(listaRetete[indexPreparat], nrPortii)) {
                    comanda.adaugaPreparat(listaPreparate[indexPreparat], nrPortii);

                    cout << "\nPreparatul " << denumire << " a fost adaugat la comanda.";
                }
                else {
                    cout << "\nNu s-a putut adauga preparatul " << denumire << " la comanda.";
                }
            }
            else {
                cout << "\nPreparatul cu denumirea " << denumire << " nu a fost gasit.";
                cout << "\nReincercati introducerea denumirii.";
            }

            cout << "\nMai doriti si altceva? (Da sau Nu) ";
            cin >> raspuns;
            cin.ignore();

        } while (raspuns == "Da" || raspuns == "da");

        listaComenzi[nrComenzi] = new Comanda(comanda);
        nrComenzi++;
        cout << "\nDetaliile comenzii:";
        comanda.afisareComanda();

    }

    void afisareIstoricComenzi()
    {
        if (listaComenzi != nullptr)
        {
            for (int i = 0; i < this->nrComenzi; i++)
            {
                cout << "\nComanda " << i + 1 << "- Detalii:";
                cout << *listaComenzi[i];
            }
        }
        else throw exception("\nNu exista comenzi in istoric.");
    }

    void cresteStocuri(float stocDeAdaugat)
    {
        if (stocDeAdaugat > 0)
        {
            if (listaStocuri != nullptr)
            {
                for (int i = 0; i < nrIngrediente; i++)
                {
                    *listaStocuri[i] += stocDeAdaugat;
                }
            }
            else throw exception("\nNu exista stocuri.");
        }
        else throw exception("\nValoare negativa.");
    }

    Stoc2 operator[](int index)
    {
        if (index >= 0 && index < Restaurant::nrIngrediente)
        {
            return *listaStocuri[index];
        }
    }

    void adaugaStocIngredient(int index, float cantitate)
    {
        //if (index >= 1 && index <= Restaurant::nrIngrediente)
         //{
        if (cantitate > 0)
        {
            for (int i = 0; i < Restaurant::nrIngrediente; i++)
            {
                if (index == Restaurant::listaIngrediente[i]->getId())
                {
                    *listaStocuri[i] += cantitate;
                    cout << "\nStocul ingredientului " << listaIngrediente[i]->getDenumire();
                    cout << " a fost actualizat cu succes.\nNoul stoc este:" << listaStocuri[i]->getStocIngredient();
                }
            }
        }
        else throw exception("\nValoare negativa.");
        //}
       // else throw exception("\nID-ul nu a fost gasit.Stocul nu s-a actualizat.");
    }


    void modificaStocIngredientDeLaTastatura()
    {
        cout << "\nIntroduceti denumirea ingredientului pentru care se face modificarea:";
        string denumire;
        getline(cin, denumire);

        for (int i = 0; i < Restaurant::nrIngrediente; i++)
        {
            if (denumire == *listaIngrediente[i])
            {
                float cantitate;
                do {
                    cout << "\nIntroduceti cantitatea cu care se modifica stocul:";
                    cin >> cantitate;
                    if (cantitate < 1) {
                        cout << "\nCantitatea trebuie sa fie cel putin 1.";
                    }
                    cin.ignore();
                } while (cantitate < 1);
                adaugaStocIngredient(listaIngrediente[i]->getId(), cantitate);
                return;
            }
        }
        cout << "\nIngredientul cu denumirea " << denumire << " nu a fost gasit.";
    }

};
Ingredient** Restaurant::listaIngrediente = nullptr;
int Restaurant::nrIngrediente = 0;
Stoc2** Restaurant::listaStocuri = nullptr;
Reteta** Restaurant::listaRetete = nullptr;
Preparat** Restaurant::listaPreparate = nullptr;
int Restaurant::nrPreparate = 0;
//Comanda** Restaurant::listaComenzi = nullptr;
//int Restaurant::nrComenzi = 0;

int main()
{
    Restaurant meniu;
    //Ingrediente
    Ingredient aluat("Aluat"); Stoc2 stocAluat(1100);
    Ingredient pepperoni("Pepperoni"); Stoc2 stocPepperoni(350);
    Ingredient jalapeno("Jalapeno"); Stoc2 stocJalapeno(130);
    Ingredient sosRosii("Sos de rosii"); Stoc2 stocSosRosii(375);
    Ingredient mozarella("Mozarella"); Stoc2 stocMozarella(275);
    Ingredient prosciutto("Prosciutto"); Stoc2 stocProsciutto(300);
    Ingredient parmezan("Parmezan"); Stoc2 stocParmezan(270);
    Ingredient pui("Piept de pui"); Stoc2 stocPui(1000);
    Ingredient sosTeriyaki("Sos Teriyaki"); Stoc2 stocTeriyaki(150);
    Ingredient usturoi("Usturoi"); Stoc2 stocUsturoi(200);
    Ingredient vita("Carne vita"); Stoc2 stocVita(1000);
    Ingredient cartofi("Cartofi"); Stoc2 stocCartofi(500);
    Ingredient sosDulceAcrisor("Sos dulce acrisor"); Stoc2 stocSosDulceAcrisor(140);
    //chifla, carne vita, rosii, salata, sos burger
    Ingredient chifla("Chifla"); Stoc2 stocChifla(400);
    Ingredient rosii("Rosii"); Stoc2 stocRosii(350);
    Ingredient salata("Salata"); Stoc2 stocSalata(350);
    Ingredient sosBurger("Sos burger"); Stoc2 stocSosBurger(200);
    //penne, bacon, ou, parmezan
    Ingredient penne("Penne"); Stoc2 stocPenne(500);
    Ingredient bacon("Bacon"); Stoc2 stocBacon(250);
    Ingredient oua("Oua"); Stoc2 stocOua(200);
    Ingredient sosAlfredo("Sos Alfredo"); Stoc2 stocSosAlfredo(200);
    Ingredient brocolli("Brocolli"); Stoc2 stocBrocolli(350);
    //clatite, caramel,migdale
    Ingredient clatite("Clatite"); Stoc2 stocClatite(400);
    Ingredient caramel("Caramel"); Stoc2 stocCaramel(200);
    Ingredient migdale("Migdale"); Stoc2 stocMigdale(300);

    Ingredient mere("Mere"); Stoc2 stocMere(200);
    Ingredient scortisoara("Scortisoara"); Stoc2 stocScortisoara(100);

    meniu.adaugaIngredientRestaurant(&aluat, &stocAluat);
    meniu.adaugaIngredientRestaurant(&pepperoni, &stocPepperoni);
    meniu.adaugaIngredientRestaurant(&jalapeno, &stocJalapeno);
    meniu.adaugaIngredientRestaurant(&sosRosii, &stocSosRosii);
    meniu.adaugaIngredientRestaurant(&mozarella, &stocMozarella);
    meniu.adaugaIngredientRestaurant(&prosciutto, &stocProsciutto);
    meniu.adaugaIngredientRestaurant(&parmezan, &stocParmezan);
    meniu.adaugaIngredientRestaurant(&pui, &stocPui);
    meniu.adaugaIngredientRestaurant(&sosTeriyaki, &stocTeriyaki);
    meniu.adaugaIngredientRestaurant(&usturoi, &stocUsturoi);
    meniu.adaugaIngredientRestaurant(&vita, &stocVita);
    meniu.adaugaIngredientRestaurant(&cartofi, &stocCartofi);
    meniu.adaugaIngredientRestaurant(&sosDulceAcrisor, &stocSosDulceAcrisor);
    meniu.adaugaIngredientRestaurant(&chifla, &stocChifla);
    meniu.adaugaIngredientRestaurant(&rosii, &stocRosii);
    meniu.adaugaIngredientRestaurant(&salata, &stocSalata);
    meniu.adaugaIngredientRestaurant(&sosBurger, &stocSosBurger);
    meniu.adaugaIngredientRestaurant(&penne, &stocPenne);
    meniu.adaugaIngredientRestaurant(&bacon, &stocBacon);
    meniu.adaugaIngredientRestaurant(&oua, &stocOua);
    meniu.adaugaIngredientRestaurant(&sosAlfredo, &stocSosAlfredo);
    meniu.adaugaIngredientRestaurant(&brocolli, &stocBrocolli);
    meniu.adaugaIngredientRestaurant(&clatite, &stocClatite);
    meniu.adaugaIngredientRestaurant(&caramel, &stocCaramel);
    meniu.adaugaIngredientRestaurant(&migdale, &stocMigdale);
    meniu.adaugaIngredientRestaurant(&mere, &stocMere);
    meniu.adaugaIngredientRestaurant(&scortisoara, &stocScortisoara);

    //Retete
    Ingredient* listaIngredPizzaDiavola[] = { &aluat,&pepperoni,&jalapeno,&sosRosii,&mozarella };
    float cantitatiNecesarePizzaDiavola[] = { 200,40,20,100,60 };
    Reteta retetaPizzaDiavola(5, listaIngredPizzaDiavola, cantitatiNecesarePizzaDiavola, 25);

    Ingredient* listaIngredMargherita[] = { &aluat, &sosRosii,&mozarella };
    float cantitatiNecesareMargherita[] = { 200, 100, 60 };
    Reteta retetaMargherita(3, listaIngredMargherita, cantitatiNecesareMargherita, 20);

    Ingredient* listaIngredProsciutto[] = { &aluat, &sosRosii,&prosciutto,&parmezan };
    float cantitatiNecesareProsciutto[] = { 200,100,70,50 };
    Reteta retetaProsciutto(4, listaIngredProsciutto, cantitatiNecesareProsciutto, 25);

    Ingredient* listaIngredPuiTeriyaki[] = { &pui,&sosTeriyaki,&usturoi };
    float cantitatiNecesarePuiTeriyaki[] = { 150,50,15 };
    Reteta retetaPuiTeriyaki(3, listaIngredPuiTeriyaki, cantitatiNecesarePuiTeriyaki, 23);

    Ingredient* listaIngredVitaCartofi[] = { &vita,&cartofi,&sosDulceAcrisor };
    float cantitatiNecesareVitaCartofi[] = { 200,120,40 };
    Reteta retetaVitaCartofi(3, listaIngredVitaCartofi, cantitatiNecesareVitaCartofi, 30);

    Ingredient* listaIngredBurgerVita[] = { &vita,&chifla,&rosii,&salata,&sosBurger,&cartofi };
    float cantitatiNecesareBurgerVita[] = { 100,70,20,20,15,100 };
    Reteta retetaBurgerVita(6, listaIngredBurgerVita, cantitatiNecesareBurgerVita, 30);

    Ingredient* listaIngredBurgerPui[] = { &pui,&chifla,&salata,&sosBurger,&cartofi };
    float cantitatiNecesareBurgerPui[] = { 100,70,20,15,100 };
    Reteta retetaBurgerPui(5, listaIngredBurgerPui, cantitatiNecesareBurgerPui, 27);
    //penne,bacon,oua,parmezan
    Ingredient* listaIngredPenneCarbonara[] = { &penne,&bacon,&oua,&parmezan };
    float cantitatiNecesarePenneCarbonara[] = { 200,60,50,10 };
    Reteta retetaPenneCarbonara(4, listaIngredPenneCarbonara, cantitatiNecesarePenneCarbonara, 20);
    //penne, sos alfredo, broccoli, parmezan
    Ingredient* listaIngredPenneAlfredo[] = { &penne,&sosAlfredo,&brocolli,&parmezan };
    float cantitatiNecesarePenneAlfredo[] = { 200,50,100,10 };
    Reteta retetaPenneAlfredo(4, listaIngredPenneAlfredo, cantitatiNecesarePenneAlfredo, 20);

    Ingredient* listaIngredientePlacintaMere[] = { &mere,&scortisoara,&aluat };
    float cantitatiNecesarePlacintaMere[] = { 100,20,250 };
    Reteta retetaPlacintaMere(3, listaIngredientePlacintaMere, cantitatiNecesarePlacintaMere, 15);

    Ingredient* listaIngredClatite[] = { &clatite,&caramel,&migdale };
    float cantitatiNecesareClatite[] = { 200,50,50 };
    Reteta retetaClatite(3, listaIngredClatite, cantitatiNecesareClatite, 15);
    //Preparate

    //pizza diavola--aluat,jalapeno,pepperoni,sosRosii,mozarella
    Preparat pizzaDiavola("Pizza Diavola", 420, 35, retetaPizzaDiavola);
    meniu.adaugaPreparatRestaurant(&pizzaDiavola, &retetaPizzaDiavola);
    //pizza margherita--aluat, sos rosii, mozarella
    Preparat pizzaMargherita("Pizza Margherita", 360, 28, retetaMargherita);
    meniu.adaugaPreparatRestaurant(&pizzaMargherita, &retetaMargherita);
    //pizza prosciutto--aluat, sos rosii,prosciutto,parmezan 
    Preparat pizzaProsciutto("Pizza Prosciutto", 420, 35, retetaProsciutto);
    meniu.adaugaPreparatRestaurant(&pizzaProsciutto, &retetaProsciutto);
    //pui teriyaki--piept de pui, sos teriyaki, usturoi
    Preparat puiTeriyaki("Pui Teriyaki", 215, 32, retetaPuiTeriyaki);
    meniu.adaugaPreparatRestaurant(&puiTeriyaki, &retetaPuiTeriyaki);
    //vita cu piure de cartofi--carne vita, cartofi, sos dulce acrisor
    Preparat vitaCartofi("Carne de vita si cartofi", 360, 45, retetaVitaCartofi);
    meniu.adaugaPreparatRestaurant(&vitaCartofi, &retetaVitaCartofi);
    //burger vita cu cartofi--chifla,carne vita,rosii,salata, sos burger, cartofi
    Preparat burgerVita("Burger vita cu cartofi", 325, 37, retetaBurgerVita);
    meniu.adaugaPreparatRestaurant(&burgerVita, &retetaBurgerVita);
    //burger de pui cu cartofi--chifla, carne pui, salata, sos burger
    Preparat burgerPui("Burger pui cu cartofi", 305, 32, retetaBurgerPui);
    meniu.adaugaPreparatRestaurant(&burgerPui, &retetaBurgerPui);
    //penne carbonara--penne, bacon, ou,parmezan
    Preparat penneCarbonara("Penne Carbonara", 320, 27, retetaPenneCarbonara);
    meniu.adaugaPreparatRestaurant(&penneCarbonara, &retetaPenneCarbonara);
    //penne alfredo--penne, sos alfredo, broccoli,parmezan
    Preparat penneAlfredo("Penne Alfredo", 360, 27, retetaPenneAlfredo);
    meniu.adaugaPreparatRestaurant(&penneAlfredo, &retetaPenneAlfredo);
    //placinta mere--aluat,mere,scortisoara
    Preparat placintaMere("Placinta cu mere", 370, 24.99, retetaPlacintaMere);
    meniu.adaugaPreparatRestaurant(&placintaMere, &retetaPlacintaMere);
    //clatite cu caramel--clatite, caramel,migdale
    Preparat clatiteCuCaramel("Clatite cu caramel", 300, 20, retetaClatite);
    meniu.adaugaPreparatRestaurant(&clatiteCuCaramel, &retetaClatite);
    //meniu.afisareListaIngrediente();
    ////MENIU
    /*cout << "==============================================================================";
    cout << "\n****************************BINE ATI VENIT!****************************";
    cout << "\nPentru a consulta optiunile de preparate, tastati: Afiseaza meniu";
    cout << "\nPentru a comanda, tastati: Comanda noua";
    cout << "\nPentru meniul administratorului, tastati: 11032003";
    cout << "\nPentru a vedea ultimele comenzi date, tastati: Afiseaza istoric comenzi";
    cout << "\nPentru a parasi meniul, tastati: Iesire";*/
    cout << "\n==============================================================================";
    cout << "\n****************************BINE ATI VENIT!****************************";

    string optiune;
    do {
        cout << "\n\nPentru a consulta optiunile de preparate, tastati: Afiseaza meniu";
        cout << "\nPentru a comanda, tastati: Comanda noua";
        cout << "\nPentru meniul administratorului, tastati: 11032003";
        cout << "\nPentru a vedea ultimele comenzi date, tastati: Afiseaza istoric comenzi";
        cout << "\nPentru a consulta retetele, tastati: Afiseaza retete";
        cout << "\nPentru a parasi meniul, tastati: Iesire";

        cout << "\n\nIntroduceti optiunea dumneavoastra:";
        getline(cin, optiune);

        if (optiune == "Afiseaza meniu") {
            cout << "\n-----------------------------------------------------";
            meniu.afisareProduseMeniu();
        }
        else if (optiune == "Comanda noua") {
            cout << "\n----------------------------------------------------";
            meniu.adaugaProdusLaComanda();
        }
        else if (optiune == "11032003") {
            cout << "\nSe va intra in meniul administratorului.";
            string optiune2;
            do {
                cout << "\n\n----------------------------------------------------------------------------------";
                cout << "\nPentru a verifica ingredientele si stocurile lor tastati: Verifica depozit";
                cout << "\nPentru a creste stocul unui ingredient tastati: Creste stoc ingredient";
                cout << "\nPentru aprovizionare depozit tastati: Aprovizionare";
                cout << "\nPentru a parasi meniul administratorului tastati: Iesire la meniul principal";

                cout << "\n\nIntroduceti optiunea dumneavoastra:";
                getline(cin, optiune2);

                if (optiune2 == "Verifica depozit") {
                    //cout << "Se vor afisa toate ingredientele si stocurile existente.";
                    cout << "\n--------------------------------------------------------------------------------";
                    meniu.afisareListaIngrediente();
                }
                else if (optiune2 == "Creste stoc ingredient") {
                    //cout << "\nIntroduceti ID-ul ingredientului pentru care vreti sa faceti aprovizionarea:";
                    meniu.modificaStocIngredientDeLaTastatura();
                    //cin.ignore();
                }
                else if (optiune2 == "Aprovizionare") {
                    cout << "\nIntroduceti valoarea pentru aprovizionarea tuturor ingredientelor:";
                    float valoareAprovizionare;
                    cin >> valoareAprovizionare;
                    try {
                        meniu.cresteStocuri(valoareAprovizionare);
                        cout << "\nAprovizionarea a fost confirmata. Noile stocuri sunt:";
                        meniu.afisareListaIngrediente();
                    }
                    catch (exception ex)
                    {
                        cout << endl << ex.what();
                    }
                    cin.ignore();
                }

                else if (optiune2 == "Iesire la meniul principal")
                {
                    cout << "\nSe va reveni la meniul principal.";
                    break;
                }
                else {
                    cout << "\nOptiune invalida. Incercati din nou.";

                }
            } while (true);
        }
        else if (optiune == "Afiseaza istoric comenzi") {
            try {
                meniu.afisareIstoricComenzi();
            }
            catch (exception ex)
            {
                cout << endl << ex.what();
            }
            //merge si cand nu exista comenzi.
        }
        else if (optiune == "Afiseaza retete")
        {
            meniu.afisareRetete();
        }
        else if (optiune == "Iesire") {
            break;
        }
        else cout << "\nOptiune invalida.Va rugam incercati din nou.";
    } while (true);
    //meniul merge

    return 0;
}