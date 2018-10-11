#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int comparaString(string one, string two){
    reverse(one.begin(), one.end());
    reverse(two.begin(), two.end());
    return one.back() > two.back();
}

#if 0
    "Iteradores te dão uma forma de caminhar pela estrutura sem que você precise 'saber' como ela se comporta/funciona"
#endif

int main(){

    vector<string> villains = {"penguin", "riddler", "Alfredz", "two-Face", "bane", "bacate"};

    #if 0
    // Primeira letra de cada para maiúsculo
    // FUP de ser
    // for indexado - acesso aleatório
    for (size_t i = 0; i < villains.size(); i++){
        villains[i][0] -= 'a' - 'A';
    }
    // POO de ser
    // auto ~> Inferência de tipo
    // for range
    for (auto& villain : villains){
        villain[0] = toupper(villain[0]);
    }
    #endif

    // Iteradores classe que se comporta como ponteiro
    // Ele sabe se orientar pela estrutura
    // "Aponta" para o atual e sabe como chegar no próximo
    #if 0
    villains.begin() // Iterador para o primeiro elemento
    villains.end() // Iterador para o final, abismo, elemento após o último
    villains.front() // Retorna a referência para o primeiro elemento
    villains.back() // Retorna a referência para o último elemento real da estrutura
    #endif
    for (auto& villain : villains){
        // villain.front() = toupper(villain.front());
        // *villain.begin() = toupper(*villain.begin());
        // villain.back() = toupper(villain.back());
    }

    // Remover da estrutura os que começam com 'B'
    for (auto it = villains.begin(); it != villains.end();){
        if (it->front() == 'B' || it->front() == 'b')
            villains.erase(it);
        else
            it++;
    }

    // Buscar elemento na estrutura com find
    auto it = find(villains.begin(), villains.end(), "penguin");
    if (it != villains.end())
        *it = "Oswald Cobblepot";

    for (auto villain : villains)
        cout << villain << " ";
    cout << endl;

    // Ordenar em ordem lexicográfica
    std::sort(villains.begin(), villains.end());
    // 'Ensinar' ao sort o critério de ordenação
    std::sort(villains.begin(), villains.end(), comparaString);

    for (auto villain : villains)
        cout << villain << " ";

    return 0;
}