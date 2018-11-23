#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Fone {
public:
    string id;
    string number;

    Fone(string id = "", string number = ""){
        this->id = id;
        this->number = number;
    }

    static bool validate(string number) {
        string data = "1234567890()- ";
        for(auto c : number)
            if(data.find(c) == string::npos)
                return false;
        return true;
    }

    bool operator==(Fone fone){
        return (this->id == fone.id) && (this->number == fone.number);
    }
};

class Contato {
    string name;
    vector<Fone> fones;
    bool favorite {false};
public:
    Contato(string name = ""){
        this->name = name;
    }

    string getName(){
        return name;
    }

    bool isFavorite(){ return this->favorite; }
    void setFavorite(bool favorite){ this->favorite = favorite; }

    void addFone(Fone fone){
        if(!Fone::validate(fone.number))
            throw string("fone " + fone.number + " invalido");
        fones.push_back(fone);
    }

    void rmFone(size_t indice){
        if(indice < 0 || indice >= fones.size())
            throw string("indice " + to_string(indice) + " nao existe");
        fones.erase(fones.begin() + indice);
    }

    vector<Fone> getFones(){
        vector<Fone> resp;
        for(auto fone: fones)
            resp.push_back(fone);
        return resp;
    }

    string toString(){
        string saida = this->name + " C ";
        int i = 0;
        for(auto fone : getFones())
            saida += "[" + to_string(i++) + ":" + fone.id + ":" + fone.number + "]";
        return saida;
    }
};

class Agenda {
    map<string, Contato> contatos;
    map<string, Contato*> favoritos;

public:
    void addContato(Contato cont){
        string name = cont.getName();
        if(contatos.count(name) == 1){
            auto contato = getContato(name);
            for (auto fone : cont.getFones()){
                // auto f = find(contato->getFones(), contato->getFones()+contato->getFones().size(), fone);
                auto it = std::find_if(contato->getFones().begin(), contato->getFones().end(), [fone](Fone f){ return fone.id==f.id && fone.number==f.number; });
                if (it == contato->getFones().end())
                    cout << ".\n";
                contato->addFone(fone);
            }
        }
            // throw string("contato " + name + " ja existe");
        contatos[name] = cont;
    }

    void addFavorite(Contato* contato){
        string name = contato->getName();
        if (favoritos.count(name) == 1)
            throw string("contato " + name + " ja favoritado");
        contato->setFavorite(true);
        favoritos[name] = contato;
    }

    void rmContato(string name) {
        contatos.erase(name);
    }

    void rmFavorite(string name){
        auto contato = getContato(name);
        if (!contato->isFavorite())
            throw string("contato " + contato->getName() + " nao e favorito");
        contato->setFavorite(false);
        favoritos.erase(name);
    }

    Contato * getContato(string name){
        if(contatos.count(name))
            return &contatos[name];
        throw string("  contato " + name + " nao existe");
    }

    vector<Contato> getContatos(){
        vector<Contato> resp;
        for(auto& par : contatos)
            resp.push_back(par.second);
        return resp;
    }

    vector<Contato> getFavorites(){
        vector<Contato> favorites;
        for (auto& par : contatos)
            if (par.second.isFavorite())
                favorites.push_back(par.second);
        return favorites;
    }

    vector<Contato> search(string pattern){
        vector<Contato> resp;
        for(auto& par : contatos)
            if(par.second.toString().find(pattern) != string::npos)
                resp.push_back(par.second);
        return resp;
    }

    string toString(){
        string saida = "";
        for(auto contato : getContatos()){
            if (contato.isFavorite())
                saida += "@ ";
            else
                saida += "- ";
            saida += contato.toString() + "\n";
        }
        return saida;
    }
};

class Controller {

    Agenda agenda;
public:

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "addContato"){
            string name, id_number;
            ss >> name;
            Contato cont(name);
            while(ss >> id_number){
                string id, fone;
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
                cont.addFone(Fone(id, fone));
            }
            agenda.addContato(cont);
        }
        else if(op == "rmFone"){
            string name;
            int indice;
            ss >> name >> indice;
            agenda.getContato(name)->rmFone(indice);
        }
        else if(op == "rmContato"){
            string name;
            ss >> name;
            agenda.rmContato(name);
        }
        else if(op == "agenda"){
            cout << agenda.toString();
        }
        else if(op == "search"){
            string pattern;
            ss >> pattern;
            auto resp = agenda.search(pattern);
            for(auto contato : resp)
                cout << contato.toString() << endl;
        } else if (op == "fav"){
            string name;
            ss >> name;
            auto* contato = agenda.getContato(name);
            agenda.addFavorite(contato);
        } else if (op == "favorited"){
            auto favorites = agenda.getFavorites();
            for (auto favorite : favorites)
                cout << "@ " << favorite.toString() << endl;
        } else if (op == "unfav"){
            string name;
            ss >> name;
            agenda.rmFavorite(name);
        }
        /*
        if(op == "fav"){
            string name;
            ss >> name;
            agenda.favoritar(name);
            return "done";
        }
        if(op == "desfav"){
            string name;
            ss >> name;
            agenda.desfavoritar(name);
            return "done";
        }
        if(op == "showFav"){
            string saida = "";
            auto favs = agenda.getFavoritos();
            for(auto contato : favs)
                saida += contato.toString() + "\n";
            return saida;
        }
        */
        else
            cout << "comando invalido" << endl;
    }


    void exec() {
        string line = "";
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            try {
                shell(line);
            } catch(const string& e) {
                cout << e << endl;
            }
        }
    }
};

int main()
{
    Controller controller;
    controller.exec();
    return 0;
}