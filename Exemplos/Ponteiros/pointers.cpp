#include <iostream>
using namespace std;

// Uso em funções
// void swap(int a, int b){
//     // Não passa de uma cópia, não alterar o 'valor dos parâmetros' passados, por isso tem que ser passado por referência
//     int c = a;
//     a = b;
//     b = c;
// }

void swap(int &a, int &b){
    // Desse modo os dois parâmetros passados serão realmente alterados
    int c = a;
    a = b;
    b = c;
}

int main(){
    
    // int a = 789;
    // lvalue = rvalue;
    // int * pointer = &a;

    /*

        * como lvalue = guarde em quem 'mora'
        * como rvalue = pegando quem 'mora'
        & como lvalue = referência a, 'apelido', se eu modificar o apelido, o rvalue será modificado
        & como rvalue = o endereço de
    */

    // cout << pointer << endl;
    // cout << *pointer << endl;
    // cout << &pointer << endl;
    // cout << a << endl;
    // cout << &a;

    // int &c = a;
    // c = 1;

    // cout << c << " " << a << " " << *pointer;

    int a = 1;
    int * pointer = &a;
    int b = 2;
    int * pointer1 = &b;
    swap(*pointer, *pointer1);
    cout << a << " " << b;

    return 0;
}