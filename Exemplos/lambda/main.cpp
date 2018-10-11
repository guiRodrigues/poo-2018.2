#include <iostream>
#include <vector>
using namespace std;

int main(){

    #if 0
        [] = captura de variáveis
        () = passagem de parâmetros
        {} = escopo da função
        -> = tipo de retorno
    #endif
    
    auto maior = [](vector<int> numbers)->int{
        int m = 0;
        for (int i : numbers)
            if (i > m) m = i;
        return m;
    };

    cout << maior({2, 3, 56, 7, 764, 342, 1});

    // cout << maior(8, 18);

    return 0;
}