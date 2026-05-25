#include <algorithm>
#include <iostream>
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
};
class Dragonrider : public Targaryen {
private:
    string dragonname;
};
class Dragonmaster : public Targaryen {
private:
    string dragonname;
};
class Baratheon : public Westeros {
    private:
    int army;
};
class Baratheonknight : public Baratheon {  
private:
    string weapon;
};
int main()
{
    Starkwarrior jon("Jon Snow", 1, 100, "Longclaw");
    jon.showWarrior();
    return 0;
}

