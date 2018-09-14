#include <iostream>
#include <sstream>
using namespace std;

class Pet{
private:
    int hungry, hungryM, energy, energyM, clean, cleanM, diamonds{0}, age{0}, vivo;
public:

    // Getters
    int getHungry(){ return this->hungry; }
    int getEnergy(){ return this->energy; }
    int getclean(){ return this->clean; }
    int getHungryM(){ return this->hungryM; }
    int getEnergyM(){ return this->energyM; }
    int getcleanM(){ return this->cleanM; }
    int getDiamonds(){ return this->diamonds; }
    int getAge(){ return this->age; }
    bool isVivo(){ return this->vivo; }

    // Setters
    // É mais semântico realizar o tratamento de erro aqui?
    void setHungry(int hungry){
        if (hungry < 0)
            this->hungry = 0;
        else
            this->hungry = hungry;
    }
    void setEnergy(int energy){ this->energy = energy; }
    void setClean(int clean){ this->clean = clean; }
    void setHungryM(int hungryM){ this->hungryM = hungryM; }
    void setEnergyM(int energyM){ this->energyM = energyM; }
    void setCleanM(int cleanM){ this->cleanM = cleanM; }
    void setDiamonds(int diamonds){ this->diamonds = diamonds; }
    void setAge(int age){ this->age = age; }
    void setVivo(bool vivo){ this->vivo = vivo; }

    // Construtor
    Pet(int energyM = 0, int hungryM = 0, int cleanM = 0):
        hungry(hungryM), hungryM(hungryM),
        energy(energyM), energyM(energyM),
        clean(cleanM), cleanM(cleanM)
    {}

    // Others methods
    string toString(){
        stringstream flow;
        flow << "E:" << getEnergy() << "/" << getEnergyM() << ", "
             << "H:" << getHungry() << "/" << getHungryM() << ", "
             << "C:" << getclean() << "/" << getcleanM() << ", "
             << "D:" << getDiamonds() << ", "
             << "A:" << getAge() << endl;
        return flow.str();
    }

    bool coveiroAceita(){
        if (getEnergy() <= 0){
            setEnergy(0);
            cout << "fail: pet morreu de fraqueza";
            setVivo(false);
            return true;
        }
        else if (getHungry() <= 0){
            setHungry(0);
            setVivo(false);
            cout << "fail: pet morreu de fome";
            return true;
        }
        else if (getclean() <= 0){
            setClean(0);
            setVivo(false);
            cout << "fail: pet morreu de sujeira";
            return true;
        }
        return false;
    }

    void play(){
        if (!isVivo()){
            cout << "fail: pet esta morto";
            return;
        }
        setEnergy(getEnergy() - 2);
        setHungry(getHungry() - 1);
        setClean(getclean() - 3);
        coveiroAceita();
        setAge(getAge() + 1);
        setDiamonds(getDiamonds() + 1);
    }

    void eat(){
        if (!isVivo()){
            cout << "fail: pet esta morto";
            return;
        }
        if (getHungry() >= getHungryM())
            cout << "o pet está saciado";
        else {
            setEnergy(getEnergy() - 1);
            setHungry(getHungry() + 4);
            setClean(getclean() - 2);
            setAge(getAge() + 1);
        }
    }

    void sleep(){
        if (!isVivo()){
            cout << "fail: pet esta morto";
            return;
        }
        setHungry(getHungry() - 1);
        setAge(getAge() + (getEnergyM() - getEnergy()));
        setEnergy(getEnergyM());
    }

    void cleanPet(){
        if (!isVivo()){
            cout << "fail: pet esta morto";
            return;
        }
        setHungry(getHungry() - 1);
        setEnergy(getEnergy() - 3);
        setAge(getAge() + 2);
        setClean(getcleanM());
    }

    
};

class Controller{
public:
    Pet pet;

    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "init"){
            int energyM, hungryM, cleanM;
            in >> energyM >> hungryM >> cleanM;
            pet = Pet(energyM, hungryM, cleanM);
            out << "success" << endl;
        }
        else if (op == "show")
            out << pet.toString();
        else if (op == "play")
            pet.play();
        else if (op == "eat")
            pet.eat();
        else if (op == "sleep")
            pet.sleep();
        else if (op == "clean")
            pet.cleanPet();
        return out.str();
    }

    void exec(){
        cout << endl << endl; // estética
        string line;
        while (true){
            getline(cin, line);
            if (line == "end")
                return;
            cout << line << endl;
            cout << shell(line) << endl;
        }
    }

};

int main(){

    Controller controller;
    controller.exec();

    return 0;
}