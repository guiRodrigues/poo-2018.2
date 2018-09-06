#if 0

    TODO:
        ~ Aplicar ponteiros
        ~ Problemas com o unsigned int
        ~ 

#endif

#include <iostream>
#include <sstream>
#include <vector>
// #include <iomanip>
// #include <cctype>
using namespace std;

class Fone{
public:
    string operadora, numero;

    Fone(string operadora, string numero){
        this->operadora = operadora;
        this->numero = numero;
    }

    string toString(){
        stringstream flow;
        flow << operadora << ":" << numero;
        return flow.str();
    }
};

class Contato{
private:
    string nome;
    vector<Fone> lista;

public:
    Contato(string nome = "vazio"):
        nome(nome)
    {}

    // ~Contato(){
    //     for (Fone fone : lista)
    //         delete(fone);
    // }

    string toString(){
        stringstream flow;
        flow << nome << "=>";
        // for (Fone f : lista) ~ Como pegar o índice em um For Each?
        for (unsigned int i=0; i<lista.size(); i++)
            flow << " [" << i << ":" << lista[i].toString() << "]";
        return flow.str();
    }

    bool val(string s){
        for (int i=0; i<(int)s.size(); i++){
            if(!isdigit(s[i]) && s[i] != '(' && s[i] != ')')
                return false;
        }
        return true;
    }

    bool add(Fone fone){
        for (Fone f : lista)
            if (f.numero == fone.numero){
                cout << "   fail: ID's repitidos não são aceitos;" << endl;
                return false;
            }
        if (!val(fone.numero)){
            cout << "   fail: Fone inválido" << endl;
            return false;
        } else {
            lista.push_back(fone);
            return true;
        }
    }

    // bool rm(string numero){
    //     for (int i=0; i<(int)lista.size(); i++)
    //         if (lista[i].numero == numero){
    //             lista.erase(lista.begin() + i);
    //             return true;
    //         }
    //     return false;
    // }

    void rmL(string foneId){
        for(int i = 0; i < (int) lista.size(); i++)
            if(lista[i].operadora == foneId){
                lista.erase(lista.begin() + i);
            }
    }

    void rmI(int i){
        lista.erase(lista.begin() + i);
    }

    void update(string line){
        stringstream flow(line);
        string word;

        flow >> word;
        if (word == nome){
            lista.clear();
            while (flow >> word){
                stringstream ss(word);
                string operadora, numero;
                getline(ss, operadora, ':');
                getline(ss, numero);
                if (val(numero))
                    lista.push_back(Fone(operadora, numero));
                else{
                    cout << "   fail: o numero da " << operadora << " não é valido";
                }
            }
        } else{
            cout << "   fail: update invalido" << endl;
        }
    }

};

struct Controller{

    Contato contato;

    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "help")
            out << "SHOW!!!";
        else if (op == "init"){
            string nome = "";
            in >> nome;
            contato = Contato(nome);
            out << "   done" << endl;
        } else if (op == "show"){
            out << contato.toString() << endl;
        } else if (op == "add"){
            string nome, numero;
            in >> nome >> numero;
            contato.add(Fone(nome, numero));
        } else if (op == "rm"){
            string sop; // Second Operation
            in >> sop;
            if (sop == "-l"){ // i == indice
                string label;
                in >> label;
                contato.rmL(label);
            } else if (sop == "-i"){ // l == label
                int i;
                in >> i;
                contato.rmI(i);
            }
        } else if (op == "update"){
            string line;
            getline(in, line);
            contato.update(line);
        }
        return out.str();
    }

    void exe(){
        string line;
        while (true){
            getline(cin, line);
            if (line == "end")
                return;
            cout << line << endl;
            cout << "   " << shell(line) << endl;
        }
    }

};

int main(){

    Controller controller;
    controller.exe();

    return 0;
}
