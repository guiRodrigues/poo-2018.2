#include <iostream>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

class Person{
    string name;
    int age;
public:
    // Constructor
    Person(string name = "", int age = 0):
    name(name), age(age)
    {}
    // Getters and Setters
    string getName(){ return this->name; }
    int getAge(){ return this->age; }
    // Others methods
    string toString(){
        return getName() + " " + to_string(getAge());
    }
};

#if 0

class Pet{
    string name, breed;
public:
    Pet(string name, string breed):
    name(name), breed(breed)
    {}
};

class Repository{
    bool add(Person person);
    Person& getPerson(string key);
    // Person * getPerson(string key);
    void remove();
    vector<Person> getAll();
};

# endif

int main(){

    // Estrutura chave - valor
    // Mapeamento de quem para quem?
    // Mapeamento de string para pessoa
    map<string, Person> repository;
    map<string, Person>::iterator it;
    repository["penguin"] = Person("Oswald Cobblepot", 40);
    repository["riddler"] = Person("Edward Nygma", 37);
    repository["two-face"] = Person("Harvey Dent", 35);
    // Inserir via chamada de função
    repository.insert(pair<string, Person>("scarecrow", Person("Jonathan Crane", 30)));
    // Ou emitir o tipo de mapeamento
    repository.insert(make_pair("mad_hatter", Person("Jervis Tech", 41)));

    # if 0
    // Acesso direto aos elementos da estrutura chave-valor (mapa)
    cout << "Penguin: ";
    cout << repository["penguin"].getName() << endl;
    cout << repository["penguin"].getAge() << endl;

    cout << "Riddler: ";
    cout << repository.at("riddler").getName() << endl;
    cout << repository.at("riddler").getAge() << endl;
    # endif

    // ????????????????????????????????????????????????????????????????????????????
    // find
    cout << repository.find("joker")->first << endl; // retorna algo como lixo
    cout << repository.find("penguin")->first << endl; // retorna penguin
    cout << repository.find("penguin")->second.toString() << endl << endl;
    // ????????????????????????????????????????????????????????????????????????????

    // Retornar todos os elementos do map
    // for (auto person : repository){
    for (pair<string, Person> villain : repository){
        cout << "Key: " << villain.first << ", Element: " << villain.second.toString() << endl;
    }

    // Removing element
    // by key
    repository.erase("mad_hatter");
    cout << endl;
    // by iterator
    it = repository.find("penguin");
    repository.erase(it);
    // until the end
    it = repository.find("scarecrow");
    repository.erase(it, repository.end());

    for (pair<string, Person> villain : repository){
        cout << "Key: " << villain.first << ", Element: " << villain.second.toString() << endl;
    }

    return 0;
}