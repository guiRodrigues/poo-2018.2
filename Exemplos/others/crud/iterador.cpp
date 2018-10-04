#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){

    // Iterador = tem como acessar todos os elementos por ele
    // Ele sabe como acessar a próxima/anterior informação
    vector<int> vet = {7, 89, 2, 32, 42, 99, 546, 344, 2, 3};

    auto it = std::find(vet.begin(), vet.end(), 8);
    // vector<int>::iterator it = std::find(vet.begin(), vet.end(), 89);
    // Nome da estrutura, o que ela guarda, dps cria o iterador

    // Como saber se encontrou?
    if (it != vet.end()) // Quer dizer que encontrou
        cout << "Encontrou!!";
    else
        cout << "Não econtrou :(";
    cout << endl;
    *it = 98;
    it++;
    *it = 545;
    it -= 2;
    *it = 41;

    for (int i : vet)
        cout << i << " ";
    cout << endl;

    // Somar 1 a todos os elementos!
    for (auto it = vet.begin(); it != vet.end(); it++)
        // *it++; pq não funciona?
        *it += 1;
    for (int i : vet)
        cout << i << " ";

    return 0;
}