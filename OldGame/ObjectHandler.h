#pragma once
#ifndef OBJECTHANDLER_H
#define OBJECTHANDLER_H

#include "Object.h"
#include <array>

enum OBJECTLIST
{
	STATIC = 0, MOVING = 1, TRANS = 2
};

class ObjectHandler
{
public:
	ObjectHandler();
	~ObjectHandler();

	bool addObject(Object* obj, OBJECTLIST type);
	bool removeObject(int ID, OBJECTLIST type);
	
	std::vector<Object*>& getObjList(OBJECTLIST type) { return this->pObjects.at(type); };
	std::vector<Object*>& getALL(OBJECTLIST type);

private:
	std::vector<std::vector<Object* >> pObjects;
	//std::array<<Object*, OBJECTLIST::SIZE> aObjects;
	int nextID;
};

inline ObjectHandler::ObjectHandler()
{
	nextID = 0;

	for (int i = 0; i < sizeof(OBJECTLIST); i++)
	{
		std::vector<Object*> list;
		this->pObjects.push_back(list);
	}
}

inline ObjectHandler::~ObjectHandler()
{
	for (auto j : this->pObjects)
	{
		j.clear();
		//for (auto i : j)
		//{
		//	i.clear();
		//}
	}
	this->pObjects.clear();
}

inline bool ObjectHandler::addObject(Object * obj, OBJECTLIST type)
{
	this->pObjects.at(type).push_back(obj);
	obj->setID(this->nextID);
	this->nextID++;

	return true;
}

inline bool ObjectHandler::removeObject(int ID, OBJECTLIST type)
{
	int index = 0;
	for(auto i : this->pObjects.at(type))
	{
		if (i->getID() == ID)
		{
			this->pObjects.at(type).erase(this->pObjects.at(type).begin() + index);
		}
		else
			index++;
	}
	bool retVal = true;
	if (index == this->pObjects.at(type).size())
	{
		retVal = false;
	}
	return retVal;
}

inline std::vector<Object*>& ObjectHandler::getALL(OBJECTLIST type)
{
	std::vector<Object*> combinedlist;
	// TODO: insert return statement here

	return combinedlist;
}

#endif // !OBJECTHANDLER_H
