#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Westeros {
protected:
    string name;
private:
    int id;
public:
    int getId() {
        return id;
    }
    void setId(int id) {
        this->id = id;
	}
    string getName() {
        return name;
    }
    void showinfo() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
	}
    Westeros(string n, int i) {
        name = n;
        id = i;
    }

};

class Lannister : public Westeros {
protected:
    int wealth;
};
class Stark : public Westeros {
protected:
    int honor;
public:
    Stark(string n, int i, int h) : Westeros(n, i) {
        honor = h;
	}
};
class Starkwarrior : public Stark {
private:
    string weapon;
public:
    Starkwarrior(string n, int i, int h, string w) : Stark(n, i, h) {
        weapon = w;
	}
    void showWarrior() {
        showinfo();
        cout << "Honor: " << honor << endl;
        cout << "Weapon: " << weapon << endl;
	}
    
};
class Targaryen : public Westeros {
private:
    int dragons;
public:
    Targaryen(string n, int i, int d) : Westeros(n, i) {
        dragons = d;
	}
    int getDragons() {
        return dragons;
	}
};
class Dragonrider : public Targaryen {
private:
    string dragonname;

public:
    Dragonrider(string n, int i, string d) : Targaryen(n, i, 1) {
        dragonname = d;
    }
    string getDragonName() {
        return dragonname;
    }
};
class Dragonmaster : public Targaryen {
private:
    string dragonname;
public:
    Dragonmaster(string n, int i, string d) : Targaryen(n, i, 0) {
        dragonname = d;
    }
    string getDragonName() {
        return dragonname;
	}
};
class Baratheon : public Westeros {
private:
    int army;
public:
    Baratheon(string n, int i) : Westeros(n, i) {
        army = 1000;
    }
     int getArmy() {
        return army;
	 }
};
class Baratheonknight : public Baratheon {  
private:
    string weapon;
public:
    Baratheonknight(string n, int i, string w) : Baratheon(n, i) {
        weapon = w;
	}
    string getWeapon() {
        return weapon;
	}
};
int main()
{
    
	vector<Westeros*> westerosCharacters;
    vector<Starkwarrior> starkWarriors;
	vector<Dragonrider> dragonRiders;
	vector<Dragonmaster> dragonMasters;
	vector<Baratheonknight> baratheonKnights;
    string currentNode = "Starkwarrior"; 
    string command;

    while (true) {

        cout << "Command: ";
        cin >> command;

        if (command == "MO") {

            if (currentNode == "Starkwarrior") {

                string name, weapon;
                int id, honor;

                cin.ignore();
                getline(cin, name);
                cin >> id >> honor;
                cin.ignore();
                if (!(getline(cin, name))) return 0;
                if (!(cin >> id >> honor)) return 0;
                cin.ignore();
                getline(cin, weapon);

                bool exists = false;
                for (auto& x : starkWarriors)
                    if (x.getName() == name) exists = true;

                if (!exists)
                    starkWarriors.push_back(Starkwarrior(name, id, honor, weapon));
            }

            else if (currentNode == "Dragonrider") {

                string name, dragonname;
                int id;

                cin.ignore();
                getline(cin, name);
                cin >> id;
                cin.ignore();
                getline(cin, dragonname);

                dragonRiders.push_back(Dragonrider(name, id, dragonname));
            }

            else if (currentNode == "Dragonmaster") {

                string name, dragonname;
                int id;

                cin.ignore();
                getline(cin, name);
                cin >> id;
                cin.ignore();
                getline(cin, dragonname);

                dragonMasters.push_back(Dragonmaster(name, id, dragonname));
            }

            else if (currentNode == "Baratheonknight") {

                string name, weapon;
                int id;

                cin.ignore();
                getline(cin, name);
                cin >> id;
                cin.ignore();
                getline(cin, weapon);

                baratheonKnights.push_back(Baratheonknight(name, id, weapon));
            }
        }
        else if (command == "DIR") {

            if (currentNode == "Starkwarrior") {
                for (auto& x : starkWarriors) x.showWarrior();
            }

            else if (currentNode == "Dragonrider") {
                for (auto& x : dragonRiders)
                    cout << x.getName() << endl;
            }

            else if (currentNode == "Dragonmaster") {
                for (auto& x : dragonMasters)
                    cout << x.getName() << endl;
            }

            else if (currentNode == "Baratheonknight") {
                for (auto& x : baratheonKnights)
                    cout << x.getName() << endl;
            }
        }
        else if (command == "FIND") {

            cin.ignore();
            string searchedName;
            getline(cin, searchedName);

            bool found = false;

            for (auto& x : starkWarriors)
                if (x.getName() == searchedName) {
                    x.showWarrior();
                    found = true;
                }

            for (auto& x : dragonRiders)
                if (x.getName() == searchedName) {
                    cout << x.getName() << endl;
                    found = true;
                }

            for (auto& x : dragonMasters)
                if (x.getName() == searchedName) {
                    cout << x.getName() << endl;
                    found = true;
                }

            for (auto& x : baratheonKnights)
                if (x.getName() == searchedName) {
                    cout << x.getName() << endl;
                    found = true;
                }

            if (!found)
                cout << "Character not found!\n";
        }
        else if (command == "CD") {
            string node;
            cin >> node;

            if (node == "Starkwarrior" ||
                node == "Dragonrider" ||
                node == "Dragonmaster" ||
                node == "Baratheonknight") {

                currentNode = node;
                cout << "Changed node to: " << currentNode << endl;
            }
            else {
                cout << "Invalid node!\n";
            }
        }
        else if (command == "EXIT") {
            break;
        }
        
    }
    return 0;


