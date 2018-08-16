#include <iostream>
// Usado para "arredondar para cima" o valor do tanque de combustivel
#include <cmath> 
using namespace std;

struct Carro{

    //  Atributos
    float combustivel, km, limCombustivel;
    int passageiros, limPessoas;

    // Métodos

    // Construtor
    Carro(){
        combustivel = 0;
        km = 0;
        limCombustivel = 10;
        passageiros = 0;
        limPessoas = 2;
    }

    void show(){
        cout << "   pass: " << passageiros << ", gas: " << combustivel << ", km: " << km << endl;
    }

    bool in(){
        if (passageiros < limPessoas){
            passageiros++;
            cout << "   done" << endl;
            return true;
        }
        cout << "   O carro esta lotado" << endl;
        return false;
    }

    bool out(){
        if (passageiros > 0){
            passageiros--;
            cout << "   done" << endl;
            return true;
        }
        cout << "   O carro ja esta vazio" << endl;
        return false;
    }

    void fuel(float gasolina){
        combustivel+=gasolina;
        if (combustivel > limCombustivel)
            combustivel = limCombustivel;
        cout << "   done" << endl;
    }

    bool drive(float distancia){
        bool c1 = passageiros>0, c2 = combustivel>0, c3 = distancia<=combustivel*10;
        if ( c1 && c2 && c3 ){
            km += distancia;
            combustivel -= distancia/10;
            // Caso seja nescessario que o combustível seja medido de forma inteira
            // combustivel -= ceil(distancia/10);
            cout << "   done" << endl;
            return true;
        }
        if (!c1)
            cout << "   fail: nao ha ninguem no carro" << endl;
        else if (!c2 || !c3)
            cout << "   fail: gasolina insuficiente" << endl;
        return false;
    }

};

int main(){

    Carro carro;
    string op;

    while (true){
        cin >> op;
        if (op == "help")
            cout << "show; in; out; fuel _combustivel; drive _distancia" << endl;
        else if (op == "show")
            carro.show();
        else if (op == "in")
            carro.in();
        else if (op == "out")
            carro.out();
        else if (op == "fuel"){
            float gasolina;
            cin >> gasolina;
            carro.fuel(gasolina);
        }
        else if (op == "drive"){
            float distancia;
            cin >> distancia;
            carro.drive(distancia);
        }
    }

    return 0;
}