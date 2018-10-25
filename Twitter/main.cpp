#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Tweet{
    string body;
public:
    Tweet(string body = ""):
    body(body)
    {}
};

class Timeline{
    
};

class User{
    string username, password;
    vector<User> seguidos;
    vector<User> seguidores;
    vector<Tweet> tweets;
public:
    User(string username = "", string password = ""):
    username(username), password(password)
    {}
    // Getters
    string getUsername(){ return this->username; }
    // Setters
    
    void follow(User user){
        for (auto u : seguidos)
            if (user == u)
                throw "Fail: " + this->username + " já segue " + user.username;
        seguidos.push_back(user);
    }
    
    void followed(User user){
        seguidores.push_back(user);
    }
    
    bool operator==(User user){
        return this->username == user.username;
    }
    
    void tweetar(string body){
        tweets.push_back(Tweet(body));
    }
    
//    void addNote(string title, string body){
//        for (auto& note : notes)
//            if (note.getTitle() == title)
//                throw "Fail: Nota já cadastrada";
//        notes.push_back(Note(title, body));
//    }
    
//    void removeNote(string title){
//        // auto it = find(users.begin(), users.end(), User(username));
//        // if (it != users.end()) // Diferente do abismo!
//        //     return *it;
//
//        auto it = find_if(notes.begin(), notes.end(), [title](auto note){return note.getTitle() == title;});
//        if (it == notes.end())
//            throw "Fail: Nota não encontrada";
//        notes.erase(it);
//        // Como buscar um objeto pelo find???????????
//        /* for (size_t i=0; i<notes.size(); i++)
//         if (notes[i].getTitle() == title){
//         notes.erase(notes.begin() + i);
//         break;
//         } */
//    }
    
//    string showNotes(){
//        stringstream allNotes;
//        for (auto& note : notes)
//            allNotes << note;
//        return allNotes.str();
//    }
    
    // toString()
    friend ostream& operator<<(ostream& os, User user);
};

ostream& operator<<(ostream& os, User user){
    os  << "\n" << user.username << "\n  seguidos [ ";
    
    for (auto& u : user.seguidos)
        os << u.username << " ";
    
    os << "]";
    os << "\n  seguidores [ ";
    
    for (auto& u : user.seguidores)
        os << u.username << " ";
    
    os << "]";
    return os;
}

class System{
    vector<User> users;
public:
    System(){}
    
    // Como implementar o exists() nesse caso?
    
    User& getUser(string username){
        for (auto& user : users)
            if (user.getUsername() == username)
                return user;
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
    
    void follow(string username, string toFollow){
        getUser(username).follow(getUser(toFollow));
        getUser(toFollow).followed(getUser(username));
    }
    // tenho como sobrecarregar um método de uma  classe?
};

class Controller{
    System system;
public:
    
    Controller(){}
    
    string frontEnd(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "nwuser"){
            string username;
            in >> username;
            system.addUser(User(username));
        }
        else if (op == "lauser"){
            out << system.getUsers().str();
        }
        else if (op == "seguir"){
            string username, toFollow;
            in >> username >> toFollow;
            system.follow(username, toFollow);
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
            } catch (const char * exception){
                cout << exception << endl;
            } catch (string exception){
                cout << exception << endl;
            }
        }
    }
};

int main(){
    Controller controller;
    controller.backEnd();
}
