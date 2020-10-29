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
void printInventory(vector<Item*>* items, vector<int> invtry);
void getItem(vector<Room*>* rooms, vector<Item*>* items,vector<int>* invtry, int currentRoom, char name[]);
void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* invtry, int currentRoom, char name[]);

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

void initializeRooms(vector<Room*>* rooms)
{
  //make exit descriptions:
  char* north = (char*)("north");
  char* south = (char*)("south");
  char* east = (char*)("east");
  char* west = (char*)("west");

  //initialize temporary map to pass in exits:
  map<int, char*> temp;

  //make rooms:
  Room* hall  = new Room();
  hall -> setDescription((char*)("in the hallway."));
  hall -> setId(1);
  temp.insert(pair<int, char*> (2, east));
  temp.insert(pair<int, char*> (3, north));
  temp.insert(pair<int, char*> (4, south));
  hall -> setExits(temp);
  hall -> setItem(0);
  rooms -> push_back(hall);
  temp.clear();
  Room* coat = new Room();
  coat -> setDescription((char*)("in the coat room."));
  coat -> setId(4);
  temp.insert(pair<int, char*> (1, north));
  coat -> setExits(temp);
  coat -> setItem(0);
  rooms -> push_back(coat);
  temp.clear();
  Room* dinner = new Room();
  dinner -> setDescription((char*)("in the dining room."));
  dinner -> setId(3);
  temp.insert(pair<int, char*> (1, south));
  temp.insert(pair<int, char*> (13, north));
  dinner -> setExits(temp);
  dinner -> setItem(0);
  rooms -> push_back(dinner);
  temp.clear();
  Room* garage = new Room();
  garage -> setDescription((char*)("in the garage. Wait, where are the cars?"));
  garage -> setId(13);
  temp.insert(pair<int, char*> (3, south));
  garage -> setExits(temp);
  garage -> setItem(3/*keys*/);
  rooms -> push_back(garage);
  temp.clear();
  Room* living = new Room();
  living -> setDescription((char*)("in the living room, fun fact: you can't die in this room."));
  living -> setId(2);
  temp.insert(pair<int, char*> (1, west));
  temp.insert(pair<int, char*> (5, north));
  temp.insert(pair<int, char*> (8, south));
  temp.insert(pair<int, char*> (6, east));
  living -> setExits(temp);
  living -> setItem(4/*boots, cant run from aliens in slides right?*/);
  rooms -> push_back(living);
  temp.clear();
  Room* bath = new Room();
  bath -> setDescription((char*)("in the bathroom. Maybe you should go before it's too late?"));
  bath -> setId(5);
  temp.insert(pair<int, char*> (2, south));
  bath -> setExits(temp);
  bath -> setItem(5/*toilet paper, can never be too careful*/);
  rooms -> push_back(bath);
  temp.clear();
  Room* guest = new Room();
  guest -> setDescription((char*)("in the guest bedroom."));
  guest -> setId(6);
  temp.insert(pair<int, char*> (2, west));
  temp.insert(pair<int, char*> (7, north));
  guest -> setExits(temp);
  guest -> setItem(0);
  rooms -> push_back(guest);
  temp.clear();
  Room* closet = new Room();
  closet -> setDescription((char*)("in the closet. Dead end! Why would you even go in there?"));
  closet -> setId(7);
  temp.insert(pair<int, char*> (6, south));
  closet -> setExits(temp);
  closet -> setItem(0);
  rooms -> push_back(closet);
  temp.clear();
  Room* inhall = new Room();
  inhall -> setDescription((char*)("in the internal hallway."));
  inhall -> setId(8);
  temp.insert(pair<int, char*> (2, north));
  temp.insert(pair<int, char*> (9, west));
  temp.insert(pair<int, char*> (10, east));
  temp.insert(pair<int, char*> (11, south));
  inhall -> setExits(temp);
  rooms -> push_back(inhall);
  temp.clear();
  Room* office = new Room();
  office -> setDescription((char*)("in your office, I don't think you have time to be working!"));
  office -> setId(9);
  temp.insert(pair<int, char*> (8, east));
  office -> setExits(temp);
  office -> setItem(1/*laptop*/);
  rooms -> push_back(office);
  temp.clear();
  Room* master = new Room();
  master -> setDescription((char*)("in the master bedroom. Nap time?"));
  master -> setId(10);
  temp.insert(pair<int, char*> (8, west));
  temp.insert(pair<int, char*> (14, north));
  temp.insert(pair<int, char*> (12, east));
  master -> setExits(temp);
  master -> setItem(2/*briefcase*/);
  rooms -> push_back(master);
  temp.clear();
  Room* secret = new Room();
  secret -> setDescription((char*)("in a secret room. You shouldn't be here!"));
  secret -> setId(14);
  temp.insert(pair<int, char*> (10, south));
  secret -> setExits(temp);
  secret -> setItem(0);
  rooms -> push_back(secret);
  temp.clear();
  Room* balcony = new Room();
  balcony -> setDescription((char*)("on the balcony outside. What a view!"));
  balcony -> setId(12);
  temp.insert(pair<int, char*> (10, west));
  balcony -> setExits(temp);
  balcony -> setItem(0);
  rooms -> push_back(balcony);
  temp.clear();
  Room* outside = new Room();
  outside -> setDescription((char*)("in the backyard. No exitS, but there is a lovely garden"));
  outside -> setId(11);
  temp.insert(pair<int, char*> (8, north));
  temp.insert(pair<int, char*> (15, east));
  outside -> setExits(temp);
  outside -> setItem(0);
  rooms -> push_back(outside);
  temp.clear();
  Room* shed = new Room();
  shed -> setDescription((char*)("in the shed."));
  shed -> setId(15);
  temp.insert(pair<int, char*> (11, west));
  shed -> setExits(temp);
  shed -> setItem(0);
  rooms -> push_back(shed);
  temp.clear();
}

