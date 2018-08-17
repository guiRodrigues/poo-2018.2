#include <iostream>

// Uso exclusivo no arquivo
static int soma(int a, int b){
    return a+b;
}

// Variável global mas que é restrita ao arquivo em questão
static int global_mas_local = 7;

void fun(){
    // Variável persistente, quando a função for chamada, a variável 'x' será criada uma vez, mas quando a função for encerrada, ela permanecerá
    static int x = 0;
    x++;
    std::cout << x;
}

int main(){

    /*
        em primeiro caos, o 'static' é usado em três ocasiões:
            - em variáveis globais
            - em funções
            - em variáveis locais
    */

   fun();

    return 0;
}