#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

string BaseBag::toString() const{
    string item[5] = {"Antidote", "PhoenixdownI", "PhoenixdownII", "PhoenixdownIII", "PhoenixdownIV"};
    string s("");
    int number_of_owned_item = 0;
    for (int i = 0; i < sp; i++){
        if (space[i] == NO_ITEM) break;
        number_of_owned_item++;
    }
    s += "Bag[count=" + to_string(number_of_owned_item);
    if (number_of_owned_item > 0) s+= ";";
    for (int i = 0; i < sp; i++){
        if (space[i] == NO_ITEM) break;
        if (space[i+1] == NO_ITEM) s += item[space[i]];
        else s += item[space[i]] + ",";
    }
    s += "]";
    return s;

}

PKnightBag::PKnightBag(BaseKnight * knight, int phoenixdown1, int antidote){
        this->knight = knight;
        this->phoenixdown1 = phoenixdown1;
        this->antidote = antidote;
        this->space = new ItemType[99]; // paladin bag has infinite space
        this->sp = 99;
        for (int i = 0; i < this->sp; i++){
            this->space[i] = NO_ITEM; //put no item in the bag
        }
        for (int i = 0; i < phoenixdown1; i++){
            this->space[i] = PHOENIXDOWN1; //add phoenixdown1 to the bag
        }
        for (int i = phoenixdown1; i < phoenixdown1 + antidote; i++){
            this->space[i] = ANTIDOTE; //add antidote to the bag
        }
}

LKnightBag::LKnightBag(BaseKnight * knight, int phoenixdown1, int antidote){
        this->knight = knight;
        this->phoenixdown1 = phoenixdown1;
        this->antidote = antidote;
        this->space = new ItemType[16]; // lancelot bag has 16 space
        this->sp = 16;
        for (int i = 0; i < this->sp; i++){
            this->space[i] = NO_ITEM; //put no item in the bag
        }
        for (int i = 0; i < phoenixdown1; i++){
            this->space[i] = PHOENIXDOWN1; //add phoenixdown1 to the bag
        }
        for (int i = phoenixdown1; i < phoenixdown1 + antidote; i++){
            this->space[i] = ANTIDOTE; //add antidote to the bag
        }
}

DKnightBag::DKnightBag(BaseKnight * knight, int phoenixdown1, int antidote){
        this->knight = knight;
        this->phoenixdown1 = phoenixdown1;
        this->antidote = 0;
        this->space = new ItemType[14]; // dragon bag 14 space
        this->sp = 14;
        for (int i = 0; i < this->sp; i++){
            this->space[i] = NO_ITEM; //put no item in the bag
        }
        for (int i = 0; i < phoenixdown1; i++){
            this->space[i] = PHOENIXDOWN1; //add phoenixdown1 to the bag
        }
}

NKnightBag::NKnightBag(BaseKnight * knight, int phoenixdown1, int antidote){
        this->knight = knight;
        this->phoenixdown1 = phoenixdown1;
        this->antidote = antidote;
        this->space = new ItemType[19]; // normal bag has 19 space
        this->sp = 19;
        for (int i = 0; i < this->sp; i++){
            this->space[i] = NO_ITEM; //put no item in the bag
        }
        for (int i = 0; i < phoenixdown1; i++){
            this->space[i] = PHOENIXDOWN1; //add phoenixdown1 to the bag
        }
        for (int i = phoenixdown1; i < phoenixdown1 + antidote; i++){
            this->space[i] = ANTIDOTE; //add antidote to the bag
        }
}

bool BaseBag::insertFirst(BaseItem * item){
    for (int i = 0; i < sp; i++){
        if (space[i] == NO_ITEM){
            for (int k = i; k > 0; k--){
                space[k] = space[k-1]; //shift one item to the right
            }
            space[0] = item->itemtype; //add new item to the beginning of the bag
            return true;
        }
    }
    return false; //return false if bag is full
}

