#ifndef _COLORS_

#define _COLORS_


/* FOREGROUND */

#define RST  "\x1B[0m"

#define KRED  "\x1B[31m"

#define KGRN  "\x1B[32m"

#define KYEL  "\x1B[33m"

#define KBLU  "\x1B[34m"

#define KMAG  "\x1B[35m"

#define KCYN  "\x1B[36m"

#define KWHT  "\x1B[37m"


#define FRED(x) KRED x RST

#define FGRN(x) KGRN x RST

#define FYEL(x) KYEL x RST

#define FBLU(x) KBLU x RST

#define FMAG(x) KMAG x RST

#define FCYN(x) KCYN x RST

#define FWHT(x) KWHT x RST


#define BOLD(x) "\x1B[1m" x RST

#define UNDL(x) "\x1B[4m" x RST


#endif  /* _COLORS_ */




#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

enum Creditar{ deposito, estorno };
enum Debitar{ saque, tarifa };

class Operacao{
private:
    string descricao;
    float valor{0}, saldo{0};

public:
    
    // Getters
    string getDescricao(){ return this->descricao; }
    float getValor(){ return this->valor; }
    float getSaldo(){ return this->saldo; }
    
    // Setters
    void setDescricao(string descricao){ this->descricao = descricao; }
    void setValor(float valor){ this->valor = valor; }
    void setSaldo(float saldo){ this->saldo = saldo; }
    
    // Construtor
    Operacao(string descricao = "", float valor = 0, float saldo = 0):
        descricao(descricao),
        valor(valor),
        saldo(saldo)
    {
        // Poderia usar os métodos modificadores(setters)
    }
};

class Conta{
private:
    int numero{0};
    float saldo{0};
    vector<Operacao> operacoes;
public:
    
    // Getter
    int getNumero(){ return this->numero; }
    float getSaldo(){ return this->saldo; }
    
    // Setter
    void setNumero(int numero){ this->numero = numero; }
    void setSaldo(float saldo){ this->saldo = saldo; }
    
    // Construtor
    Conta(int numero = 0):
        numero(numero)
    {
        // Poderia usar o setNumero(numero)
        pushOperation("abertura", 0, getSaldo());
    }

    // Outros métodos
    void pushOperation(string descricao, float valor, float saldo){
        operacoes.push_back(Operacao(descricao, valor, saldo));
    }
    string toString(){
        stringstream flow;
        flow << "conta:" << this->getNumero() << " saldo: " << this->getSaldo();
        return flow.str();
    }
    string extrato(size_t num = 0){
        stringstream flow;
        int index = (num > 0 && num < operacoes.size()) ? operacoes.size()-num : 0;
        for (size_t i = index; i<operacoes.size(); i++){
            flow << i 
            << ": " << setw(10) << operacoes[i].getDescricao()
            << ": " << setw(5) << operacoes[i].getValor() 
            << ": " << setw(5) << operacoes[i].getSaldo() 
            << endl;
        }
        return flow.str();
    }
    bool creditar(int op, float valor){
        switch (op){
            case 0: // deposito
                if (valor > 0){
                    setSaldo(getSaldo() + valor);
                    pushOperation("deposito", valor, getSaldo());
                    return true;
                }
            case 1: // estorno
                if (valor > 0){
                    setSaldo(getSaldo() + valor);
                    pushOperation("estorno", valor, getSaldo());
                    return true;
                }
            default:
                return false;
        }
    }
    bool debitar(int op, float valor){
        switch (op){
            case 0: // saque
                if (getSaldo() >= valor){
                    setSaldo(getSaldo() - valor);
                    pushOperation("saque", valor*(-1), getSaldo());
                    return true;
                }
            case 1: // tarifa
                if (getSaldo() >= valor){
                    setSaldo(getSaldo() - valor);
                    pushOperation("tarifa", valor*(-1), getSaldo());
                    return true;
                }
            default:
                return false;
        }
    }
    void extornar(string line){
        stringstream flow(line), out;
        unsigned int index;
        while (flow >> index){
            flow >> index;
            if (index<0 || index>=operacoes.size())
                out << FRED("failure: indice invalido");
            else if (operacoes[index].getDescricao() != "tarifa")
                out << FRED("failure: indice nao e tarifa");
            else{
                float valor = operacoes[index].getValor() * (-1);

            }
            // if (operacoes[index].getDescricao() == "tarifa")

        }
    }
};

class Controller{
public:
    Conta conta;

    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "init"){
            int numero;
            in >> numero;
            conta = Conta(numero);
            out << FGRN("success");
        }
        else if (op == "show"){
            out << conta.toString();
        }
        else if (op == "extrato"){
            int num = 0;
            if (in >> num){
                in >> num;
                out << conta.extrato(num);
            }
            else
                out << conta.extrato();
        }
        else if (op == "deposito"){
            float valor;
            in >> valor;
            // out << (conta.deposito(Creditar::deposito, valor)) ? "success" : "failure: valor invalido"; ~ second/third operand of conditional expression has no effect
            if (conta.creditar(Creditar::deposito, valor))
                out << FGRN("success");
            else
                out << FRED("failure: valor invalido");
        }
        else if (op == "saque" || op == "tarifa"){
            float valor;
            in >> valor;
            if (op == "saque")
            if (conta.debitar(Debitar::saque, valor))
                out << FGRN("success");
            else 
                out << FRED("failure: valor invalido");
        }
        return out.str();
    }

    void exec(){
        cout << endl;
        string line;
        while (true){
            getline(cin, line);
            if (line == "end")
                return;
            cout << "$ " << line << endl;
            cout << shell(line) << endl << endl;
        }
    }

};

int main(){

    Controller controller;
    controller.exec();

    return 0;
}