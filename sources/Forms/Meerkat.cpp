#include "../../headers/Forms/Meerkat.h"

Meerkat::Meerkat(string name): Character(name){

    inventory.push_back(new Item("temp"));
}


string Meerkat::shortDescription(){
    return name;
}