//init items
void initializeItems(vector<Item*>* items)
{
  Item* boots = new Item();
  boots -> setName((char*)("boots"));
  boots -> setId(4);
  items -> push_back(boots);
  Item* tp = new Item();
  tp -> setName((char*)("toilet paper. Be prepared."));
  tp -> setId(5);
  items -> push_back(tp);
  Item* laptop = new Item();
  laptop -> setName((char*)("laptop"));
  laptop -> setId(1);
  items -> push_back(laptop);
  Item* bcase = new Item();
  bcase -> setName((char*)("briefcase. What's inside?"));
  bcase -> setId(2);
  items -> push_back(bcase);
  Item* ck = new Item();
  ck -> setName((char*)("Shield"));
  ck -> setId(3);
  items -> push_back(ck);
}

//print room function
void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom)
{
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  for (r = rooms->begin(); r != rooms->end(); r++)
  {
    if (currentRoom == (*r)->getId())
    {
      cout << (*r)->getDescription() << endl;
      cout << "Exits: ";
      //exits
      //pointers really suck for memory
      for (map<int, char*>::const_iterator it = (*r) -> getExits() -> begin(); it != (*r) -> getExits() -> end(); it++)
      {
	//printing exits
	cout << it -> second << " ";
      }
      cout << endl;
      //items
      cout << "Items in this room: ";
      //for no items
      int itemCount = 0;
      for (i = items->begin(); i != items->end(); i++) {
	if ((*r)->getItem() == (*i)->getId()) {
	  //print spcific item
	  cout << (*i)->getName();
	  itemCount++;
	}
      }
      if (itemCount == 0)
      {
	cout << "no items in here." << endl;
      }
      else
      {
	cout << endl;
      }
    }
  }
}
//print inv
void printInventory(vector<Item*>* items, vector<int> invtry)
{
  vector<Item*>::iterator i;
  for (i = items->begin(); i != items->end(); i++)
  {
    for (int a = 0; a < invtry.size(); a++)
    {
      if (invtry[a] == (*i) -> getId())
      {
	cout << (*i) -> getName() << " ";
      }
    }
  }
  cout << endl;
}
//getting items
void getItem(vector<Room*>* rooms, vector<Item*>* items,vector<int>* invtry, int currentRoom, char name[])
{
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  for (r = rooms->begin(); r != rooms->end(); r++)
  {
    if (currentRoom == (*r) -> getId())
    {
      for (i = items->begin(); i != items->end(); i++)
      {
	//if item is in the room
	if (((*r) -> getItem() == (*i) -> getId()) && (strcmp((*i) -> getName(), name) == 0))
	{
	  //add to inventory
	  invtry -> push_back((*i) -> getId());
	  //set no item in room
	  (*r) -> setItem(0);
	  cout << endl << "Picked up " << (*i) -> getName() << "." << endl;
	  return;
	}
      }
    } 
  }
  cout << "Wait a minute! that item doesn't exist" << endl;
}
//dropping items
//i hated doing this
void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* invtry, int currentRoom, char name[]) {
  int counter;
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  vector<int>::iterator iv;
  //iterate through rooms
  for(r = rooms->begin(); r != rooms->end(); r++)
  {
    //if in currentRoom
    if(currentRoom == (*r) -> getId())
    {
      //if no items in the room (maximum of one)
      if ((*r) -> getItem() == 0)
      {
	//iterate through items
	for (i = items->begin(); i != items->end(); i++)
	{
	  //if item exists 
	  if (strcmp((*i) -> getName(), name) == 0)
	  {
	    //through inv
	    for (iv = invtry -> begin(); iv != invtry -> end(); iv++)
	    {
	      //if item is in inventory
	      if ((*iv) == (*i) -> getId())
	      {
		cout << endl << "Dropped " << (*i) -> getName() << "." << endl;
		//set item in current room
		(*r) -> setItem((*i) -> getId());
		//remove item from inventory
		iv = invtry -> erase(iv);
		return;
	      }
	    }
	  }
	  else if (counter == items -> size() - 1)
	  {
	    cout << endl << "You don't own that item!" << endl;
	  }
	  counter++;
	}
      }
      else
      {
	cout << endl << "You can't place that here!" << endl;
      }
    }
  }
}
