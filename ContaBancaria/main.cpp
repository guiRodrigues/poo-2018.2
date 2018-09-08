#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Operacao{

};

class Conta{
private:
    float saldo;
    int numero;
    vector<Operacao *> operacoes;
public:
    Conta(float saldo = 0, int numero = 0):
        saldo(saldo),
        numero(numero)
    {}

    string toString(){
        stringstream flow;
        flow << "conta: " << numero << "saldo: " << saldo << endl;
        return flow.str();
    }
};

class CaixaEletronico{
    public:
    Operacao operacao;

    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "test")
            out << "FUNCIONA!!" << endl;
        return out.str();
    }

    void exe(){
        string line;
        while (true){
            getline(cin, line);
            if (line == "end")
                return;
            cout << line << endl;
            cout << shell(line) << endl;
        }
    }

};

int main(){

    CaixaEletronico caixa;
    caixa.exe();

    return 0;
}