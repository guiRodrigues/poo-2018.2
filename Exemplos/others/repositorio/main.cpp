#include <iostream>
#include <sstream>
#include <map>
using namespace std;

class Aluno{
    string curso, nome;
public:
    // Construtor
    Aluno(string curso = "", string nome = ""):
    curso(curso), nome(nome)
    {}
    string toString(){
        return this->curso + ":" + this->nome;
    }
};

class Professor{
    string nivel, nome;
public:
    // Construtor
    Professor(string nivel = "", string nome = ""):
    nivel(nivel), nome(nome)
    {}
    string toString(){
        return this->nivel + ":" + this->nome;
    }
};

class Disciplina{
    string curso, nome;
public:
    // Construtor
    Disciplina(string curso = "", string nome = ""):
    curso(curso), nome(nome)
    {}
    string toString(){
        return this->curso + ":" + this->nome;
    }
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
        if (op == "addAlu" || op == "addPro" || op == "addPro"){
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
        // Get
        else if (op == "getAlu" || op == "getPro" || op == "getDis"){
            if (op == "getAlu" || op == "getPro"){
                int key = 0;
                in >> key;
                if (op == "getAlu"){
                    Aluno& alu = alunos.get(key);
                    out << key << " :" << alu.toString();
                } else {
                    Professor& pro = professores.get(key);
                    out << key << " :" << pro.toString();
                }
            } else {
                
            }
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