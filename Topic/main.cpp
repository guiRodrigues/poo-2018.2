#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Person {

//    Attributes
    string name;
    int age;
    bool preferential = false;

//    Methods
//    Constructor
    Person(string name, int age) {
        this->name = name;
        this->age = age;
        if (age > 60)
            this->preferential = true;
    }

    string toString() {
        stringstream ss;
        ss << this->name << ":" << this->age;
        return ss.str();
    }

};

struct Topic {

//    Attributes
    vector<Person *> passengers;
    int size;
    int preferential;

//    Methods
//    Constructor
    Topic(int size = 0, int pref = 0) {
        for (int i = 0; i < size; i++)
            passengers.push_back(nullptr);
        this->size = size;
        this->preferential = pref;
    }

    string toString() {
        stringstream ss;
        ss << "[";
        int pref = 0;
        for (Person *person : passengers) {
            if (person != nullptr) {
                if (person->preferential)
                    ss << " @" << person->toString();
                else
                    ss << " #" << person->toString();
            } else {
                if (pref < this->preferential)
                    ss << " @";
                else
                    ss << " -";
            }
            pref++;
        }
        ss << " ]" << endl;
        return ss.str();
    }

//    bool in(Person *person) {
//        int helper = 0;
//        if (person->age > 60) {
//            for (int i = 0; i < this->preferential; i++) {
//                if (passengers[i] == nullptr) {
//                    passengers[i] = person;
//                    return true;
//                }
//            }
//        }
//        for (int i = (this->preferential); i <= this->size; i++) {
//            if (passengers[i] == nullptr) {
//                passengers[i] = person;
//                return true;
//            }
//            else if (helper == (this->size - this->preferential)) {
//                for (int j = 0; j < this->preferential; j++) {
//                    if (passengers[j] == nullptr) {
//                        passengers[j] = person;
//                        return true;
//                    }
//                }
//            }
//            helper++;
//        }
//
//        cout << " fail: A topic lotada" << endl;
//        return false;
//    }

    bool in(Person *person) {
        int aux = 0;
        if (person->age > 60) {
            for (int i = 0; i < size; i++) {
                if (passengers[i] == nullptr) {
                    passengers[i] = person;
                    return true;
                }
            }
        } else {
            for (int i = preferential; i < size; i++) {
                aux++;
                if (passengers[i] == nullptr) {
                    passengers[i] = person;
                    return true;
                }
            }
            if (aux == (this->size - this->preferential)){
                for (int i = 0; i < size; i++) {
                    if (passengers[i] == nullptr) {
                        passengers[i] = person;
                        return true;
                    }
                }
            }
        }
        cout << "   fail: Topic lotada" << endl;
        return false;
    }

    bool out(string name) {
        for (int i = 0; i < size; i++) {
            if (passengers[i]->name == name) {
                passengers[i] = nullptr;
                cout << "   done" << endl;
                return true;
            }
        }
        cout << "   fail: deu errado" << endl;
        return false;
    }

};

int main() {

    Topic topic;
    string op;

    while (true) {
        cin >> op;
        if (op == "end")
            break;
        else if (op == "new") {
            int size = 0, pref = 0;
            cin >> size >> pref;
            topic = Topic(size, pref);
            cout << "   done" << endl;
        } else if (op == "show")
            cout << topic.toString();
        else if (op == "in") {
            string name;
            int age = 0;
            cin >> name >> age;
            if (topic.in(new Person(name, age))) {
                cout << "   done" << endl;
            }
        } else if (op == "out") {
            string name;
            cin >> name;
            topic.out(name);
        }
    }

    return 0;
}