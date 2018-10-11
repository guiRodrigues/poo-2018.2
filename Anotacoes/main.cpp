#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Note{
    string title, body;
public:
    Note(string title = "", string body = ""):
    title(title), body(body)
    {}
    // Getters
    string getTitle(){ return this->title; }
    bool operator==(Note other){
        return title == other.title;
    }
    // toString()
    friend ostream& operator<<(ostream& os, Note note);
};

ostream& operator<<(ostream& os, Note note){
    os << note.title << "; " << note.body;
    return os;
}

class User{
    string username, password;
    vector<Note> notes;
public:
    User(string username = "", string password = ""):
    username(username), password(password)
    {}
    // Getters
    string getUsername(){ return this->username; }
    // Setters
    void setPassword(string password){ this->password = password; }
    // Por que o verificar senha deve estar no usuário? é papel dele? mas só "ele" deve ter acesso
    bool validatePass(string pass){
        return this->password == pass;
    }

    void changePass(string oldPass, string newPass){
        if (validatePass(oldPass) == false)
            throw "Fail: Senha inválida";
        setPassword(password);
    }

    void addNote(string title, string body){
        for (auto& note : notes)
            if (note.getTitle() == title)
                throw "Fail: Nota já cadastrada";
        notes.push_back(Note(title, body));
    }

    void removeNote(string title){
        // auto it = find(users.begin(), users.end(), User(username));
        // if (it != users.end()) // Diferente do abismo!
        //     return *it;

        auto it = find_if(notes.begin(), notes.end(), [title](auto note){return note.getTitle() == title;});
        if (it == notes.end())
            throw "Fail: Nota não encontrada";
        notes.erase(it);
        // Como buscar um objeto pelo find???????????
        /* for (size_t i=0; i<notes.size(); i++)
            if (notes[i].getTitle() == title){
                notes.erase(notes.begin() + i);
                break;
            } */
    }

    string showNotes(){
        stringstream allNotes;
        for (auto& note : notes)
            allNotes << note;
        return allNotes.str();
    }

    // toString()
    friend ostream& operator<<(ostream& os, User user);
};
ostream& operator<<(ostream& os, User user){
    os << user.username << endl;
    for (auto note : user.notes)
        os << "[" << note << "]" << endl;
    return os;
}

class System{
    vector<User> users;
public:
    System(){}

    // Como implementar o exists() nesse caso?

    User& getUser(string username){
        // WTF???
        // auto it = find(users.begin(), users.end(), User(username));
        // if (it != users.end()) // Diferente do abismo!
        //     return *it;
        for (auto& user : users){
            if (user.getUsername() == username)
                return user;
        }
        throw "Fail: Usuario nao encontrado";
    }

    void addUser(User user){
        for (auto other : users)
            if (user.getUsername() == other.getUsername())
                throw "Fail: Usuario ja cadastrado";
        users.push_back(user);
    }

    // Qual seria uma forma interessante de pegar os usuários?
    stringstream getUsers(){
        stringstream response;
        for (auto& user : users)
            response << user;
        return response;
    }
    // tenho como sobrecarregar um método de uma  classe?
};

class LoginManeger{
    User * current;
    System * system;
public:
    LoginManeger(System * system){
        this->system = system;
        this->current = nullptr;
    }

    User& getCurrent(){
        if (current == nullptr)
            throw "Fail: Nehum usuário logado";
        return *current;
    }

    void login(string username, string pass){
        if (current != nullptr)
            throw "Fail: Já existe alguém logado no sistema";
        User& user = system->getUser(username);
        if (!user.validatePass(pass))
            throw "Fail: Senha inválida";
        current = &user;
    }

    void logout(){
        if (current == nullptr)
            throw "Fail: Niguém logado";
        current = nullptr;
    }

    bool isLogged(){
        return current != nullptr;
    }
};

class Controller{
    System system;
    LoginManeger loginManeger;
public:

    Controller():
    loginManeger(&system){

    }

    string frontEnd(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "addUser"){
            string username, password;
            in >> username >> password;
            system.addUser(User(username, password));
        }
        else if (op == "login"){
            string username, pass;
            in >> username >> pass;
            // É melhor passar nas funções como add, etc; o objeto ou os atributos?
            loginManeger.login(username, pass);
        }
        else if (op == "logout"){
            loginManeger.logout();
        }
        else if (op == "showUsers"){
            out << system.getUsers().str();
        }
        else if (op == "changePass" || op == "addNote" || op == "rmNote" || op == "shoNotes" || op == "showNotes"){
            if (loginManeger.isLogged()){
                if (op == "changePass"){
                    if (loginManeger.isLogged()){
                        string oldPass, newPass;
                        in >> oldPass >> newPass;
                        loginManeger.getCurrent().changePass(oldPass, newPass);
                    }
                }
                else if (op == "addNote"){
                    string title, body;
                    in >> title;
                    getline(in, body);
                    loginManeger.getCurrent().addNote(title, body);
                }
                else if (op == "rmNote"){
                    string title;
                    in >> title;
                    loginManeger.getCurrent().removeNote(title);
                }
                else if (op == "showNotes"){
                    out << loginManeger.getCurrent().showNotes();
                }
            } else {
                throw "Fail: Ninguém logado";
            }
        }
        else {
            out << "Fail: Comando inválido";
        }
        return out.str();
    }
    void backEnd(){
        string line;
        while (true){
            getline(cin, line);
            if (line == "end")
                return;
            cout << "$" << line << endl;
            try{
                cout << frontEnd(line) << endl;
            } catch(const char * exception){
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