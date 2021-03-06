/*

    X TODO: criar o help
    X TODO: criar o init para ser sobrescrito

*/


#include <iostream>
#include <vector>
using namespace std;

struct Cliente{

    // Atributos
    string nome;
    string fone;

    // Métodos

    // Construtor
    Cliente(string nome = "", string fone = ""){
        this->nome = nome;
        this->fone = fone;
    }

};

struct Sala{

    // Atributos
    vector<Cliente*> cadeiras;

    // Métodos

    // Construtor
    Sala(int tamanho){
        for (int i=0; i<tamanho; i++)
            cadeiras.push_back(nullptr);
    }

    void show(){
        cout << "   [ ";
        for (Cliente *c : cadeiras){
            if (c != nullptr)
                cout << c->nome << ":" << c->fone << " ";
            else
                cout << "- ";
        }
        cout << "]" << endl;
    }

    bool reservar(Cliente *cliente, int id){

        bool exist;
        int tam = cadeiras.size();
        for (Cliente *c : cadeiras){
            if (c->nome == cliente->nome)
                exist = true;
        }

        // Se ele está no cinema
        if (exist){
            cout << "   fail: " << cliente->nome << " ja esta no cinema" << endl;
            return false;
        }
        // Se a cadeira está ocupada

        // else if (cadeiras.at(id).existe == true){
        else if (cadeiras[id] != nullptr){
            cout << "   fail: cadeira ja esta ocupada" << endl;
            return false;
        }
        // Se o ID for invalido
        else if ((id < 0) || (id>=tam)){
            cout << "   fail: id invalido" << endl;
            return false;
        }
        else {
            cadeiras.at(id) = cliente;
            cout << "   done";
            return true;
        }

        // else {
        //     Cliente *c(cliente->nome, cliente->fone);
        //     cadeiras.at(id) = c;
        // }
        // // Se der certo
        // else if (cadeiras.at(id).existe == false){
        //     Cliente c(nome, fone);

        //     cout << "   done" << endl;
        //     return true;
        // }
        return false;
    }

    bool cancelar(string nome){
        int tam = cadeiras.size();
        // for (int i=0; i< (int) cadeiras.size(); i++){
        for (int i=0; i<tam; i++){
            if (cadeiras.at(i)->nome == nome){
                cadeiras.at(i) = nullptr;
                return true;
                cout << "   done" << endl;
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
            cinema = Sala(tamanho);
            cout << "   done" << endl;
        }
        else if (op == "show"){
            cinema.show();
        }
        else if (op == "reservar"){
            string nome, fone;
            int id;
            cin >> nome >> fone >> id;
            cinema.reservar(new Cliente(nome, fone), id);
        }
        else if (op == "cancelar"){
            string nome;
            cin >> nome;
            cinema.cancelar(nome);
        }
        else {
            string invalido;
            getline(cin, invalido);
            cout << "   fail: comando invalido" << endl;
        }
    }

    return 0;
}
