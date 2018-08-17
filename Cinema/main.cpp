/*

    X TODO: criar o help
    X TODO: criar o init para ser sobrescrito

*/


#include <iostream>
#include <vector>
using namespace std;

struct Cliente{

    // Atributos
    bool existe;
    string nome;
    string fone;

    // Métodos

    // Construtor
    Cliente(string nome = "cliente", string fone = "0000", bool existe = true){
        this->existe = existe;
        this->nome = nome;
        this->fone = fone;
    }

};

struct Sala{

    // Atributos
    vector<Cliente> cadeiras;

    // Métodos

    // Construtor
    Sala(int tamanho){
        init(tamanho);
    }

    void init(int tamanho){
        cadeiras.clear();
        for (int i=0; i<tamanho; i++)
            cadeiras.push_back(Cliente("", "", false));
    }

    void show(){
        cout << "   [ ";
        for (Cliente c : cadeiras){
            if (c.existe)
                cout << c.nome << ":" << c.fone << " ";
            else
                cout << "- ";
        }
        cout << "]" << endl;
    }

    bool reservar(string nome, string fone, int id){

        bool exist;
        for (Cliente c : cadeiras){
            if (c.nome == nome)
                exist = true;
        }

        if (exist){
            cout << "   fail: " << nome << " ja esta no cinema" << endl;
            return false;
        }
        if (cadeiras.at(id).existe == true){
            cout << "   fail: cadeira ja esta ocupada" << endl;
            return false;
        }
        else if (cadeiras.at(id).existe == false){
            Cliente c(nome, fone);
            cadeiras.at(id) = c;
            cout << "   done" << endl;
            return true;
        }
        return false;
    }

    bool cancelar(string nome){
        int tam = cadeiras.size();
        for (int i=0; i<tam; i++){
            if (cadeiras.at(i).nome == nome){
                cadeiras.at(i).existe = false;
                cadeiras.at(i).nome = "";
                cadeiras.at(i).fone = "";
                cout << "   done" << endl;
                return true;
            }
        }
        cout << "   fail: " << nome << " nao esta na sala" << endl;
        return false;
    }

};

int main(){

    Sala cinema(0);
    string op;

    while (true){
        cin >> op;
        if (op == "help"){
            cout << "   init _tamanho; show; reservar _nome _fone _cadeira; cancelar _nome" << endl;
        }
        else if (op == "init"){
            int tamanho;
            cin >> tamanho;
            cinema.init(tamanho);
            cout << "   done" << endl;
        }
        else if (op == "show"){
            cinema.show();
        }
        else if (op == "reservar"){
            string nome, fone;
            int id;
            cin >> nome >> fone >> id;
            cinema.reservar(nome, fone, id);
        }
        else if (op == "cancelar"){
            string nome;
            cin >> nome;
            cinema.cancelar(nome);
        }
    }

    return 0;
}
