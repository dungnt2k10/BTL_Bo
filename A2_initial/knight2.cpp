#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

string BaseBag::toString() const{
    string item[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    string s("");
    int number_of_owned_item = 0;
    for (int i = 0; i < sp; i++){
        if (space[i] == NO_ITEM) break;
        number_of_owned_item++;
    }
    s += "Bag[count=" + to_string(number_of_owned_item);
    s+= ";";
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
        for (int i = 0; i < antidote; i++){
            this->space[i] = ANTIDOTE; //add antidote to the bag
        }
        for (int i = antidote; i < phoenixdown1 + antidote; i++){
            this->space[i] = PHOENIXDOWN1; //add phoenixdown1 to the bag
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
        for (int i = 0; i < antidote; i++){
            this->space[i] = ANTIDOTE; //add antidote to the bag
        }
        for (int i = antidote; i < phoenixdown1 + antidote; i++){
            this->space[i] = PHOENIXDOWN1; //add phoenixdown1 to the bag
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
        for (int i = 0; i < antidote; i++){
            this->space[i] = ANTIDOTE; //add antidote to the bag
        }
        for (int i = antidote; i < phoenixdown1 + antidote; i++){
            this->space[i] = PHOENIXDOWN1; //add phoenixdown1 to the bag
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
        temp->base_damage = 0.06;

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
        temp->base_damage = 0.05;

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
        temp->base_damage = 0.075;

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
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl; 
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE");
}

int ArmyKnights::count() const{
    return this->nok;
}

ArmyKnights::ArmyKnights(const string& file_armyknights){
    ifstream file;
    file.open(file_armyknights, ifstream::in);
    string number_of_knights = "";
    getline(file, number_of_knights); // get number of knights to create
    nok = stoi(number_of_knights);
    num = nok - 1;
    array_of_knights = new BaseKnight[nok]; //create an array to store 
    int id = 1;
    BaseKnight new_knight;
    string temp = "";
    string arr[5];
    int attr[5];
    for (int i = 0; i < nok; i++){ // create and load parameter to knights
        getline(file, temp);
        split(temp, ' ', arr);
        for (int j = 0; j < 5; j++) attr[j] = stoi(arr[j]); //convert string to int
        this->array_of_knights[i]=*new_knight.create(id, attr[0], attr[1], attr[3], attr[4], attr[2]); //create new knight with new attribute using base knight

        id++;
    }
    PaladinShield = 0;
    LancelotSpear = 0;
    GuinevereHair = 0;
    ExcaliburSword = 0;
    met_hades = 0;
    met_omega = 0;
    ultimecia_hp = 5000;
    win = 0;
    event_counter = 0;
    file.close();
}

//ArmyKnights::~ArmyKnights(){
    //delete[] array_of_knights;
//}

BaseKnight * ArmyKnights::lastKnight() const {
    if (!array_of_knights[0].isALive) return nullptr; //no last knight return null
    return array_of_knights+num; //return pointer to the last knight
}

bool ArmyKnights::fight(BaseOpponent * opponent){
    if ((num == 0 && array_of_knights[num].get_hp() <= 0) || lastKnight() == nullptr){
        nok = 0;
        return false;
    }
    if (opponent->get_type() == 1 || opponent->get_type() == 2 || opponent->get_type() == 3 || opponent->get_type() == 4 || opponent->get_type() == 5){
        if(array_of_knights[num].get_knightType() == LANCELOT || array_of_knights[num].get_knightType() == PALADIN || array_of_knights[num].get_level() >= opponent->get_level()){
            array_of_knights[num].reward_gil(opponent->get_gil());
            //if(!transfer_gil(array_of_knights, num)) return true;
            //else cout << "failed to transfer gil" << endl;
            if(!transfer_gil(array_of_knights,num)) return true;
            return true;
        }
        else {
            if (array_of_knights[num].get_level() < opponent->get_level()){
                int new_hp = array_of_knights[num].get_hp() - opponent->get_dmg() * (opponent->get_level()-array_of_knights[num].get_level());
                array_of_knights[num].modify_hp(new_hp);
            }
        }
    }
    if (opponent->get_type() == ULTIMECIA){
        //has excalibur
        if (hasExcaliburSword()){
            win = 1;
            return true;
        }
        else{
            
            //fight ultimecia 
            if ((hasGuinevereHair() && hasLancelotSpear()) && hasPaladinShield()){
                if (array_of_knights[num].get_knightType() == NORMAL){ //skip normal
                    if (num == 0){
                        nok = 0;
                        return false;
                    }
                    num -= 1;
                    return fight(opponent);
                }
                else if (num == 0 && array_of_knights[num].get_knightType() == NORMAL){
                    nok = 0;
                    return false;
                }
                else{
                    ultimecia_hp -= array_of_knights[num].get_hp() * array_of_knights[num].get_level() * array_of_knights[num].base_damage;
                    if (ultimecia_hp > 0){
                        array_of_knights[num].modify_hp(0);
                        num -= 1;
                        nok -= 1;
                        array_of_knights[num].isALive = 0;
                        return fight(opponent);
                        
                    }
                    else{
                        win = 1;
                        return true;
                    }
                }
            } 

            //dont have excalibur or dont have 3 needed items
            if (!hasGuinevereHair() || !hasLancelotSpear() || !hasPaladinShield()){
                nok = 0;
                array_of_knights[0].modify_hp(0);
                array_of_knights[0].isALive = 0;
                return false;
            }
        }
    }
    if (opponent->get_type() == 6){
        if (array_of_knights[num].get_level() < opponent->get_level()){
            bool have_antidote = found_antidote(array_of_knights[num].get_bag());
            if (have_antidote){
                use_item(array_of_knights[num].get_bag(),ANTIDOTE);
            }
            if (array_of_knights[num].get_knightType() != DRAGON && !have_antidote){
                int new_hp = array_of_knights[num].get_hp() - 10;
                array_of_knights[num].modify_hp(new_hp);
                shift_item_3(array_of_knights[num].get_bag()); //drop 3 items
            }
        }
        else{
            int new_level = array_of_knights[num].get_level() + 1;
            array_of_knights[num].modify_level(new_level);
            return true;
        }
    }
    if (opponent->get_type() == 7){
        if (array_of_knights[num].get_level() < opponent->get_level()){
            if (array_of_knights[num].get_knightType() != PALADIN){
                int new_gil = array_of_knights[num].get_gil()/2;
                array_of_knights[num].modify_gil(new_gil);
            }
        }
        else{
            int new_gil = array_of_knights[num].get_gil()*2;
            array_of_knights[num].modify_gil(new_gil);
            if(!transfer_gil(array_of_knights,num)) return true;
            return true;
        }
    }
    if (opponent->get_type() == 9){
        if (array_of_knights[num].get_knightType() == DRAGON || (array_of_knights[num].get_level() == 10 && array_of_knights[num].get_hp() == array_of_knights[num].get_maxhp())){
            array_of_knights[num].modify_level(10);
            array_of_knights[num].modify_gil(999);
            return true;
        }
        else {
            array_of_knights[num].modify_hp(0);
        }

    }
    if (opponent->get_type() == 11){
        if (array_of_knights[num].get_level() == 10 || (array_of_knights[num].get_knightType() == PALADIN && array_of_knights[num].get_level() >= 8)){
            get_PaladinShield();
            return true;
        }
        else {
            array_of_knights[num].modify_hp(0);
        }
    }
    if (array_of_knights[num].get_hp() < array_of_knights[num].get_maxhp()/4){
        if (find_phoenixdown2(array_of_knights[num].get_bag())){
            array_of_knights[num].modify_hp(array_of_knights[num].get_maxhp());
            use_item(array_of_knights[num].get_bag(), PHOENIXDOWN2);
        }
    }
    if (array_of_knights[num].get_hp() < array_of_knights[num].get_maxhp()/3){
        if (find_phoenixdown3(array_of_knights[num].get_bag())){
            if (array_of_knights[num].get_hp() <= 0){
                array_of_knights[num].modify_hp(array_of_knights[num].get_maxhp()/3);
                use_item(array_of_knights[num].get_bag(), PHOENIXDOWN3);
            }
            else{
                array_of_knights[num].modify_hp(array_of_knights[num].get_hp()+array_of_knights[num].get_maxhp()/4);
                use_item(array_of_knights[num].get_bag(), PHOENIXDOWN3);
            }
        }
    }
    if (array_of_knights[num].get_hp() < array_of_knights[num].get_maxhp()/2){
        if (find_phoenixdown4(array_of_knights[num].get_bag())){
            if (array_of_knights[num].get_hp() <= 0){
                array_of_knights[num].modify_hp(array_of_knights[num].get_maxhp()/2);
                use_item(array_of_knights[num].get_bag(), PHOENIXDOWN4);
            }
            else{
                array_of_knights[num].modify_hp(array_of_knights[num].get_hp()+array_of_knights[num].get_maxhp()/5);
                use_item(array_of_knights[num].get_bag(), PHOENIXDOWN4);
            }
        }
    }
    if (array_of_knights[num].get_hp() <= 0){
            if (find_phoenixdown1(array_of_knights[num].get_bag())){
                array_of_knights[num].modify_hp(array_of_knights[num].get_maxhp());
                use_item(array_of_knights[num].get_bag(), PHOENIXDOWN1);
            }
            else if (array_of_knights[num].get_gil() >= 100){
                array_of_knights[num].modify_gil(array_of_knights[num].get_gil()-100);
                array_of_knights[num].modify_hp(0.5*array_of_knights[num].get_maxhp());
            }
            else{
                array_of_knights[num].isALive = 0;
                nok -= 1;
                num -= 1;
                return ArmyKnights::fight(opponent); //next knight
            }
    }
    if (array_of_knights[num].get_hp() > 0){
                return true;
    }

}


bool ArmyKnights::adventure (Events * events) {
    switch(events->arr_of_events[event_counter]){
        case 1:{
            BaseOpponent * opponent = new MadBear();
            opponent->modifyLevel(event_counter, events);
            fight(opponent);
            delete[] opponent;
            break;
        }
        case 2:{
            BaseOpponent * opponent = new Bandit();
            opponent->modifyLevel(event_counter, events);
            fight(opponent);
            delete[] opponent;
            break;
        }
        case 3:{
            BaseOpponent * opponent = new LordLupin();
            opponent->modifyLevel(event_counter, events);
            fight(opponent);
            delete[] opponent;
            break;
        }
        case 4:{
            BaseOpponent * opponent = new Elf();
            opponent->modifyLevel(event_counter, events);
            fight(opponent);
            delete[] opponent;
            break;
        }
        case 5:{
            BaseOpponent * opponent = new Troll();
            opponent->modifyLevel(event_counter, events);
            fight(opponent);
            delete[] opponent;
            break;
        }
        case 6:{
            BaseOpponent * opponent = new Tornbery();
            opponent->modifyLevel(event_counter, events);
            fight(opponent);
            delete[] opponent;
            break;
        }
        case 7:{
            BaseOpponent * opponent = new Queen_of_Cards();
            opponent->modifyLevel(event_counter, events);
            fight(opponent);
            delete[] opponent;
            break;
        }
        case 8:
            if (array_of_knights[num].get_knightType() == PALADIN && array_of_knights[num].get_hp() < array_of_knights[num].get_maxhp()/3){
                int new_hp = array_of_knights[num].get_hp() + array_of_knights[num].get_maxhp() * 0.2;
                if (new_hp > array_of_knights[num].get_maxhp()) new_hp = array_of_knights[num].get_maxhp();
                array_of_knights[num].modify_hp(new_hp);
            }
            else if (array_of_knights[num].get_knightType() != PALADIN){
                if (array_of_knights[num].get_hp() < array_of_knights[num].get_maxhp()/3 && array_of_knights[num].get_gil() >= 50){
                    int new_hp = array_of_knights[num].get_hp() + array_of_knights[num].get_maxhp() * 0.2;
                    if (new_hp > array_of_knights[num].get_maxhp()) new_hp = array_of_knights[num].get_maxhp();
                    array_of_knights[num].modify_hp(new_hp);
                    int new_gil = array_of_knights[num].get_gil() - 50;
                    array_of_knights[num].modify_gil(new_gil);
                }
            }
            break;
        case 9: 
            array_of_knights[num].modify_hp(array_of_knights[num].get_maxhp());
            break;
        case 10:{
            if (!met_omega){
            BaseOpponent * opponent = new Omega();
            fight(opponent);
            delete[] opponent;
            met_omega = true;
            }
            break;
        }
        case 11:{
            if (!met_hades){
                BaseOpponent * opponent = new Hades();
                fight(opponent);
                delete[] opponent;
                met_hades = true;
            }
            break;
        }
        case 112:{
            BaseItem * item = new Phoenixdown2();
            transfer_item(array_of_knights, num, item);
            delete[] item;
            break;
        }
        case 113:{
            BaseItem * item = new Phoenixdown3();
            transfer_item(array_of_knights, num, item);
            delete[] item;
            break;
        }
        case 114:{
            BaseItem * item = new Phoenixdown4();
            transfer_item(array_of_knights, num, item);
            delete[] item;
            break;
        }
        case 95:
            get_PaladinShield();
            break;
        case 96:
            get_LancelotSpear();
            break;
        case 97:
            get_GH();
            break;
        case 98:
            if ((hasGuinevereHair() && hasLancelotSpear()) && hasPaladinShield()) get_Ex();
            break;
        case 99:{
            BaseOpponent * opponent = new Ultimecia();
            fight(opponent);
            delete[] opponent;
            break;
        }
    }
    printInfo();
    //cout << "counter: "<< events->arr_of_events[event_counter] << endl;
    //int temp = events->arr_of_events[event_counter];
    //cout << "result: "<< win << endl;
    if (events->arr_of_events[event_counter] == 99){
        printResult(win);
        return true;
    }
    else{ 
        event_counter++;
        //cout << "event counter: "<< event_counter << endl;
        //return false;
        return ArmyKnights::adventure(events);
    }
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
    //armyKnights->printInfo();
    //cout << events->count() << endl; //test load event ok
    //cout << events->get(0) << endl;
    //BaseItem * antidote = new Phoenixdown2();
    //cout << armyKnights->array_of_knights[0].bag->toString();
    //armyKnights->array_of_knights[0].bag->insertFirst(antidote); //test insertfirst ok
    /*for (int i = 0; i<armyKnights->num; i++){
        cout << armyKnights->array_of_knights[i].toString() << endl;
    }*/
    //for (int i = 0; i < events->num_of_events; i++){
    armyKnights->adventure(events);
    //}
    return;
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
        file.close();
}





/* END implementation of class Events*/


/* BEGIN implementation of class Opponent*/
void BaseOpponent::modifyLevel(int event_counter, Events * event){
    int temp = event->get(event_counter);
    level = (event_counter+temp)%10+1;
}

/* END implementation of class Opponent*/


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

bool transfer_gil(BaseKnight *& arr_of_knight, int num){
    int extra_gil = 0;
    if (arr_of_knight[num].gil_check()){
        extra_gil = arr_of_knight[num].get_gil() - 999;
        arr_of_knight[num].modify_gil(999);
        if (num == 0) return false; //stop transfer if lastknight
        arr_of_knight[num-1].modify_gil(arr_of_knight[num-1].get_gil()+extra_gil); //give extra gil to next knight
        return transfer_gil(arr_of_knight, num-1); //continue checking
    }
    else return false; //stop when gil < 999
}

bool transfer_item(BaseKnight *& arr_of_knight, int num, BaseItem * item){
    if (arr_of_knight[num].check_bag()){
        arr_of_knight[num].get_bag()->insertFirst(item);
        return true;
    }
    else if (num == 0 && !arr_of_knight[num].check_bag()){
        return false;
    }
    else{
        return transfer_item(arr_of_knight, num - 1, item);
    }
}

void shift_item_3(BaseBag * bag){//drop 3 items
    bag->space[0] = NO_ITEM;
    bag->space[1] = NO_ITEM;
    bag->space[2] = NO_ITEM;
    for (int i = 0; i < bag->sp - 2; i++){
        bag->space[i] = bag->space[i+3];
        if (i>=3 && bag->space[i] == NO_ITEM) break;
    }
    bag->space[bag->sp-1] = NO_ITEM;
    bag->space[bag->sp-2] = NO_ITEM;
    bag->space[bag->sp-3] = NO_ITEM;

}

bool found_antidote(BaseBag * bag){
    for (int i = 0; i < bag->sp; i++){
        if (bag->space[i] == ANTIDOTE) return true;
    }
    return false;
}

bool find_phoenixdown1(BaseBag * bag){
    for (int i  = 0; i < bag->sp; i++){
        if (bag->space[i] == PHOENIXDOWN1) return true;
    }
    return false;
}

bool find_phoenixdown2(BaseBag * bag){
    for (int i  = 0; i < bag->sp; i++){
        if (bag->space[i] == PHOENIXDOWN2) return true;
    }
    return false;
}

bool find_phoenixdown3(BaseBag * bag){
    for (int i  = 0; i < bag->sp; i++){
        if (bag->space[i] == PHOENIXDOWN3) return true;
    }
    return false;
}

bool find_phoenixdown4(BaseBag * bag){
    for (int i  = 0; i < bag->sp; i++){
        if (bag->space[i] == PHOENIXDOWN4) return true;
    }
    return false;
}

void use_item(BaseBag * bag, ItemType item_to_use){
    ItemType temp;
    temp = bag->space[0];
    for (int i = 0; i < bag->sp; i++){
        if (bag->space[i] == item_to_use){
            bag->space[i] = temp;
            break; //switch item
        }
    }
    for (int i = 0; i < bag->sp - 1; i++){
        bag->space[i] = bag->space[i+1]; //switch item to the left
    }
    bag->space[bag->sp-1] = NO_ITEM;
}

