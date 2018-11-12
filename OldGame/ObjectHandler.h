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
	
	std::vector<Object*>* getObjList(OBJECTLIST type) { return &this->pObjects.at(type); };

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

	return false;
}

inline bool ObjectHandler::removeObject(int ID, OBJECTLIST type)
{
	for()

	return false;
}

#endif // !OBJECTHANDLER_H
