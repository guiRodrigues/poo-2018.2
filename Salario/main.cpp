#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;



class Funcionario{
    string name, description;
    int diarias{0}, maxDiarias;
    float salario, bonus{0};
public:
    Funcionario(string name = "", string description = "", int maxDiarias = 0):
    name(name), description(description), maxDiarias(maxDiarias)
    {}

    // Getters
    string getName(){ return this->name; }
    string getDescription(){ return this->description; }
    float getSalario(){ return this->salario; }
    float getBonus(){ return this->bonus; }
    int getDiarias(){ return this->diarias; }
    int getMaxDiarias(){ return this->maxDiarias; }

    // Setters
    void setSalario(float salario){ this->salario = salario + this->bonus; }
    void setDiarias(int diarias){ this->diarias = diarias; }
    void setBonus(float bonus){ this->bonus = bonus; }

    // Others Methods
    virtual string toString() = 0; // Método abstrato
};

// enum sal {A = 3000, B = 5000, C = 7000, D = 9000, E = 11000};

class Professor : public Funcionario{
    char classe;
public:
    Professor(string name = "", char classe = '*'):
    Funcionario(name, "Prof", 2), classe(classe)
    {
        // Idiotice?
        int sal = 0;
        switch(classe){
            case 'A':
                sal = 3000; break;
            case 'B':
                sal = 5000; break;
            case 'C':
                sal = 7000; break;
            case 'D':
                sal = 9000; break;
            case 'E':
                sal = 11000; break;
        }
        Funcionario::setSalario(sal);
    }
    
    virtual string toString(){
        return Funcionario::getDescription() + " " + Funcionario::getName() + ", classe: " + classe + "\nsalario: R$" + to_string(Funcionario::getSalario());
    }
};

class Servidor : public Funcionario{
    int level;
public:
    Servidor(string name = "", int level = 0):
    Funcionario(name, "Sta", 1), level(level)
    {
        Funcionario::setSalario(3000 + 300*level);
    }

    virtual string toString(){
        return Funcionario::getDescription() + " " + Funcionario::getName() + " nivel " + to_string(level) + "\nsalário: R$" + to_string(Funcionario::getSalario());
    }
};

class Terceirzado : public Funcionario{
    int hours;
    string insalubre;
public:
    Terceirzado(string name = "", int hours = 0, string insalubre = ""):
    Funcionario(name, "Ter"), hours(hours), insalubre(insalubre)
    {
        float sal = (insalubre == "sim") ? (4 * hours) : (4 * hours + 500);
        Funcionario::setSalario(sal);
    }

    virtual string toString(){
        string ambiente = (insalubre == "sim") ? "não insalubre" : "insalubre";
        return Funcionario::getDescription() + " " + Funcionario::getName() + " " + to_string(hours) + "hrs, " + ambiente + "\nsalario R$" + to_string(Funcionario::getSalario());
    }
};

struct Repositorio{
    map<string, Funcionario*> repositorio;

    // isso vai percorrer apenas uma vez?
    void add(string key, Funcionario* fun){
        // auto iterador = it(key);

        auto it = repositorio.find(key);
        if (it != repositorio.end())
            throw "Fail: A chave \"" + key + "\" já está cadastrada";
        repositorio[key] = fun;
    }

    // Como retornar o iterador?
    // map<string, Funcionario*>::iterator& it(string key){
    //     auto it = repositorio.find(key);
    //     if (it == repositorio.end())
    //         throw "FAIL"; // qual tipo de erro?
    //     return it;
    // }

    // Funcionario& get(string key){
    //     // Como retornar o usuário assim?
    //     // auto it = repositorio.find(key);
    //     // if (it == repositorio.end())
    //     //     throw "Fail: Chave \"" + key + "\" não encontrada";
        
    //     for (auto& fun : repositorio){
    //         if (fun.first == key)
    //             return fun;
    //     }
    // }

    string showFun(string key){
        auto it = repositorio.find(key);
        if (it == repositorio.end())
            throw "Fail: Funcionário \"" + key + "\" não encontrado";
        return it->second->toString();
    }

    string remove(string key){
        auto it = repositorio.find(key);
        if (it == repositorio.end())
            throw "Fail: Funcionário \"" + key + "\" não encontrado";
        string str = it->second->getDescription() + " " + it->second->getName() + " removido";
        repositorio.erase(key);
        return str;
    }

    void addDiaria(string key){
        auto it = repositorio.find(key);
        if (it == repositorio.end())
            throw "Fail: Funcionário \"" + key + "\" não encontrado";
        if (it->second->getDescription() == "Ter")
            throw (string) + "Ter nao pode receber diaria";
        if (it->second->getDiarias() == it->second->getMaxDiarias())
            throw (string) + "Fail: Limite de diarias atingido";
        it->second->setDiarias(it->second->getDiarias() + 1);
        it->second->setSalario(it->second->getSalario() + 100);
    }

    void bonus(float value){
        float individualValue = value/repositorio.size();
        cout << value << " - " << repositorio.size() << " - " << individualValue << endl;
        for (auto& fun : repositorio){
            cout << fun.second->getSalario() << " § " << fun.second->getBonus() << endl;
            fun.second->setSalario(fun.second->getSalario() - fun.second->getBonus());
        }
        for (auto& fun : repositorio){
            fun.second->setBonus(individualValue);
            fun.second->setSalario(fun.second->getSalario() + fun.second->getBonus());
            cout << fun.second->toString() << endl;
        }
    }
};

class Controller{
    Repositorio repositorio;
public:
    string frontEnd(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "addProf" || op == "addSta" || op == "addTer"){
            string name;
            in >> name;
            if (op == "addProf"){
                char classe;
                in >> classe;
                repositorio.add(name, new Professor(name, classe));
            } else if (op == "addSta"){
                int level;
                in >> level;
                repositorio.add(name, new Servidor(name, level));
            } else if (op == "addTer"){
                int hours;
                string insalubre;
                in >> hours >> insalubre;
                repositorio.add(name, new Terceirzado(name, hours, insalubre.substr(1)));
            }
        } 
        else if (op == "show"){
            string key;
            in >> key;
            out << repositorio.showFun(key);
        }
        else if (op == "rm"){
            string key;
            in >> key;
            out << repositorio.remove(key);
        }
        else if (op == "addDiaria"){
            string key;
            in >> key;
            repositorio.addDiaria(key);
        }
        else if (op == "setBonus"){
            float value;
            in >> value;
            repositorio.bonus(value);
        }
        return out.str();
    }

    void backEnd(){
        string line;
        while (true){
            cout << endl;
            getline(cin, line);
            if (line == "end")
                return;
            cout << "$" << line << endl;
            try{
                cout << frontEnd(line) << endl;
            } catch (string e){
                cout << e << endl;
            }
        }
    }

};

int main(){

    Controller controller;
    controller.backEnd();

    return 0;
}