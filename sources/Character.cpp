#include "headers/Character.h"

Character::Character(string description) {
	this->description = description;
}
void Character::addItems(Item *item) {
    itemsInCharacter.push_back(*item);
}
void Character::putItems(Item *item) {
    itemsInCharacter.push_back(*item);
    delete item;
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
  string ret = this->description;
  ret += "\n Item list:\n";
  for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    ret += "\t"+ (*i).getLongDescription() + "\n";
  return ret;
}



