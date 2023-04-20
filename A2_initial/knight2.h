#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseKnight;
class BaseBag;
class BaseItem;

enum ItemType {ANTIDOTE, PHOENIXDOWN1, PHOENIXDOWN2, PHOENIXDOWN3, PHOENIXDOWN4, NO_ITEM = -1};

class BaseBag {
public:
    BaseKnight * knight;
    int phoenixdown1; //number of phoenixdown1 in the bag
    int antidote; // number of antidote in the bag
    ItemType * space; //item inside the bag
    int sp; //total number of space
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};


class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    //BaseBag * bag;
    KnightType knightType;

public:
    BaseBag * bag;
    bool isALive; //show if knight is alive
    bool isPoisoned; //show if knight is poisoned
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    void modifyStat(); //method to access and modify stat
};

class PaladinKnight: public BaseKnight {

};

class DragonKnight: public BaseKnight {

};

class LancelotKnight: public BaseKnight {

};

class NormalKnight: public BaseKnight {

};


class PKnightBag: public BaseBag {
public:

    PKnightBag(BaseKnight * knight, int phoenixdown1, int antidote);
    //string toString() const;
};

class LKnightBag: public BaseBag {
public:

    LKnightBag(BaseKnight * knight, int phoenixdown1, int antidote);
    //string toString() const;
};

class DKnightBag: public BaseBag {
public:

    DKnightBag(BaseKnight * knight, int phoenixdown1, int antidote);
    //string toString() const;
};

class NKnightBag: public BaseBag {
public:

    NKnightBag(BaseKnight * knight, int phoenixdown1, int antidote);
    //string toString() const;
};

class ArmyKnights {
public:
    BaseKnight * array_of_knights;
    BaseBag** armybag;
    int num;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    //bool fight(BaseOpponent * opponent);
    //bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    //bool hasPaladinShield() const;
    //bool hasLancelotSpear() const;
    //bool hasGuinevereHair() const;
    //bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    ItemType itemtype;
    //virtual bool canUse ( BaseKnight * knight ) = 0;
    //virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote: public BaseItem {
public:
    Antidote(){ //constructor for item
        itemtype = ANTIDOTE;
    }
};

class Phoenixdown1: public BaseItem {
public:
    Phoenixdown1(){ //constructor for item
        itemtype = PHOENIXDOWN1;
    }
};

class Phoenixdown2: public BaseItem {
public:
    Phoenixdown2(){ //constructor for item
        itemtype = PHOENIXDOWN2;
    }
};

class Phoenixdown3: public BaseItem {
public:
    Phoenixdown3(){ //constructor for item
        itemtype = PHOENIXDOWN3;
    }
};

class Phoenixdown4: public BaseItem {
public:
    Phoenixdown4(){ //constructor for item
        itemtype = PHOENIXDOWN4;
    }
};

class NoItem: public BaseItem {
public:
    NoItem(){ //constructor for item
        itemtype = NO_ITEM;
    }
};

class Events {
public:
    int num_of_events;
    int * arr_of_events;
    Events(const string & file_events);
    ~Events(){
        delete[] arr_of_events;
    }
    int count() const;
    int get(int i) const{
        return arr_of_events[i];
    }
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(){
        delete[] armyKnights;
        delete[] events;
    }; // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

//function to split string with a seperator
int len(string str);

void split(string str, char seperator, string arr[]);

bool isPrime(int num);

bool isPythagoras(int n);
#endif // __KNIGHT2_H__