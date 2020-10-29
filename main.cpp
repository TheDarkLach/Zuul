#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

#include "room.h"
#include "item.h"

using namespace std;

//init functions
void initializeRooms(vector<Room*>* rooms);
void initializeItems(vector<Item*>* items);

//functions
void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom);
void printInventory(vector<Item*>* items, vector<int> inv);
void getItem(vector<Room*>* rooms, vector<Item*>* items,vector<int>* inv, int currentRoom, char name[]);
void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inv, int currentRoom, char name[]);

//move function (returns int of room going to or a 0 if no room there)
int move(vector<Room*>* rooms, int currentRoom, char direction[]);

int main()
{
  bool run = true;

  vector<Room*> roomList;
  vector<Item*> itemList;
  vector<int> inventory;

  //cstring input
  char input[30];
  
  //gotta start somewhere right?
  int currentRoom = 1;

  initializeRooms(&roomList);
  initializeItems(&itemList);

  //program
  cout << "Aliens are invading! What? Go through your house" << endl;
  cout << "and pick up items needed for survival;." << endl;
  cout << "You have the following commands: go, get, drop, inventory, quit, and help." << endl;
  cout << "Godspeed" << endl;
  
  while (run)
  {
    cout << endl << "You currently are ";
    printRoom(&roomList, &itemList, currentRoom);
    cin >> input;
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(input, "quit") == 0)
    {
      run = false;
    }
    else if (strcmp(input, "go") == 0)
    {
      cout << "Which direction would you like to go?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      if (move(&roomList, currentRoom, input) == 0)
      {
	cout << endl << "There is nothing in that direction" << endl;
      }
      else
      {
	currentRoom = move(&roomList, currentRoom, input);
      }
    }
    else if (strcmp(input, "inventory") == 0)
    {
      if (inventory.size() != 0)
      {
	cout << endl << "You have: ";
	printInventory(&itemList, inventory);
      }
      else
      {
	cout << endl << "You're broke, there's nothing in your inventory" << endl;
      }
    }
    else if (strcmp(input, "get") == 0)
    {
      //get item from that room
      cout << "What item would you like to get: " << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      getItem(&roomList, &itemList, &inventory, currentRoom, input);
    }
    else if (strcmp(input, "drop") == 0)
    {
      cout << "What would you like to drop?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      dropItem(&roomList, &itemList, &inventory, currentRoom, input);
    }
    else if (strcmp(input, "help") == 0)
    {
      cout << "You have the following commands: go, get, drop, inventory, quit, and help." << endl;
      cout << "Don't be afraid, don't you know aliens don't enter unless invited inside?" << endl;
    }
    else
    {
      cout << endl <<"Invalid input." << endl;
    }

    //win conditions
    for (int a = 0; a < inventory.size(); a++) {
      for (int b = 0; b < inventory.size(); b++) {
	for (int c = 0; c < inventory.size(); c++) {
	  if (currentRoom == 1 && inventory[a] == 1 && inventory[b] == 2 && inventory[c] == 3) {
	    cout << endl << "You have the items to beat those Aliens!" << endl << endl;
	    return 0;
	  }
	}
      }
    }
    //lose conditions
    for (int a = 0; a < inventory.size(); a++) {
      if (inventory[a] == 4 || inventory[a] == 5) {
	cout << endl << "Hey! You don't need those items." << endl;
	cout << "You lose! :(" << endl << endl;
	return 0;
      }
    }
  }
  
  return 0;
    
}
//movement
int move(vector<Room*>* rooms, int currentRoom, char direction[])
{
  vector<Room*>::iterator i;
  for(i = rooms->begin(); i != rooms->end(); i++)
  {
    //find current room
    if (currentRoom == (*i)->getId())
    {
      map<int, char*> exits;
      exits = *(*i) -> getExits();
      //get exits
      map<int, char*>::const_iterator m;
      for (m = exits.begin(); m != exits.end(); ++m)
      {
	if (strcmp(m -> second, direction) == 0)
	{
	  //int move will be the room player is going to
	  return m -> first;
	}
      }
    }
  }
  return 0;
}
