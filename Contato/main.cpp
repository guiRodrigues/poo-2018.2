#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Contato{
private: //implícito
    // Atributos da classe/objeto
    string operadora, fone;

public:
    // Construtor
    Contato(string operadora = "", string fone = ""):
        operadora(operadora),
        fone(fone)
    {}

    // Creating getters and setters (Métodos acessores e modificadores)
    // GETTERS
    string getOperadora(){ return this->operadora; }
    string getFone(){ return this->fone; }
    // SETTERS
    void setOperadora(string operadora){ this->operadora = operadora; }
    void setFone(string fone){ this->fone = fone; }

    // Outros métodos
    string toString(){
        stringstream flow;
        flow << getOperadora() << ":" << getFone();
        return flow.str();
    }

};

class Pessoa{
private:
    // Atributos
    string nome;
    vector<Contato> lista;

public:
    // Construtor
    Pessoa(string nome = ""):
      nome(nome)
    {}
    // Getters and Setters methods (Métodos acessores e modificadores)
    string geTNome(){ return this->nome; }
    string getLista(){
        stringstream flow;
        int i = 0;
        for (Contato contato : lista) {
          flow << " [" << i << ":" << contato.toString() << "]";
          i++;
        }
        return flow.str();
    }
    void setNome(string nome) { this->nome = nome; }

    // Outros Métodos
    bool validate(string fone){
      for (size_t i = 0; i < fone.length(); i++)
        if (!isdigit(fone[i]) && fone[i]!='(' && fone[i]!=')' && fone[i]!='.')
          return false;
      return true;
    }

    bool add(Contato novoContato){
      for (Contato contato : lista)
        if (contato.getFone() == novoContato.getFone()){
          cout << "FAIL: fones repetidos não são aceitos!" << endl;
          return false;
        }
      if (!validate(novoContato.getFone())){
        cout << "FAIL: o número inserido não é válido" << endl;
        return false;
      }
      lista.push_back(novoContato);
      return true;
    }

    bool removeIndex(int i){
      if (i>=0 && i<(int)lista.size()){
        lista.erase(lista.begin() + i);
        cout << "done" << endl;
        return true;
      }
      cout << "FAIL: índice não reconhecido" << endl;
      return false;
    }

    bool removeLabel(string label){
      int aux = 0;
      for (size_t i=0; i<lista.size(); i++){
        if (lista[i].getOperadora() == label)
        lista.erase(lista.begin() + i);
        aux++;
      }
      if (aux>0){
        cout << "done" << endl;
        return true;
      }
      cout << "FAIL: nehuma operadora com o nome " << label << " foi encontrada" << endl;
      return false;
    }

    void update(string line){
      stringstream flow(line);
      string word;
      flow >> word;
      setNome(word);
      lista.clear();
      while (flow >> word){
        stringstream ss(word);
        string operadora, fone;
        getline(ss, operadora, ':');
        getline(ss, fone);
        if (validate(fone))
          lista.push_back(Contato(operadora, fone));
        else
          cout << "WARNING: o contato " << operadora << ":" << fone << " é inválido e não será inserido" << endl;
      }
    }
};

class Controller{
private:
  Pessoa pessoa;

public:
  string shell(string line){
    stringstream in(line), out;
    string op;
    in >> op;
    if (op == "help")
      out << "new _nome_; show;" << endl;
    else if (op == "new"){
      string nome;
      in >> nome;
      pessoa = Pessoa(nome);
      out << "done" << endl;
    } else if (op == "show"){
      out << pessoa.geTNome() << " => {" << pessoa.getLista() << " }" << endl;
    } else if (op == "add"){
      string nome, fone;
      in >> nome >> fone;
      pessoa.add(Contato(nome, fone));
      cout << "done" << endl;
    } else if (op == "rm"){
      string opOp;
      in >> opOp;
      if (opOp == "-i"){
        int index = 0;
        in >> index;
        pessoa.removeIndex(index);
      } else if (opOp == "-l"){
        string label;
        in >> label;
        pessoa.removeLabel(label);
      } else
        out << "FAIL: comando não reconhecido" << endl;
    } else if (op == "update"){
      string line;
      getline(in, line);
      pessoa.update(line);
      out << "done" << endl;
    }
    return out.str();
  }

  void exec(){
    cout << endl; //Questão estética!!!
    string line;
    while (true){
      getline(cin, line);
      if (line == "end")
        return;
      cout << "$ " << line << endl;
      cout << "~ " << shell(line) << endl;
    }
  }

};

int main(){

  Controller controller;
  controller.exec();

    return 0;
}
