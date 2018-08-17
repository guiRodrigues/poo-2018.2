#include <iostream>
#include <cstdio>
// As bibliotecas do C foram "adaptadas" para o C++ com o acréscimo do 'c' no include { #include <ctime> }

int x = 7;

int main(){

    int x = 9;

    /*
        x ~> x do escopo
        ::x ~> do arquivo
    */

    std::cout << x << " " << ::x << std::endl;
    // Impressão de como seria em C
    printf("%d %d\n", x, ::x);

    return 0;
}