/*
    TODO:
        ~ comparison between signed and unsigned integer expressions
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Cliente{

    // Atributos
    bool existe;
    string nome;
    string fone;

    // Métodos
    // Construtor
    Cliente(string nome = "fulano", string fone = "0000", bool existe = true){
        this->nome = nome;
        this->fone = fone;
        this->existe = existe;
    }

    // string toString(){
    //     stringstream ss;
    //     if (existe)
    //         ss << this->nome << ":" << this->fone;
    //     else
    //         ss << "-";
    //     return ss.str();
    // }

    void toString(){
        if (existe)
            cout << this->nome << ":" << this->fone;
        else
            cout << "-";
    }

};

struct Cinema{

    vector<vector<Cliente>> sala;

    // Atributos
    Cinema(int x = 0, int y = 0){
        for (int i=0; i<x; i++){
            vector<Cliente> fileira;
            for (int j=0; j<y; j++){
                fileira.push_back(Cliente("", "", false));
            }
            sala.push_back(fileira);
        }
    }

    void show(){
        // Como usar o stringstream aqui?
        for (int i=0; i<sala.size(); i++){
            cout << "   | ";
            for (int j=0; j<sala[i].size(); j++){
                sala[i][j].toString();
                cout << " ";
            }
            cout << "|";
            cout << endl;
        }
    }

    bool reservar(Cliente cliente, int x, int y){
        x--;
        y--;
        if (sala[x][y].nome == cliente.nome){
            cout << "   fail: " << cliente.nome << " ja esta na sala" << endl;
            return false;
        } else if ( (x<0 || x>=sala.size()) || (y<0 || y>=sala[0].size()) ){
            cout << "   fail: essa cadeira nao existe" << endl;
            return false;
        } else if (sala[x][y].nome == cliente.nome){
            cout << "   fail: essa cadeira esta ocupada" << endl;
            return false;
        } else{
            sala[x][y] = cliente;
            cout << "   done" << endl;
            return true;
        }
    }

    bool cancelar(Cliente cliente){
        for (int i=0; i<sala.size(); i++)
            for (int j=0; j<sala[0].size(); j++)
                if (sala[i][j].nome == cliente.nome){
                    sala[i][j] = Cliente("", "", false);
                    cout << "   done" << endl;
                    return true;
                }
        cout << "   fail: " << cliente.nome << " nao esta na sala" << endl;
        return false;
    }
};

int main(){

    int x, y;
    Cinema cinema;

    string op;
    while (true){
        cin >> op;
        if (op == "init"){
            cin >> x >> y;
            cinema = Cinema(x, y);
            cout << "   sala criada com " << (x*y) << " cadeiras" << endl;
        } else if (op == "show"){
            cinema.show();
        } else if (op == "reservar"){
            string nome, fone;
            cin  >> nome >> fone >> x >> y;
            cinema.reservar(Cliente(nome, fone), x, y);
        } else if (op == "cancelar"){
            string nome;
            cin >> nome;
            cinema.cancelar(Cliente(nome));
        } else {
            cout << "   fail: comando invalido" << endl;
        }
    }

    return 0;
}
