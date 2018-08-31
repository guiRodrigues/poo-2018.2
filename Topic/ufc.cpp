#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Person{
    // Attributes
    string name;
    int age;

    // Methods
    // Constructor
    Person(string name = "", int age = 0){
        this->name = name;
        this->age = age;
    }

    string toString(){
        stringstream flow;
        flow << name << ":" << age;
        return flow.str();
    }

};

#if 0
    This is a comment
#endif

class Topic{
private:
    // Attributes
    vector<Person*> passengers;
    int pref;
public:
    // Methods
    // Constructor
    Topic(int size = 0, int pref = 0):
        passengers(size, nullptr),
        pref(pref)
    {}

    ~Topic(){
        for (Person * person : passengers)
            delete(person);
    }

    string toString(){
        stringstream flow;
        flow << "[";
        // Uso de um iterador para saber se a posição é referente a um ascento preferencial
        // Não consegui pegar um índice de person!
        int iterator = 0;
        for (Person * person : passengers){
            // flow << ((person == nullptr) ? ((iterator<pref) ? " @" : " =") : person->toString());
            flow << ((person != nullptr) ? ((iterator<pref) ? " @" + person->toString() : " =" + person->toString()) : ((iterator<pref) ? " @" : " ="));
            iterator++;
        }
        flow << " ]";
        return flow.str();
    }

    int find(string name = ""){ // Não está tão semântico
        // Pode ser usado o For Each, mas não consigo pegar o índice do "para cada"
        for (unsigned int i=0; i<passengers.size(); i++)
            if (passengers[i] != nullptr &&  passengers[i]->name == name)
                return i;
        return -1;
    }

    int findPref(){
        for (unsigned int i=0; i<passengers.size(); i++)
            if (passengers[i] == nullptr)
                return i;
        return -1;
    }

    int findCommon(){
        for (unsigned int i=pref; i<passengers.size(); i++)
            if (passengers[i] == nullptr)
                return i;
        return findPref();
    }

    bool in(string name = "", int age = 0){
        bool pref = (age > 60) ? true : false;
        if (find(name) != -1 && passengers[find(name)] == nullptr){
            cout << "   fail: " << name << " já está no veículo" << endl;
            return false;
        }
        else if (pref){
            if (findPref() != -1 && passengers[findPref()] == nullptr){
                passengers[findPref()] = new Person(name, age);
                return true;
            }
        }
        else if (!pref){
            if (findCommon() != -1 && passengers[findCommon()] == nullptr){
                passengers[findCommon()] = new Person(name, age);
                return true;
            }
        }
        passengers.push_back(new Person(name, age));
        return true;
    }

    bool out(string name = ""){
        int pos = find(name);
        if (pos == -1){
            cout << "   fail: " << name << " não pode sair pois não está no veículo!" << endl;
            return false;
        }
        delete passengers[pos];
        passengers[pos] = nullptr;
        return true;
    }

};

class Controller{
private:
    Topic topic;

public:
    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "help")
            out << "new _size _pref; " << endl;
        else if (op == "new"){
            int size = 0, pref = 0;
            in >> size >> pref; // PQ que quando uso o cin >>  fica em loop infinito?
            topic = Topic(size, pref);
            out << "   done" << endl;
        } else if (op == "show"){
            cout << topic.toString();
        }else if (op == "in"){
            string name;
            int age = 0;
            in >> name >> age;
            if (topic.in(name, age))
                out << "   done" << endl;
        } else if (op == "out"){
            string name;
            in >> name;
            if (topic.out(name))
                out << "   done" << endl;
        }
        return out.str();
    }

    void exec(){
        string line;
        while (true) {
            getline(cin, line);
            if (line == "end")
                break;
            // cout << line << endl; // Para quando usar um .txt como input, o comando reaparecer
            cout << "   " << shell(line) << endl;
        }
    }

};

int main(){

    Controller controller;
    controller.exec();

    return 0;
}