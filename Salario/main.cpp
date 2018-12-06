#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

class Funcionario{
protected:
    string name;
    int diarias{0}, maxDiaria;
    float salario, bonus{0};
public:
    Funcionario(string name = ""):
        name(name)
    {}

    // Getters
    virtual string getName() = 0;
    virtual float getSalario() = 0;
    virtual float getBonus() = 0;
    virtual int getDiarias() = 0;
    virtual int getMaxDiariaa() = 0;

    virtual void calcSalario() = 0;

    // Setters
    // void setSalario(float salario){ this->salario = salario; }
    // void setDiarias(int diarias){ this->diarias = diarias; }
    void setBonus(float bonus){ this->bonus = bonus; }
    virtual void addDiaria(){this->diarias += 1;}

    // Others Methods
    virtual string toString() = 0; // Método abstrato
};

// enum sal {A = 3000, B = 5000, C = 7000, D = 9000, E = 11000};

class Professor : public Funcionario{
    string profissao{"Prof"};
    int maxDiaria {2};
    char classe;
public:
    Professor(string name = "", char classe = '*'):
        Funcionario(name), classe(classe)
    {}

    virtual string getName(){return name;} 
    virtual string getProfiss(){return profissao;}
    virtual int getDiaria(){return diarias;}
    virtual int getMaxDiaria(){return maxDiaria;}

    void calcSalario(){
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
        salario += 100 * diarias + bonus;
    }
    
    string toString(){
        return profissao + name + ", classe: " + classe + "\nsalario: R$" + to_string(salario);
    }
};

class Servidor : public Funcionario{
    string profissao {"Sta"};
    int maxDiaria{1}, level;
public:
    Servidor(string name = "", int level = 0):
        Funcionario(name), level(level)
    {}

    virtual string getName(){return name;} 
    virtual string getProfiss(){return profissao;}
    virtual int getDiaria(){return diarias;}
    virtual int getMaxDiaria(){return maxDiaria;}

    void calcSalario(){
        salario = 3000 + 300 * level + 100 * diarias + bonus;
    }

    virtual string toString(){
        return profissao + " " + name + " nivel " + to_string(level) + "\nsalário: R$" + to_string(salario);
    }
};

class Terceirzado : public Funcionario{
    int maxDiaria{-1}, hours; //?-1
    string profissao{"Ter"}, insalubre;
public:
    Terceirzado(string name = "", int hours = 0, string insalubre = ""):
    Funcionario(name), hours(hours), insalubre(insalubre)
    {}

    virtual string getName(){return name;} 
    virtual string getProfiss(){return profissao;}
    virtual int getDiaria(){return diarias;}
    virtual int getMaxDiaria(){return maxDiaria;}

    void calcSalario(){
        salario = (insalubre == "sim") ? (4 * hours + bonus) : (4 * hours + 500 + bonus);
    }

    virtual string toString(){
        string ambiente = (insalubre == "sim") ? "não insalubre" : "insalubre";
        return profissao + " " + name + " " + to_string(hours) + "hrs, " + ambiente + "\nsalario R$" + to_string(salario);
    }
};

template<typename T>
class Repositorio{
    map<string, T*> data;
public:
    bool exists(string k){
        return data.find(key) != data.end();
    }
    bool addUser(string k, T* v){
        if (!exists(k)){
            data[k] = v;
            return true;
        }
        else
            throw "fail: usuario ja cadastrado";
    }
    void rmUser(string k){
        auto user = getUser(k);
        data.erase(k);
        cout << "  " + user->getProfiss() + " " + user->getName() + " foi removido!";
        delete user;
    }
    T* getUser(string k){
        auto it = data.find(k);
        if (it != data.end())
            return it->second;
        throw "fail: funcionario " + k + " nao existe";
    }
    void refreshSalario(T* t){
        t->calcSalario();           
    }
    void addDiaria(string k){
        auto user = getUser(k);
        // Conversão de tipos
        if (dynamic_cast<Terceirizado*>(user)) // se eu conseguir converter ele para terceirizado?
            throw "fail: Ter nao pode receber diarias";
        else if (user->getMaxDiaria() >= user->getDiaria())
            user->addDiaria();
        else
            throw "fail: limite de diarias atingido";
    }
    void setBonus(int bonus){
        bonus = bonus / data.size();
        for(auto& pair : data){
            pair.second->setBonus(bonus);
        }
    }
    string toString(){
        stringstream ss;
        for(auto pair : data)
            ss << pair.second->toString()
               << endl << "  ";
        return ss.str();
    }
};

class Controller{
    Repositorio<Funcionario> repositorio;
public:
    string frontEnd(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        try {
            if(op == "addProf"){
                string name;
                char level;
                in >> name >> level;
                Professor* P = new Professor(name, level);
                if(!repositorio.addUser(name, P))
                    delete P;
                out << "done";
            }
            else if(op == "addSta"){
                string name;
                int level;
                in >> name >> level;
                Servidor* S = new Servidor(name, level);
                if(!repositorio.addUser(name, S))
                    delete S;
                out << "done";
            }
            else if(op == "addTer"){
                string name, salub;
                int hours_work;
                in >> name >> hours_work >> salub;
                Terceirzado* T = new Terceirizado(name, hours_work, salub);
                if(!repositorio.addUser(name, T))
                    delete T;
                out << "done";
            }
            else if(op == "rm"){
                string name;
                in >> name;
                repositorio.rmUser(name);
            }
            else if(op == "show"){
                if(in >> op){
                    Funcionario* f = repositorio.getUser(op);
                    repositorio.refreshSalario(f);
                    out << repositorio.getUser(op)->toString();
                } else
                    out << repositorio.toString();
            }
            else if(op == "addDiaria"){
                string name;
                in >> name;
                repositorio.addDiaria(name);
                out << "done";
            }
            else if(op == "setBonus"){
                int bonus;
                in >> bonus;
                repositorio.setBonus(bonus);
                out << "done";
            }
        }
        catch(const char* e){ out << e; }
        catch(string e){ out << e; }
        catch(...){out << "fail: ocorreu uma exceção";}

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