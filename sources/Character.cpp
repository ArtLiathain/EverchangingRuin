#include "../headers/Character.h"

Character::Character(string description) {
	this->description = description;
    this->currentForm = "human";
    availableForms.push_back("human");
    availableForms.push_back("meerkat");
    availableForms.push_back("bee");
    availableForms.push_back("lobster");
    availableForms.push_back("elephant");
}
void Character::addItems(Item *item) {
    itemsInCharacter.push_back(item);
}
void Character::putItems(Item *item) {
    int location = getItemIndex(item);
    if (location == -1){
        cout << "you don't have the item" << endl;
    }
    else{
    itemsInCharacter.erase(itemsInCharacter.begin()+location);
    }
}

int Character::getItemIndex(Item *item){
    string name = item->getShortDescription();
    int size = itemsInCharacter.size();
    for (int i = 0; i < size; i++){
    if(itemsInCharacter[i]->getShortDescription().compare(name) == 0)
            return i;
    }
    return -1;
}

Item* Character::hasItem(string name){
    for (Item* i : itemsInCharacter)
    if(i->getShortDescription().compare(name) == 0)
            return i;
    return nullptr;
}

string Character::printInventory()
{
    for (Item* i : itemsInCharacter)
    cout << (i)->getShortDescription() << endl;
    return "";
}

void Character::setForm(int formNumber){
    if(formNumber < (int)availableForms.size()){
        currentForm = availableForms[formNumber];
    }
}

int Character::getFormNumber(string form){
    for (unsigned int i = 0; i < availableForms.size(); i++)
    {
        if (availableForms[i].compare(form) == 0)
            return i;
    }
    return -1;
}
string Character::getCurrentForm(){
    return currentForm;
}



