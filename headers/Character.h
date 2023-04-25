#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "item.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;


class Character {
private:
	string description;
    vector < Item > itemsInCharacter;
    vector < string > availableForms;
    string currentForm;
public:
    void addItems(Item *Item);
    void putItems(Item *Item);
    Item hasItem(string name);
    int getItemIndex(Item *item);
    void setForm(int formNumber);
    int getFormNumber(string form);
    string getCurrentForm();


public:
	Character(string description);
	string shortDescription();
    string printInventory();

};

#endif /*CHARACTER_H_*/
