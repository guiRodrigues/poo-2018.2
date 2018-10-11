#include <iostream>
#include <sstream>
using namespace std;

template <typename T>
T read(stringstream& ss){
    T something;
    ss >> something;
    return something;
}

template <class T>
string hello(T something){
    return "Hello " + to_string(something);
}

int main(){
    
    stringstream flow("Cobblepot 17 99.72");
    string nome = read<string>(flow);
    int some = read<int>(flow);
    float f = read<float>(flow);

    string ola = hello<int>(some);
    cout << ola;

    return 0;
}