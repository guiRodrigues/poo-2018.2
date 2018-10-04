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
    // Setter
    void setLevel(int level){
        if (level>=0 && level<=10)
            this->level = level;
        else throw "fail: nível inválido";
    }
    // Construtor
    Secret(int level = 0, string secret = ""):
        secret(secret)
    {
        setLevel(level);
    }
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
    string maskPass(){
        string mask;
        for (int i=0; i<(getPass().size()); i++)
            mask+='*';
        return mask;
    }
    bool checkPass(string pass){
        return getPass() == pass;
    }
};

class System{
    vector<User> users;
public:
    // Construtor
    System(){
        users.push_back(User("admin", "admin"));
    }
    User& getUser(string name){
        for (auto& user : users)
            if (user.getName() == name)
                return user;
        throw "fail: usuário não encontrado";
    }
    // CRUD
    // CREATE
    void addUser(User user){
        for (auto& u : users) // & para pegar a referência do usuário, não a cópia dele / a variável u e o user no vector possuem o mesmo endereço
            if (u.getName() == user.getName())
                throw "fail: usuário já cadastrado";
        users.push_back(user);
    }
    // READ
};

class LoginManeger{
    User * current;
    System * system;
public:
    LoginManeger(System * system){
        this->system = system;
    }
    User& getUser(){
        if (current == nullptr)
            throw "fail: ninguem logado";
        return *current;
    };

    void login(string login, string pass){
        if (current != nullptr)
            throw "fail: já existe alguém logado";
        User& user = system->getUser(login);
        if (!user.checkPass(pass))
            throw "fail: senha invalida";
        current = &user;
    }

    void logout(){
        if (current == nullptr)
            throw "fail: não há ninguem logado";
        current = nullptr;
    }
};

class Controller{
    System system;
    LoginManeger logMan;
    User * current;
public:
    // "O login é uma informação persistente de quem está logado"
    Controller():
        logMan(&system)
    {
        current = nullptr;
    }
    string frontEnd(string line){
        stringstream in(line), out;
        string option;
        in >> option;
        if (option == "add"){
            string name, pass;
            in >> name >> pass;
            system.addUser(User(name, pass));
        } else if (option == "login"){
            string name, pass;
            in >> name >> pass;
            logMan.login(name, pass);
        } else if (option == "logout"){
            logMan.logout();
        } else if (option == "string"){
            if (current == nullptr)
                throw "fail: não há ninguém logado";
            out << current->toString() << endl;
        }
        return out.str();
    }
    
    void backEnd(){
        string line;
        while(true){
            getline(cin, line);
            if (line == "end")
                return;
            try{
                cout << frontEnd(line) << endl;
            } catch(const char* exception){
                cout << exception << endl;
            }
        }
    }
};

int main(){
    
    Controller controller;
    controller.backEnd();
    
    return 0;
}
