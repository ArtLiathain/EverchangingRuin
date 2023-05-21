#include <iostream>

using namespace std;
#include "../headers/Model.h"

Model::Model() {
	createRooms();
    createCharacter();
}

void Model::createCharacter(){
    Character *Tim;
    Tim = new Character("Tim");
    currentCharacter = Tim;
}

void Model::createRooms()  {
    Room *MeerkatStatue, *OpenRoomLight, *TreeRoom, *BeeStatue, *MiniOcean, *CrossRoads, *BeeTrial,
    *LobsterStatue, *Cobwebs, *ElephantStatue, *EmptyHallway ,*BreakableWallRoom, *RedHot,*Chasm, *FlowerRoom;

    MeerkatStatue = new Room("MeerkatStatue");
        MeerkatStatue->addItem(new Item("MeerkatStatue", 1, 11));
    OpenRoomLight = new Room("OpenRoomLight");
    TreeRoom = new Room("TreeRoom");
    BeeStatue = new Room("BeeStatue");
    MiniOcean = new Room("MiniOcean");
    CrossRoads = new Room("CrossRoads");
    BeeTrial = new Room("BeeTrial");
    LobsterStatue = new Room("LobsterStatue");
    Cobwebs = new Room("Cobwebs");
    ElephantStatue = new Room("ElephantStatue");
    EmptyHallway = new Room("EmptyHallway");
    BreakableWallRoom = new Room("BreakableWallRoom");
    RedHot = new Room("RedHot");
    Chasm = new Room("Chasm");
    FlowerRoom = new Room("FlowerRoom");
//             (N, E, S, W)
    MeerkatStatue->setExits(NULL, OpenRoomLight, NULL, NULL);
    OpenRoomLight->setExits(TreeRoom, MiniOcean, NULL, MeerkatStatue);
    TreeRoom->setExits(BeeStatue, NULL, OpenRoomLight, NULL);
    BeeStatue->setExits(NULL,RedHot,TreeRoom,NULL);
    MiniOcean->setExits(NULL, CrossRoads, NULL, OpenRoomLight);
    CrossRoads->setExits(Cobwebs, Chasm, BeeTrial, MiniOcean);
    BeeTrial->setExits(CrossRoads, NULL, LobsterStatue, NULL);
    LobsterStatue->setExits(BeeTrial, NULL, NULL, NULL);
    Cobwebs->setExits(ElephantStatue, NULL, CrossRoads, BreakableWallRoom);
    ElephantStatue->setExits(NULL,NULL,Cobwebs, EmptyHallway);
    EmptyHallway->setExits(NULL,ElephantStatue, BreakableWallRoom, NULL);
    RedHot->setExits(NULL, BreakableWallRoom,NULL , BeeStatue);
    BreakableWallRoom->setExits(EmptyHallway, Cobwebs, NULL, RedHot);
    Chasm->setExits(NULL, FlowerRoom, NULL, CrossRoads);
    FlowerRoom->setExits(NULL,NULL,NULL,Chasm);

        currentRoom = MeerkatStatue;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void Model::play() {
	printWelcome();
}

string Model::printWelcome() {
    string returnstring;
    returnstring += "start \n";
    returnstring +="info for help \n ";
    returnstring +=currentRoom->longDescription() + "\n";
    return returnstring;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the Model game, true is returned, otherwise false is
 * returned.
 */
void Model::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
    }
    string commandWord = command.getCommandWord();
    if (!command.hasSecondWord()){

        if (commandWord.compare("info") == 0)
            printHelp();

        else if (commandWord.compare("map") == 0)
        {
            //printMap();
        }

        else if (commandWord.compare("inventory") == 0){
            currentCharacter->printInventory();
        }

        else if (commandWord.compare("check") == 0){
            cout << currentCharacter->getCurrentForm() << endl;
        }

        else if (commandWord.compare("quit") == 0) {
            //quit
        }

    }

    if (commandWord.compare("go") == 0)
        go(command.getSecondWord());

    else if (commandWord.compare("take") == 0)
    {
        cout << takeItem(command.getSecondWord());
    }

    else if (commandWord.compare("put") == 0)
    {
        cout << putItem(command.getSecondWord());

    }

    //maybe make the function retrun stuff or break out if it finished/finds a command




}
/** COMMANDS **/
void Model::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void Model::processString(string command){
    cout << "temp" << endl;
}

string Model::go(string direction) {
//	Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("Can't go that way! \n" + currentRoom->longDescription());
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
    }
}

string Model::returnCurrentRoom(){
    return currentRoom->shortDescription();
}

string Model::takeItem(string item){
    string returnString = "";
    cout << "you're trying to take " + item << endl;
    int location = currentRoom->isItemInRoom(item);
    if (location  < 0 ){
        returnString += "item is not in room \n";
        returnString += currentRoom->longDescription() + "\n";
    }
    else{
        returnString += "item is in room \n";
        returnString += "index number " + to_string(location) + "\n";
        Item* currentItem = currentRoom->getItemFromRoom(location);
        currentCharacter->addItems(currentItem);
        currentRoom->removeItemFromRoom(location);
        cout << currentRoom->longDescription() << endl;
    }

    return returnString;
}

string Model::putItem(string item){
    string returnString = "";
    returnString += "you're adding " + item + "\n";
    Item* itemToPut = currentCharacter->hasItem(item);
    if(!itemToPut){
        returnString += "But you have none of it! \n";
        returnString += currentRoom->longDescription() + "\n";
        return returnString;
    }
    returnString += "And you manage to sucessfully \n";
    currentRoom->addItem(itemToPut);
    currentCharacter->putItems(itemToPut);
//    cout << currentRoom->longDescription() << endl;

    return returnString;
}




