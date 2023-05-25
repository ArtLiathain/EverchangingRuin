#include "../headers/Character.h"

Character::Character(string description) {
    this->name = description;
    this->currentForm = "human";
    availableForms.push_back("human");
    availableForms.push_back("meerkat");
    availableForms.push_back("bee");
    availableForms.push_back("lobster");
    availableForms.push_back("elephant");
}
void Character::addItems(Item *item) {
    inventory.push_back(item);
}
void Character::putItems(Item *item) {
    int location = indexOfThing(item, inventory);
    if (location == -1){
        cout << "you don't have the item" << endl;
    }
    else{
    inventory.erase(inventory.begin()+location);
    }
}

string Character::printInventory()
{
    string inventoryString;
    for (Item* i : inventory)
    inventoryString += (i)->getShortDescription() + ", ";
    return inventoryString;
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

Item* Character::hasItem(string name){
    return hasThing(name, inventory);
}





