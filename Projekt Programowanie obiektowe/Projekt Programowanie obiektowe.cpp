#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Westeros {
protected:
    string name;
private:
    int id;
public:
    int getId() { return id; }
    void setId(int id) { this->id = id; }
    void showinfo() {
        std::cout << "Name: " << name << endl;
        std::cout << "ID: " << id << endl;
    }
    Westeros(string n, int i) {
        name = n;
        id = i;
    }
    virtual string getName() { return name; }
    virtual void show() { showinfo(); }
    virtual string getType() = 0;

    virtual bool isKindOf(string baseNode) {
        if (baseNode == "Westeros") return true;
        return false;
    }

    virtual ~Westeros() {}
};

class Lannister : public Westeros {
protected:
    int wealth;
    string castle;
private:
    int lannisterPrivateField;
public:
    string getType() override { return "Lannister"; } 
    Lannister(string n, int i, int w) : Westeros(n, i) {
        wealth = w;
        castle = "Casterly Rock";
        lannisterPrivateField = 42;
    }
    int getWealth() { return wealth; }
    void show() override {
        showinfo();
        std::cout << "Castle (from Lannister): " << castle << endl;
        std::cout << "Wealth: " << wealth << " gold dragons" << endl;
    }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Lannister") return true;
        return Westeros::isKindOf(baseNode);
    }
};

class Stark : public Westeros {
protected:
    int honor;
    string sigil;
private:
    int starkPrivateField;
public:
    Stark(string n, int i, int h) : Westeros(n, i) {
        honor = h;
        sigil = "Direwolf";
        starkPrivateField = 7;
    }
    int getHonor() { return honor; }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Stark") return true;
        return Westeros::isKindOf(baseNode);
    }
};

class Starkwarrior : public Stark {
private:
    string weapon;
protected:
    int warriorRank;
public:
    string getType() override { return "Starkwarrior"; }
    Starkwarrior(string n, int i, int h, string w) : Stark(n, i, h) {
        weapon = w;
        warriorRank = 1;
    }
    void show() override {
        showinfo();
        std::cout << "Sigil (from Stark): " << sigil << endl;
        std::cout << "Honor: " << honor << endl;
        std::cout << "Weapon: " << weapon << endl;
    }
    string getWeapon() { return weapon; }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Starkwarrior") return true;
        return Stark::isKindOf(baseNode);
    }
};

class Targaryen : public Westeros {
protected:
    string hairColor;
private:
    int dragons;
public:
    Targaryen(string n, int i, int d) : Westeros(n, i) {
        dragons = d;
        hairColor = "Silver";
    }
    int getDragons() { return dragons; }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Targaryen") return true;
        return Westeros::isKindOf(baseNode);
    }
};

class Dragonrider : public Targaryen {
private:
    string dragonname;
protected:
    int flightHours;
public:
    string getType() override { return "Dragonrider"; }
    Dragonrider(string n, int i, string d) : Targaryen(n, i, 1) {
        dragonname = d;
        flightHours = 100;
    }
    string getDragonName() { return dragonname; }
    void show() override {
        showinfo();
        std::cout << "Hair Color (from Targaryen): " << hairColor << endl;
        std::cout << "Dragon: " << dragonname << endl;
    }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Dragonrider") return true;
        return Targaryen::isKindOf(baseNode);
    }
};

class Dragonmaster : public Targaryen {
private:
    string dragonname;
protected:
    int masteryLevel;
public:
    string getType() override { return "Dragonmaster"; }
    Dragonmaster(string n, int i, string d) : Targaryen(n, i, 0) {
        dragonname = d;
        masteryLevel = 10;
    }
    string getDragonName() { return dragonname; }
    void show() override {
        showinfo();
        std::cout << "Hair Color (from Targaryen): " << hairColor << endl;
        std::cout << "Dragon: " << dragonname << endl;
    }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Dragonmaster") return true;
        return Targaryen::isKindOf(baseNode);
    }
};

class Baratheon : public Westeros {
protected:
    string motto;
private:
    int army;
public:
    Baratheon(string n, int i) : Westeros(n, i) {
        army = 1000;
        motto = "Ours is the Fury";
    }
    int getArmy() { return army; }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Baratheon") return true;
        return Westeros::isKindOf(baseNode);
    }
};

class Baratheonknight : public Baratheon {
private:
    string weapon;
protected:
    bool hasShield;
public:
    string getType() override { return "Baratheonknight"; }
    Baratheonknight(string n, int i, string w) : Baratheon(n, i) {
        weapon = w;
        hasShield = true;
    }
    string getWeapon() { return weapon; }
    void show() override {
        showinfo();
        std::cout << "Motto (from Baratheon): " << motto << endl;
        std::cout << "Weapon: " << weapon << endl;
    }
    bool isKindOf(string baseNode) override {
        if (baseNode == "Baratheonknight") return true;
        return Baratheon::isKindOf(baseNode);
    }
};

