#include <iostream>

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

  char input[30]; //cstring for user inputs
  int currentRoom = 1;

  initializeRooms(&roomList);
  initializeItems(&itemList);
}
