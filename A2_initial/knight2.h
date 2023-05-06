#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseKnight;
class BaseBag;
class BaseItem;
class Events;

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

enum OpponentType {MADBEAR = 1, BANDIT = 2, LORDLUPIN = 3, ELF = 4, TROLL = 5, TORNBERY = 6, QUEEN = 7, OMEGA = 9, HADES = 11, ULTIMECIA = 99};
class BaseOpponent{
protected:
    int dmg;
    int level;
    int gil_reward;
    OpponentType opponent_type;
public:
    void modifyStat();
    void modifyLevel(int event_counter, Events * event);
    OpponentType get_type(){
        return opponent_type;
    }
    int get_gil(){
        return gil_reward;
    }
    int get_level(){
        return level;
    }
    int get_dmg(){
        return dmg;
    }
};

class MadBear: public BaseOpponent {
public:
    MadBear(){ 
        dmg = 10;
        gil_reward = 100;
        opponent_type = MADBEAR;
    }
};

class Troll: public BaseOpponent {
public:
    Troll(){ 
        dmg = 95;
        gil_reward = 800;
        opponent_type = TROLL;
    }
};

class Bandit: public BaseOpponent {
public:
    Bandit(){ 
        dmg = 15;
        gil_reward = 150;
        opponent_type = BANDIT;
    }
};

class LordLupin: public BaseOpponent {
public:
    LordLupin(){ 
        dmg = 45;
        gil_reward = 450;
        opponent_type = LORDLUPIN;
    }
};

class Elf: public BaseOpponent {
public:
    Elf(){ 
        dmg = 75;
        gil_reward = 750;
        opponent_type = ELF;
    }
};

class Tornbery: public BaseOpponent {
public:
    Tornbery(){

        opponent_type = TORNBERY;
    }
};

class Queen_of_Cards: public BaseOpponent {
public: 
    Queen_of_Cards(){
        opponent_type = QUEEN;
    }
};

class Omega: public BaseOpponent {
public:
    Omega(){
        opponent_type = OMEGA;
    }
};

class Hades: public BaseOpponent {
public:
    Hades(){
        opponent_type = HADES;
    }
};

class Ultimecia: public BaseOpponent {
public:
    Ultimecia(){
        opponent_type = ULTIMECIA;
    }
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    
    float base_damage;
    bool isALive; //show if knight is alive
    bool isPoisoned; //show if knight is poisoned
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    BaseBag * get_bag(){
        return bag;
    }
    KnightType get_knightType(){
        return knightType;
    }
    void reward_gil(int reward){
        gil += reward;
    }
    void modify_gil(int new_gil){
        gil = new_gil;
    }
    int get_gil(){
        return gil;
    }
    bool gil_check(){
        if (gil > 999){
            return true; //return true if gil > 999;
        }
        return false;
    }
    int get_level(){
        return level;
    }
    void modify_hp(int new_hp){
        hp = new_hp;
    }
    int get_hp(){
        return hp;
    }
    void modify_level(int new_level){
        level = new_level;
        if (level >= 10) level = 10;
    }
    int get_maxhp(){
        return maxhp;
    }
    bool check_bag(){
        if (bag->space[bag->sp-1] != NO_ITEM) return false;
        return true;
    }
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
protected:
    bool PaladinShield;
    bool LancelotSpear;
    bool GuinevereHair;
    bool ExcaliburSword;
public:
    BaseKnight * array_of_knights;
    BaseBag** armybag;
    int num;
    int nok;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const{
        if(PaladinShield) return true;
        return false;
    }
    bool hasLancelotSpear() const{
        if(LancelotSpear) return true;
        return false;
    }
    bool hasGuinevereHair() const{
        if(GuinevereHair) return true;
        return false;
    }
    bool hasExcaliburSword() const{
        if(ExcaliburSword) return true;
        return false;
    }

    void get_PaladinShield(){
        PaladinShield = 1;
    }

    void get_LancelotSpear(){
        LancelotSpear = 1;
    }

    void get_GH(){
        GuinevereHair = 1;
    }

    void get_Ex(){
        ExcaliburSword = 1;
    }

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

bool transfer_gil(BaseKnight *& arr_of_knight, int num);

bool transfer_item(BaseKnight *& arr_of_knight, int num, BaseItem * item);

void shift_item_3(BaseBag * bag);

bool found_antidote(BaseBag * bag);

void use_item(BaseBag * bag, ItemType item_to_use);

bool find_phoenixdown1(BaseBag * bag);
bool find_phoenixdown2(BaseBag * bag);
bool find_phoenixdown3(BaseBag * bag);
bool find_phoenixdown4(BaseBag * bag);



#endif // __KNIGHT2_H__