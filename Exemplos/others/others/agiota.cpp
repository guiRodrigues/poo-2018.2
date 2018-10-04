#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Cliente{
private:
    // Atributos
    string clienteId, nome;
    bool vivo;
public:
    // Getters
    string getClienteId(){ return this->clienteId; }
    string getNome(){ return this->nome; }
    bool isVivo(){ return this->vivo; }
    // Setters
    void setVivo(bool vivo){ this->vivo = vivo; }
    // Construtor
    Cliente(string clienteId = "", string nome = ""):
    clienteId(clienteId),
    nome(nome),
    vivo(true)
    {}
    // Outras funções
    string toString(){
        stringstream flow;
        flow << "👉  " << getClienteId() << ":" << getNome();
        return flow.str();
    }
};

class Sistema{
private:
    int quantia;
    vector<Cliente> clientes;
public:
    // Getters
    int getQuantia(){ return this->quantia; }
    // Setters
    void setQuantia(int quantia){ this->quantia = quantia; }
    // Construtor
    Sistema(int quantia = 0):
        quantia(quantia)
    {}
    // Outras funções
    void add(string clienteId = "", string nome = ""){
        for (Cliente c : clientes){
            if (c.getClienteId() == clienteId)
                throw "fail: cliente " + c.getClienteId() + " maria ja existe";
        }
        clientes.push_back(Cliente(clienteId, nome));
    }
    string showCliente(){
        stringstream flow;
        for (Cliente c : clientes)
            flow << c.toString() << endl;
        return flow.str();
    }

};

class Controller{

    Sistema sistema;

public:
    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "init"){
            int quantia;
            in >> quantia;
            sistema = Sistema(quantia);
        }
        else if (op == "add"){
            string opr, clienteID, nome, aux;
            if (in >> opr){
                if (opr == "cli"){
                    if (in >> clienteID){
                        getline(in, nome);
                        sistema.add(clienteID, nome);
                    } 
                } 
                // else if (opr == "tr")
                else throw "fail: parametro invalido";    
            }
            else throw "fail: ausencia de parametros";
        }
        else if (op == "show"){
            string opr;
            in >> opr;
            if (opr == "cli")
                cout << sistema.showCliente() << endl;
            else if (opr == "tr")
                throw "ainda nao implementado";
            else throw "fail: estrutura do comando SHOW invalida";
        }
        return out.str();
    }

    void exec(){
        cout << endl;
        string line;
        while(true){
            getline(cin, line);
            if (line == "end")
                return;
            cout << line << endl;
            try{
                cout << shell(line) << endl << endl;
            } catch (const char * exception){
                cout << exception << endl;
            }
        }
    }

};

int main(){

    Controller controller;
    controller.exec();

    return 0;
}