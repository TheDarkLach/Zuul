#include <iostream>
#include <cstring>
#include "item.h"

using namespace std;

Item::Item()
{

}

//getters
char* Item::getName()
{
  return name;
}

int Item::getId()
{
  return id;
}

void Item::setName(char* newName)
{
  name = newName;
}

void Item::setId(int newId)
{
  id = newId;
}
