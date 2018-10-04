#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T sum(T a, T b){
    return a + b;
}

struct Ostra{
    int value;
    Ostra(int value){
        this->value = value;
    }
    int getValue(){ return this->value; }
};

int main(){

    // Sobrecarga de soma para inteiros?
    cout << sum<int>(2, 7) << endl;
    cout << sum<float>(2.7, 7.2) << endl;
    cout << sum<char>('a', 'b') << endl;
    cout << sum<string>("gui", "lherme") << endl;

    return 0;
}