bool isLeaf(string node) {
    return (node == "Lannister" || node == "Starkwarrior" ||
        node == "Dragonrider" || node == "Dragonmaster" || node == "Baratheonknight");
}
bool isIdUnique(const vector<Westeros*>& all, int id) {
    for (auto* x : all) {
        if (x->getId() == id) {
            return false; 
        }
    }
    return true; 
}

int main()
{
    vector<Westeros*> all;
    string currentNode = "Westeros";
    string command;

    while (true) {
        std::cout << "\n[Current Node: " << currentNode << "]\n";
        std::cout << "Command: ";
        std::cin >> command;

        if (command == "MO") {
            if (!isLeaf(currentNode)) {
                std::cout << "Error: You can only add objects to LEAF nodes!\n";
                continue;
            }
            std::string name;
            int id;
            std::cout << "Enter name and id: ";
            std::cin >> name >> id;
            if (!isIdUnique(all, id)) {
                std::cout << "Error: Object with ID " << id << " already exists! Try another ID.\n";
                continue;
            }
            if (currentNode == "Lannister") {
                int wealth;
                std::cout << "Enter wealth (gold): ";
                std::cin >> wealth;
                all.push_back(new Lannister(name, id, wealth));
            }
            else if (currentNode == "Starkwarrior") {
                int honor;
                std::string weapon;
                std::cout << "Enter honor and weapon: ";
                std::cin >> honor >> weapon;
                all.push_back(new Starkwarrior(name, id, honor, weapon));
            }
            else if (currentNode == "Dragonrider") {
                std::string dragon;
                std::cout << "Enter dragon name: ";
                std::cin >> dragon;
                all.push_back(new Dragonrider(name, id, dragon));
            }
            else if (currentNode == "Dragonmaster") {
                std::string dragon;
                std::cout << "Enter dragon name: ";
                std::cin >> dragon;
                all.push_back(new Dragonmaster(name, id, dragon));
            }
            else if (currentNode == "Baratheonknight") {
                std::string weapon;
                std::cout << "Enter weapon: ";
                std::cin >> weapon;
                all.push_back(new Baratheonknight(name, id, weapon));
            }
            std::cout << "Character added!\n";
        }

        else if (command == "MDO") {
            if (!isLeaf(currentNode)) {
                std::cout << "Error: You can only modify objects in LEAF nodes!\n";
                continue;
            }
            std::string searchedName;
            std::cout << "Enter name of the character to modify: ";
            std::cin >> searchedName;

            bool found = false;
            for (int i = 0; i < (int)all.size(); i++) {
                if (all[i]->getName() == searchedName && all[i]->getType() == currentNode) {
                    found = true;
                    std::cout << "Character found! Enter NEW data.\n";

                    std::string newName;
                    int newId;
                    std::cout << "Enter new name and new id: ";
                    std::cin >> newName >> newId;

                    if (currentNode == "Lannister") {
                        int newWealth;
                        std::cout << "Enter new wealth (gold): ";
                        std::cin >> newWealth;
                        delete all[i];
                        all[i] = new Lannister(newName, newId, newWealth);
                    }
                    else if (currentNode == "Starkwarrior") {
                        int newHonor;
                        std::string newWeapon;
                        std::cout << "Enter new honor and new weapon: ";
                        std::cin >> newHonor >> newWeapon;
                        delete all[i];
                        all[i] = new Starkwarrior(newName, newId, newHonor, newWeapon);
                    }
                    else if (currentNode == "Dragonrider") {
                        std::string newDragon;
                        std::cout << "Enter new dragon name: ";
                        std::cin >> newDragon;
                        delete all[i];
                        all[i] = new Dragonrider(newName, newId, newDragon);
                    }
                    else if (currentNode == "Dragonmaster") {
                        std::string newDragon;
                        std::cout << "Enter new dragon name: ";
                        std::cin >> newDragon;
                        delete all[i];
                        all[i] = new Dragonmaster(newName, newId, newDragon);
                    }
                    else if (currentNode == "Baratheonknight") {
                        std::string newWeapon;
                        std::cout << "Enter new weapon: ";
                        std::cin >> newWeapon;
                        delete all[i];
                        all[i] = new Baratheonknight(newName, newId, newWeapon);
                    }
                    std::cout << "Character modified successfully!\n";
                    break;
                }
            }
            if (!found) std::cout << "Character not found for the current node!\n";
        }

        else if (command == "DO") {
            if (!isLeaf(currentNode)) {
                std::cout << "Error: You can only delete objects from LEAF nodes!\n";
                continue;
            }
            std::string searchedName;
            std::cout << "Enter name to delete: ";
            std::cin >> searchedName;

            bool found = false;
            for (int i = 0; i < (int)all.size(); i++) {
                if (all[i]->getName() == searchedName && all[i]->getType() == currentNode) {
                    delete all[i];
                    all.erase(all.begin() + i);
                    std::cout << "Character deleted!\n";
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "Character not found!\n";
        }

        else if (command == "DIR") {
            std::cout << "Objects visible from node [" << currentNode << "]:\n";
            bool anyVisible = false;
            for (auto* x : all) {
                if (x->isKindOf(currentNode)) {
                    std::cout << "- " << x->getName() << " (" << x->getType() << ")\n";
                    anyVisible = true;
                }
            }
            if (!anyVisible) std::cout << "(No objects visible)\n";
        }

        else if (command == "FIND" || command == "SHOW") {
            std::string searchedName;
            std::cout << "Enter name to show: ";
            std::cin >> searchedName;

            bool found = false;
            for (auto* x : all) {
                if (x->getName() == searchedName) {
                    x->show();
                    found = true;
                }
            }
            if (!found) std::cout << "Character not found!\n";
        }

        else if (command == "CD") {
            std::string node;
            std::cout << "Enter new node type: ";
            std::cin >> node;

            if (node == "Westeros" || node == "Lannister" || node == "Stark" ||
                node == "Starkwarrior" || node == "Targaryen" || node == "Dragonrider" ||
                node == "Dragonmaster" || node == "Baratheon" || node == "Baratheonknight") {
                currentNode = node;
                std::cout << "Changed node to: " << currentNode << "\n";
            }
            else {
                std::cout << "Invalid node!\n";
            }
        }

        else if (command == "TREE") {
            std::cout << "\nStructure of Westeros classes:\n";
            std::cout << "Westeros" << (currentNode == "Westeros" ? " <-- [CURRENT]" : "") << "\n";
            std::cout << "  |-- Lannister" << (currentNode == "Lannister" ? " <-- [CURRENT] (LEAF)" : " (LEAF)") << "\n";
            std::cout << "  |-- Stark" << (currentNode == "Stark" ? " <-- [CURRENT]" : "") << "\n";
            std::cout << "  |     |-- Starkwarrior" << (currentNode == "Starkwarrior" ? " <-- [CURRENT] (LEAF)" : " (LEAF)") << "\n";
            std::cout << "  |-- Targaryen" << (currentNode == "Targaryen" ? " <-- [CURRENT]" : "") << "\n";
            std::cout << "  |     |-- Dragonrider" << (currentNode == "Dragonrider" ? " <-- [CURRENT] (LEAF)" : " (LEAF)") << "\n";
            std::cout << "  |     |-- Dragonmaster" << (currentNode == "Dragonmaster" ? " <-- [CURRENT] (LEAF)" : " (LEAF)") << "\n";
            std::cout << "  `-- Baratheon" << (currentNode == "Baratheon" ? " <-- [CURRENT]" : "") << "\n";
            std::cout << "        |-- Baratheonknight" << (currentNode == "Baratheonknight" ? " <-- [CURRENT] (LEAF)" : " (LEAF)") << "\n";
        }

        else if (command == "SAVE") {
            std::ofstream file("data.txt");
            for (auto* x : all) {
                std::string type = x->getType();
                file << type << " " << x->getName() << " " << x->getId() << " ";

                if (type == "Lannister") {
                    file << dynamic_cast<Lannister*>(x)->getWealth();
                }
                else if (type == "Starkwarrior") {
                    auto* sw = dynamic_cast<Starkwarrior*>(x);
                    file << sw->getHonor() << " " << sw->getWeapon();
                }
                else if (type == "Dragonrider")
                    file << dynamic_cast<Dragonrider*>(x)->getDragonName();
                else if (type == "Dragonmaster")
                    file << dynamic_cast<Dragonmaster*>(x)->getDragonName();
                else if (type == "Baratheonknight")
                    file << dynamic_cast<Baratheonknight*>(x)->getWeapon();

                file << "\n";
            }
            std::cout << "Saved!\n";
        }

        else if (command == "READ") {
            std::ifstream file("data.txt");
            if (!file) {
                std::cout << "No save file found!\n";
                continue;
            }

            for (auto* x : all) delete x;
            all.clear();

            std::string type;
            while (file >> type) {
                std::string name;
                int id;
                file >> name >> id;
				
                if (type == "Lannister") {
                    int wealth;
                    file >> wealth;
                    all.push_back(new Lannister(name, id, wealth));
                }
                else if (type == "Starkwarrior") {
                    int honor;
                    std::string weapon;
                    file >> honor >> weapon;
                    all.push_back(new Starkwarrior(name, id, honor, weapon));
                }
                else if (type == "Dragonrider") {
                    std::string dragon;
                    file >> dragon;
                    all.push_back(new Dragonrider(name, id, dragon));
                }
                else if (type == "Dragonmaster") {
                    std::string dragon;
                    file >> dragon;
                    all.push_back(new Dragonmaster(name, id, dragon));
                }
                else if (type == "Baratheonknight") {
                    std::string weapon;
                    file >> weapon;
                    all.push_back(new Baratheonknight(name, id, weapon));
                }
            }
            std::cout << "Loaded!\n";
        }

        else if (command == "EXIT") {
            for (auto* x : all) delete x;
            break;
        }
    }
    return 0;
}
