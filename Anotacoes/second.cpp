#include <iostream>
#include <vector>
using namespace std;

class User{
    string username, password;
    vector<Note> notes;
public:
    User(string username = "", string password = ""):
    username(username), password(password)
    {}
    // friendship
    friend ostream& operator<<(ostream& os, User user);
};

ostream& operator<<(ostream& os, User user){
    os << user.username << "\n";
    return os;
}

class Note{
    string title, body;
public:
    Note(string title = "", string body = ""):
    title(title), body(body)
    {}
    // friendship
    friend ostream& operator<<(ostream& os, Note note);
};

ostream& operator<<(ostream& os, Note note){
    os << note.title << ", " << note.body << "\n";
    return os;
}

int main(){

    return 0;
}