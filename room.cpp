#include <iostream>
#include <cstring>
#include <map>
#include "room.h"

using namespace std;

Room::Room()
{

}

//I think that's right?
map<int,char*>* Room::getExits()
{
  return &exits;
}

int Room::getId()
{
  return id;
}

int Room::getItem()
{
  return &item;
}

