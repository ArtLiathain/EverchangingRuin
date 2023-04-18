#include "headers/Character.h"

Character::Character(string description) {
	this->description = description;
}
void Character::addItems(Item *item) {
    itemsInCharacter.push_back(*item);
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
        if(itemsInCharacter[i].getShortDescription().compare(name) == 0)
            return i;
    }
    return -1;
}

Item Character::hasItem(string name){
    for (Item i : itemsInCharacter)
        if(i.getShortDescription().compare(name) == 0)
            return i;
    Item* temp = new Item("Nothing");
    return *temp;
}

string Character::printInventory()
{
    for (Item i : itemsInCharacter)
        cout << (i).getShortDescription() << endl;
}



