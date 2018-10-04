#include <iostream>
#include <sstream>
using namespace std;

class Calculadora{
private:
    int battery{0}, maxBattery{5};
public:
    // Getters
    int getBattery(){ return this->battery; }
    int getMaxBattery(){ return this->maxBattery; }
    // Setters
    void setBattery(int battery){ this->battery = battery; }
    void setMaxBattery(int maxBattery){ this->maxBattery = maxBattery; }
    // Construtor
    Calculadora(int maxBattery = 0):
        battery(maxBattery),
        maxBattery(maxBattery)
    {}
    // Others Methods
    void gastarBateria(){
        if (getBattery() == 0)
            throw "fail: bateria descarregada";
        setBattery(getBattery()-1);
    }
    bool charge(int charge){
        if (charge >= 0 ){
            if (charge + getBattery() >= getMaxBattery())
                setBattery(getMaxBattery());
            else
                setBattery(getBattery() + charge);
            return true;
        }
        return false;
    }
    int soma(int a, int b){
        gastarBateria();
        return a+b;
    }
    int subtracao(int a, int b){
        gastarBateria();
        return a-b;
    }
    int multiplicacao(int a, int b){
        gastarBateria();
        return a*b;
    }
    float divisao(int a, int b){
        gastarBateria();
        if (b == 0)
            throw "fail: divisao por zero";
        return a/b;
    }
    string percent(){
        // float percent = (getBattery()*100)/getMaxBattery();
        return to_string(getBattery());
    }
};

class Controller{
public:
    Calculadora calculadora;

    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
           if (op == "new"){
                int maxBattery;
                in >> maxBattery;
                calculadora = Calculadora(maxBattery);
            } else if (op == "soma"){
                int a, b;
                in >> a >> b;
                out << calculadora.soma(a, b);
            } else if (op == "subtrair"){
                int a, b;
                in >> a >> b;
                out << calculadora.subtracao(a, b);
            } else if (op == "multiplica"){
                int a, b;
                in >> a >> b;
                out << calculadora.multiplicacao(a, b);
            } else if (op == "divisao"){
                int a, b;
                in >> a >> b;
                out << calculadora.divisao(a, b);
            } else if (op == "charge"){
                int a;
                in >> a;
                calculadora.charge(a);
            } else if (op == "show"){
                out << "~ [" << calculadora.percent() << "]";
            } else{
                out << "fail: comando invalido";
            }
            return out.str();
    }

    void exec(){
        string line;
        while (true){
            getline(cin, line);
            if (line == "end")
                return;
            try{
                cout << shell(line) << endl;
            } catch (const char * exception){
                cout << exception << endl;
            }
        }
    }
    
};

int main(){

    Controller c;
    c.exec();

    return 0;
}