/*

TODO:
    ~ Implementar class, private e public

    ~ Falar para o David Sena passar iteradores
    ~ Aplicar as "visualizações": private & public
    ~ Retirar a "responsabilidade" do passageiro em saber se é preferencial
    ~ Substituir o size da topic pelo passengers.size()
    ~ #if 0 #endif
    ~ Para o @ e = usar operador ternário
    ~ Usar o operador ternário para a verificar se é ou não nullptr
    ~ Usar _news_ e _deletes_ no mesmo escopo da classe (boa prática)
    ~ Dar o new e o delte do passageiro no mesmo ecopo, como ele havia falado em sala. Quem der o new deve dar o delete
    ~ Usar uma outra função para buscar o passageiro no trem
    ~ Criar subfunções mais simples para modularizar o código
    ~ Dois passos para deletar: [ delete passenger[i]; ] e [ passenger[i] = nullptr; ] respectivamente
    ~ Elaborar o Controller
    ~ Criar o ônibus da UFC com a quantidade de pessoas que podem entrar infinita
    ~ !!LISTA DE INICIALIZAÇÃO
    ~ Lembrar de usar o _auto_
    ~ private, public e substituir struct por class
    ~ sombreamento entre variáveis
    ~ Fazer caso onde o numero de preferenciais é maior que o de cadeiras

    Contato(string id):
        id(id) <-- Posso passar os atributos aqui
    {}

*/

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

struct Topic{

    // Attributes
    vector<Person*> passengers;
    int pref;

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
            flow << ((person == nullptr) ? ((iterator<pref) ? " @" : " =") : person->toString());
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
        findPref();
        return -1;
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
        cout << "   fail : O veículo está lotado" << endl;
        return false;
    }

    bool out(string name = ""){
        int pos = find(name);
        if (pos == -1){
            cout << "HU3" << endl;
            return false;
        }
        delete passengers[pos];
        passengers[pos] = nullptr;
        return true;
    }

};

struct Controller{

    Topic topic;

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
            out << "    done" << endl;
        } else if (op == "show"){
            cout << topic.toString();
        }else if (op == "in"){
            string name;
            int age = 0;
            in >> name >> age;
            if (topic.in(name, age))
                out << "    done" << endl;
        } else if (op == "out"){
            string name;
            in >> name;
            if (topic.out(name))
                out << "    done" << endl;
        }
        return out.str();
    }

    void exec(){
        string line;
        while (true) {
            getline(cin, line);
            if (line == "end")
                break;
            cout << "   " << shell(line) << endl;
        }
    }

};

int main(){

    Controller controller;
    controller.exec();

    return 0;
}