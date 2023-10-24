#include <iostream>
#include <string>
#include <utility>
struct Osoba
{
    unsigned int wiek;
    std::string imie;
    Osoba()
    {
        wiek = 1;
        imie = "as";
    }
    Osoba(unsigned int age , std::string name)
    {
        wiek = age;
        imie = std::move(name);
    }

    void updateData(const Osoba& objInp)
    {
        wiek = objInp.wiek;
        imie = std::move(objInp.imie);
    }
    Osoba& operator ()( Osoba* objInp)
    {
        if(&objInp != nullptr)
        {
            updateData(*objInp);
        }
        return  *this;
    }




};






template<typename Data_type>
class Dynamic_Array
{
public:
    Data_type* array;
    unsigned int currentSize;
    unsigned int maxSize;
    float growthRate;
    Dynamic_Array():currentSize(0),maxSize(1),growthRate(2.0)
    {
        array = new Data_type[maxSize];
    }
    explicit Dynamic_Array(unsigned int max):currentSize(0),maxSize(max),growthRate(2.0)
    {
        array = new Data_type[maxSize];
    }
    ~Dynamic_Array()
    {
        delete array[];
    }
    Dynamic_Array(const Dynamic_Array<Data_type> &otherDynamic )
    {
        maxSize = otherDynamic.maxSize;
        currentSize=otherDynamic.currentSize;
        growthRate=otherDynamic.growthRate;
        array = new Data_type[maxSize];
        for (unsigned int i = 0; i < currentSize; i++) {
            array[i] = otherDynamic.array[i];
        }
    }
    Dynamic_Array(const Dynamic_Array<Data_type> &otherDynamic, bool changeSize) {
        growthRate = otherDynamic.growthRate;
        if (changeSize) {
            maxSize = otherDynamic.maxSize * growthRate;
        } else {
            maxSize = otherDynamic.maxSize;
        }
        currentSize = otherDynamic.currentSize;
        array = new Data_type[maxSize];
        for (unsigned int i = 0; i < currentSize; i++) {
            array[i] = otherDynamic.array[i];
        }
    }


    void addObj(Data_type * obj) {
        if (currentSize == maxSize) {
            // Realokacja tablicy, jeśli osiągnięto maksymalny rozmiar
            maxSize *= growthRate;
            Data_type* newArray = new Data_type[maxSize];
            for (unsigned int i = 0; i < currentSize; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
        // Dodawanie nowego elementu do tablicy
        array[currentSize] = *obj;
        currentSize++;
    }
    Data_type getObj(unsigned int indeks)
    {
        if(indeks>currentSize)
        {
            std::cerr<<"\n'getObj("<<indeks<<") indeks wiekszy od tablicy!!\n";
            return nullptr;
        }
        return array[indeks];
    }
    bool editObjDate(Data_type inputData , unsigned int indeks)
    {
        Data_type editObj = getObj(indeks);
        if(getObj(indeks) == nullptr ) return false;
        else
        {
            (*editObj)(inputData);//PRZECIAZONY OPERATOR !!!!
            return true;
        }
    }
    bool clear() {
        while (currentSize > 0) {
            Data_type currentToDelete = array[currentSize - 1];
            delete currentToDelete;
            currentSize--;
        }
        maxSize = 1;
        return true;
    }
    void print()
    {
        std::cout<<"\n===================================================================================="
                   "\nAkt. Rozmiar: "<<currentSize<<
                   "\t|\tWsp. Powiekszenia: "<<growthRate<<
                   "\t|\tMaks. Rozmiar: "<<maxSize<<
                   "\n====================================================================================";
    }

};
bool printOne(Dynamic_Array<Osoba*>*lista ,unsigned int index)
{
    lista->print();
    if(index>lista->currentSize){return false;}
    Osoba *printObj = lista->getObj(index);
    std::cout <<std::endl<<"Index: "<<index<<"\t"<<"Imie: "<< printObj->imie<<"\t\t"
              <<"Wiek: "<<printObj->wiek << std::endl;  // Wyświetlenie pola Osoba
    return true;
}
bool printBetween(Dynamic_Array<Osoba*>*lista ,unsigned int indexStart,unsigned int indexEnd)
{
    lista->print();
    if(indexStart>lista->currentSize){return false;}
    else if(indexEnd>lista->currentSize){return false;}
    for(int i = indexStart ; i <= indexEnd ; i++) {
        Osoba *printObj = lista->getObj(i);
        std::cout << std::endl << "Index: " << i << "\t" << "Imie: " << printObj->imie << "\t\t"
                  << "Wiek: " << printObj->wiek ;  // Wyświetlenie pola Osoba
    }
    return true;
}
bool printAll(Dynamic_Array<Osoba*>*lista )
{
    lista->print();
    for(int i = 0 ; i < lista->currentSize ; i++) {
        Osoba *printObj = lista->getObj(i);
        std::cout << std::endl << "Index: " << i << "\t" << "Imie: " << printObj->imie << "\t\t"
                  << "Wiek: " << printObj->wiek ;  // Wyświetlenie pola Osoba
    }
    return true;
}
bool printShortFront(Dynamic_Array<Osoba*>*lista ,unsigned int count)
{
    lista->print();
    if(lista->currentSize <= count)
    {
        printAll(lista);
        return true;
    }
    std::cout<<"\n\n"<<count<<" Pierwszych Obiektow";
    for(int i = 0 ; i < count ; i++) {
        Osoba *printObj = lista->getObj(i);
        std::cout << std::endl << "Index: " << i << "\t" << "Imie: " << printObj->imie << "\t\t"
                  << "Wiek: " << printObj->wiek ;  // Wyświetlenie pola Osoba
    }
    return true;
}
bool printShortBack(Dynamic_Array<Osoba*>*lista ,unsigned int count)
{
    lista->print();
    if(lista->currentSize <= count)
    {
        printAll(lista);
        return true;
    }
    std::cout<<"\n\n"<<count<<" Ostatnich Obiektow";
    for(int i = count ; i > 0 ; i--) {
        Osoba *printObj = lista->getObj(i);
        std::cout << std::endl << "Index: " << i << "\t" << "Imie: " << printObj->imie << "\t\t"
                  << "Wiek: " << printObj->wiek ;  // Wyświetlenie pola Osoba
    }
    return true;
}

int main ()
{
    Osoba * obj = new Osoba(123,"jajkeczko");
    Osoba * obj1 = new Osoba(222,"kajkeczko");
    Osoba * obj2 = new Osoba(3,"jajo");
    Osoba * obj3 = new Osoba(123,"jajkeczko");
    Osoba * obj4 = new Osoba(222,"kajkeczko");
    Osoba * obj5 = new Osoba(3,"jajo");

    Dynamic_Array<Osoba*>*DynArray = new Dynamic_Array<Osoba*>();
    DynArray->addObj(&obj);
    DynArray->addObj(&obj1);
    DynArray->addObj(&obj2);
    DynArray->addObj(&obj3);
    DynArray->addObj(&obj4);
    DynArray->addObj(&obj5);
    printShortBack(DynArray,5);





    return 0;
}
