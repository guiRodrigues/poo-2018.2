#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class MembroDaInstituicao{
protected:
    string aux, nome;
public:
    MembroDaInstituicao(string aux = 0, string nome = 0):
    aux(aux), nome(nome)
    {}
    friend ostream& operator<<(ostream &os, MembroDaInstituicao member);
};

ostream& operator<<(ostream &os, MembroDaInstituicao member){
    os << (member.aux + " :" + member.nome);
    return os;
}

class Aluno : public MembroDaInstituicao{
public:
    Aluno(string curso = "", string nome = "" ):
    MembroDaInstituicao(curso, nome) // Como a classe super em Java
    {}
};

class Professor : public MembroDaInstituicao{
public:
    Professor(string nivel = "", string nome = ""):
    MembroDaInstituicao(nivel, nome)
    {}
};

class Disciplina : public MembroDaInstituicao{
public:
    Disciplina(string curso = "", string nome = ""):
    MembroDaInstituicao(curso, nome)
    {}
};

template <typename K, typename V>
struct Repositorio{
    map<K, V> repositorio;
    #if 0
        CRUD
        ~ Create
        ~ Remove
        ~ Update
        ~ Delete
    #endif
    // Create
    void add(K key, V element){
        if (!exists(key))
            repositorio[key] = element;
        // throw "FAIL: " + std::to_string(key) + " ja existe";
        // Como imprimir a chave aqui?
        else
            throw "FAIL: Ja existe no sistema";
    }
    // Remove
    void remove(K key){
        if (exists(key))
            // Usar a chave aqui vai percorrer novamente a estrutura, seria mais inteligente usar o iterator 
            repositorio.erase(key);
        else
            throw "FAIL: Nao encontrado";
    }
    // Get second
    V& get(K key){
        // auto it = std::find(vet.begin(), vet.end(), 8);
        auto it = repositorio.find(key);
        if (it != repositorio.end())
            return it->second;
        throw "FAIL: Nao encontrado";
    }
    // Get all (keys=first && members(alu/pro/dis)=second)
    vector<V> getMembers(){
        vector<V> members;
        for (pair<K, V> par : repositorio)
            members.push_back(par.second);
        return members;
    }
    vector<K> getKeys(){
        vector<K> keys;
        for (pair<K, V> par : repositorio)
            keys.push_back(par.first);
        return keys;
    }
    // Others functions
    bool exists(K key){
        return (repositorio.find(key) != repositorio.end());
    }
};

class Controller{
    // ????????????????????????????????????????????????????????????????????????????????????
    // Como implementar o curso na estrutura de chave e valor?
    // sei que posso ter a chave como o a matrícula e os outros dados pertencentes ao aluno
    // mas ficaria interessante assim?
    Repositorio<int, Aluno> alunos;
    Repositorio<int, Professor> professores;
    Repositorio<string, Disciplina> disciplinas;
public:
    string frontEnd(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        // Create
        if (op == "addAlu" || op == "addPro" || op == "addDis"){
            // Criar template para a key
            string aux, nome;
            if (op == "addAlu" || op == "addPro"){
                int key = 0;
                in >> key >> aux;
                getline(in, nome);
                if (op == "addAlu")
                    alunos.add(key, Aluno(aux, nome));
                else
                    professores.add(key, Professor(aux, nome));
            } else {
                string key = "";
                in >> key >> aux;
                getline(in, nome);
                disciplinas.add(key, Disciplina(aux, nome));
            }
        }
        // Remove
        else if (op == "rmAlu" || op == "rmPro" || op == "rmDis"){
            if (op == "rmAlu" || op == "rmPro"){
                int key = 0;
                in >> key;
                if (op == "rmAlu")  
                    alunos.remove(key);
                else
                    professores.remove(key);
            }  else {
                string key = "";
                in >> key;
                disciplinas.remove(key);
            }
        }
        // Get individual
        else if (op == "getAlu" || op == "getPro" || op == "getDis"){
            if (op == "getAlu" || op == "getPro"){
                int key = 0;
                in >> key;
                if (op == "getAlu"){
                    Aluno& alu = alunos.get(key);
                    out << key << " :" << alu;
                } else {
                    Professor& pro = professores.get(key);
                    out << key << " :" << pro;
                }
            } else {
                string key = "";
                in >> key;
                Disciplina& dis = disciplinas.get(key);
                out << key << " :" << dis;
            }
        }
        // Get all
        else if (op == "showAlu" || op == "showPro" || op == "showDis"){
            // dynamic_cast, como usar?
            if (op == "showAlu"){
                // for (auto& matricula : alunos.getKeys()){
                //     out << matricula << endl;
                // }
                // for (auto& aluno : alunos.getMembers()){
                //     out << aluno << endl;
                // }
                Aluno alu;
                for (auto& matricula : alunos.getKeys()){
                    alu = alunos.get(matricula);
                    out << matricula << " :" << alu << endl;
                }
                // for (pair<int, Aluno> par : alunos){
                //     out << par.first << ":" << par.second << endl;
                // }
            } else if (op == "showPro"){
                Professor pro;
                for (auto& siape : professores.getKeys()){
                    pro = professores.get(siape);
                    out << siape << " :" << pro << endl;
                }
            } else if (op == "showDis"){
                Disciplina dis;
                for (auto& codigo : disciplinas.getKeys()){
                    dis = disciplinas.get(codigo);
                    out << codigo << " :" << dis << endl;
                }
            }
        }
        return out.str();
    }

    void backEnd(){
        string line;
        while (true){
            cout << endl;
            getline(cin, line);
            if (line == "end")
                return;
            cout << "$" << line << endl;
            try{
                cout << frontEnd(line) << endl;
            } catch(const char * exceoption) {
                cout << exceoption << endl;
            }
        }
    }
};

int main(){

    Controller controller;
    controller.backEnd();

    return 0;
}