#include <iostream>

using namespace std;
#include "headers/ZorkUL.h"

int main(int argc, char *argv[]) {
	ZorkUL temp;
	temp.play();
	return 0;
}

ZorkUL::ZorkUL() {
	createRooms();
    createCharacter();
}

void ZorkUL::createCharacter(){
    Character *Tim;
    Tim = new Character("Tim");
    currentCharacter = Tim;
}

void ZorkUL::createRooms()  {
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
void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
	cout << endl;
	cout << "end" << endl;
}

void ZorkUL::printWelcome() {
	cout << "start"<< endl;
	cout << "info for help"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
        cout << "[h] --- [f] --- [g]" << endl;
		cout << "         |         " << endl;
        cout << "         |         " << endl;
		cout << "[c] --- [a] --- [b]" << endl;
		cout << "         |         " << endl;
		cout << "         |         " << endl;
		cout << "[i] --- [d] --- [e]" << endl;
		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 ){
            cout << "item is not in room" << endl;
            cout << currentRoom->longDescription() << endl;
        }
        else{
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            Item* currentItem = currentRoom->getItemFromRoom(location);
            currentCharacter->addItems(currentItem);
            currentRoom->removeItemFromRoom(location);
            cout << currentRoom->longDescription() << endl;
        }
        }
    }

    else if (commandWord.compare("put") == 0)
    {
        if (!command.hasSecondWord()) {
            cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            Item itemToPut = currentCharacter->hasItem(command.getSecondWord());
            if(itemToPut.getShortDescription().compare("Nothing") == 0){
                cout << "But you have none of it!" << endl;
                cout << currentRoom->longDescription() << endl;
            }
            else {
                cout << "And you manage to sucessfully" << endl;

                currentRoom->addItem(&itemToPut);
                currentCharacter->putItems(&itemToPut);
                cout << currentRoom->longDescription() << endl;
            }
            }
    }

    else if (commandWord.compare("inventory") == 0){
            currentCharacter->printInventory();
    }

    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
		cout << "underdefined input"<< endl;
	else {
		currentRoom = nextRoom;
		cout << currentRoom->longDescription() << endl;
	}
}

string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}
