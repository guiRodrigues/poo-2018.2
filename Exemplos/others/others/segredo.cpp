#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Secret{
    // Attributes
    int level;
    string secret;
public:
    // Getters
    int getLevel(){ return this->level; }
    string getSecret(){ return this->secret; }
    // Construtor
    Secret(int level = 0, string secret = ""):
    level(level), secret(secret)
    {}
    /*

    No caso de um construtor privado:
    Secret& getInstance(){
        static Secret secret; # aqui tenho um segredo resiliente ao escopo
        return secret; # e esse é o único segredo que há
    }
    # para chamar ficaria assim:
        Secret::getInstance()

    */
    // Others methods
    string toString(){
        return "[" + to_string(getLevel()) + " " + getSecret() + "]"; 
    }
};

class User{
    // Attributes
    string name, pass;
    Secret secret;
public:
    string maskPass(){
        string mask;
        for (char c : pass)
            mask += '*';
        return mask;
    }
    // Getters
    string getName(){ return this->name; }
    string getPass(){ return maskPass(); }
    // Construtor
    User(string name = "", string pass = ""):
    name(name), pass(pass)
    {}
    // Others methods
    string toString(){
        return "Nome: " + getName() + " " + secret.toString();
    }
};

class System{
    vector<User> users;
public:
    System(){
        users.push_back(User("admin", "admin"));
    }
};

class Controller{
    System system;
public:
    string fontEnd(string line){
        stringstream in(line), out;
        return "U";
    }

    void backEnd(){

    }
};

int main(){

    cout << "Hello";

    return 0;
}