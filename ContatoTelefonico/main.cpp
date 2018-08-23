#include <iostream>
#include <vector>
using namespace std;

struct Contato{
    // Atributos
    string nome;
    vector<Telefone> fones;

    Contato(string nome = ""){
        this->nome = nome;
    }
};

struct Telefone{
    // Atributos
    string operadora;
    string fone;

    Telefone(string operadora, string fone){
        this->operadora = operadora;
        this->fone = fone;
    }
};

struct Celular{

    // Atributos
    vector<Contato> lista;

    void init(string nome){
        lista.push_back(Contato(nome));
    }

    void show(){
        for (Contato c : lista){
            cout << c.nome << " ";
            for (Telefone f : c.fones)
                cout << "[" << f.operadora << ":" << f.operadora << "]" << endl;
        }
    }

    bool addFone(string nome, string oper, string fone){
        for (Contato c : lista)
            if (c.nome == nome){
                c.fones.push_back(Telefone(nome, fone));
                return true;
            }
        cout << "   fail: fone " << oper << " ja existe para " << nome << endl;
        return false;
    }

    bool deleteFone(string nome, string operadora){
        for (Contato c : lista)
            for (Telefone f : c.fones)
                if (operadora == f.operadora){
                    cout << "   done" << endl;
                    return true;
                }
        cout << "   fail: fone " << operadora << " nao existe" << endl;
        return false;
    }
};

int main(){

    string op;
    Celular phone;

    while (true){
        cin >> op;
        if (op == "init"){
            string nome;
            phone.init(nome);
        } else if (op == "show"){
            phone.show();
        } else if (op == "addFone"){
            string nome, operadora, fone;
            phone.addFone(nome, operadora, fone);
        } else if (op == "deleteFone"){
            string nome, operadora;
            phone.deleteFone(nome, operadora);
        }
    }

    return 0;
}