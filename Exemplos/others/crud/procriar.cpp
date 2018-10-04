#include <iostream>
#include <random>
using namespace std;

template <typename T>
T Procriate(T macho, T femea){
    if (macho.getSex() == 'M' && femea.getSex() == 'F')
        return macho.copular(femea);
    throw "FAIL: Órgão excretor não reproduz";
}

class Duck{
    char sex;
    string name;
    int age;
public:
    Duck(char sex = '*', string name = "", int age = 0):
        sex(sex), name(name), age(age)
    {}
    char getSex(){ return this->sex; }
    string getName(){ return this->name; }
    int getAge(){ return this->age; }
    Duck copular(Duck other){
        int i = rand() % 10 + 1;
        char s = (i % 2 == 0) ? 'M' : 'F';
        return Duck(s, "Filhote", 1);
    }
};

int main(){

    Duck femea('M', "Pata", 10);
    Duck macho('M', "Pato", 11);
    try{
        Duck filho = Procriate<Duck>(macho, femea);
        cout << filho.getName() << " " << filho.getSex() << " " << filho.getAge() << endl;
    } catch(const char * exception){
        cout << exception << endl;
    }
    

    return 0;
}