BaseItem * BaseBag::get(ItemType item){
    ItemType temp;
    bool haveItem = false;
    for (int i = 0; i < sp; i++){
        if (space[i] == item){
            temp = item;
            haveItem = true;
            break;
        }
    }
    if (!haveItem) return nullptr;
    
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

//method to create new knight
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    
    if (isPrime(maxhp)){ //create paladin

        PaladinKnight * temp = new PaladinKnight();

        temp->id = id;
        temp->hp = maxhp;
        temp->maxhp = maxhp;
        temp->level = level;
        temp->gil = gil;
        temp->antidote = antidote;
        temp->knightType = PALADIN;
        temp->isALive = true;
        temp->isPoisoned = false;
        temp->bag = new PKnightBag(temp, phoenixdownI, antidote);
        
        return temp;
    }
    else if (maxhp == 888){ //create lancelot
        LancelotKnight * temp = new LancelotKnight();
        temp->id = id;
        temp->hp = maxhp;
        temp->maxhp = maxhp;
        temp->level = level;
        temp->gil = gil;
        temp->antidote = antidote;
        temp->knightType = LANCELOT;
        temp->isALive = true;
        temp->isPoisoned = false;

        temp->bag = new LKnightBag(temp, phoenixdownI, antidote); 

        return temp;
    }
    else if (isPythagoras(maxhp)) { //create dragonknight
        DragonKnight * temp = new DragonKnight();
        temp->id = id;
        temp->hp = maxhp;
        temp->maxhp = maxhp;
        temp->level = level;
        temp->gil = gil;
        temp->antidote = 0;
        temp->knightType = DRAGON;
        temp->isALive = true;
        temp->isPoisoned = false;

        temp->bag = new DKnightBag(temp, phoenixdownI, antidote);

        return temp;
    }
    else { //create normal
        NormalKnight * temp = new NormalKnight();
        temp->id = id;
        temp->hp = maxhp;
        temp->maxhp = maxhp;
        temp->level = level;
        temp->gil = gil;
        temp->antidote = antidote;
        temp->knightType = NORMAL;
        temp->isALive = true;
        temp->isPoisoned = false;

        temp->bag = new NKnightBag(temp, phoenixdownI, antidote);

        return temp;
    }

}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
      if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString() << endl;
    }
    /*cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl; */
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

int ArmyKnights::count() const{
    return this->num;
}

ArmyKnights::ArmyKnights(const string& file_armyknights){
    ifstream file;
    file.open(file_armyknights, ifstream::in);
    string number_of_knights = "";
    getline(file, number_of_knights); // get number of knights to create
    num = stoi(number_of_knights);
    array_of_knights = new BaseKnight[num]; //create an array to store 
    int id = 1;
    BaseKnight new_knight;
    string temp = "";
    string arr[5];
    int attr[5];
    armybag = new BaseBag * [num];
    for (int i = 0; i < num; i++){ // create and load parameter to knights
        getline(file, temp);
        split(temp, ' ', arr);
        for (int j = 0; j < 5; j++) attr[j] = stoi(arr[j]); //convert string to int
        this->array_of_knights[i]=*new_knight.create(id, attr[0], attr[1], attr[3], attr[4], attr[2]); //create new knight with new attribute using base knight

        id++;
    }
    file.close();
}

ArmyKnights::~ArmyKnights(){
    delete[] array_of_knights;
}

BaseKnight * ArmyKnights::lastKnight() const {
    if (!array_of_knights[0].isALive) return nullptr; //no last knight return null
    return array_of_knights; //return pointer to the last knight
}


/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string& file_name){
    armyKnights = new ArmyKnights(file_name);
}

void KnightAdventure::loadEvents(const string& file_name){
    events = new Events(file_name);
}

void KnightAdventure::run(){
    armyKnights->printInfo();
    //cout << events->count() << endl; //test load event ok
    //cout << events->get(0) << endl;
    //BaseItem * antidote = new Phoenixdown2();
    //cout << armyKnights->array_of_knights[0].bag->toString();
    //armyKnights->array_of_knights[0].bag->insertFirst(antidote); //test insertfirst ok
    for (int i = 0; i<armyKnights->num; i++){
        cout << armyKnights->array_of_knights[i].toString() << endl;
    }
}

/* * * END implementation of class KnightAdventure * * */

/* BEGIN implementation of class Events*/

int Events::count() const{
    return num_of_events;
}

Events::Events(const string & file_events){
        ifstream file;
        file.open(file_events, ifstream::in);
        string temp = "";
        getline(file, temp);
        num_of_events = stoi(temp);
        string arr_temp[1024];
        arr_of_events = new int[num_of_events];
        getline(file, temp);
        split(temp,' ',arr_temp);
        for (int i = 0; i < num_of_events; i++){
            arr_of_events[i] = stoi(arr_temp[i]);
        }
}





/* END implementation of class Events*/

int len(string str){
    int length = 0;
    for (int i =0; str[i] != '\0'; i++){
        length++;
    }
    return length;
}

void split(string str, char seperator, string arr[]){
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= len(str)){
        if (str[i] == seperator || i == len(str)){
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            arr[currIndex] = subStr;
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
}

bool isPrime(int num){
    bool check = 1;
    if (num == 0 || num == 1){
        check = 0;
    }
    for (int i = 2; i < num/2; i++){
        if (num % i == 0){
            check = 0;
            break;
        }
    }
    return check;
}

bool isPythagoras(int n){
    int a, b, c;
    if (n<100) return false;
    a = n/100 %10;
    b = n/10 %10;
    c = n%10;
    if ((a*a + b*b == c*c) || (a*a + c*c == b*b) || (b*b + c*c == a*a)) return true;
    else return false;
}