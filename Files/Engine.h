#pragma once

#include "GlobalData.h"
#include "Graphics.h"
#include "Physics.h"
#include "Actor.h"
#include "Entity.h"
#include "Object.h"
#include "Terrain.h"

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif
/*
* Engine.h
* --------------------
* This is the class that handles most of the stuff happening
*/
namespace EngineData {
	enum QUEUE_DATA_INSTRUCTIONS {
		UNPACK,
		PROCESS
	};
	//UNPACK tells the engine to unpack and put the information back in the queue for proccesing
	//this allows me to have the queue process collisions
	struct PHYSICS_PROCESS_ENTRY {
		Actor* actor;
		PhysicsData::PHYSICS_OUTPUT physOut;
	};
	//I'm considering moving the entirety of COLLISION_DATA to EngineData
	struct COLLISION_ENTRY {
		Actor* actor1;
		Actor* actor2;
		PhysicsData::COLLISION_DATA cData;
	};
	struct PHYSICS_QUEUE_DATA {
		QUEUE_DATA_INSTRUCTIONS instructions;
		union {
			PHYSICS_PROCESS_ENTRY processEntry;
			COLLISION_ENTRY collisionEntry;
		};
	};
	PHYSICS_QUEUE_DATA physQData(PHYSICS_PROCESS_ENTRY processEntry);
	PHYSICS_QUEUE_DATA physQData(COLLISION_ENTRY collisionEntry);
}

class Engine
{
private:
	Graphics* graphics_;
	Physics* physics_;
	float collisionCheckingThreshold_;
	bool createdGAndP_;
	std::vector<Actor*> actorRegistry_;
	std::queue<EngineData::PHYSICS_QUEUE_DATA> physQ_;
	std::queue<GraphicsData::DRAW_DATA> drawQ_;
public:
	Engine();
	Engine(Graphics* setGraphics, Physics* setPhysics);
	~Engine();
	float getCollisionCheckingThreshold() { return collisionCheckingThreshold_; };
	void setCollisionCheckingThreshold(float newThresold);
	bool initGraphics(HWND hWnd);
	void processQueueEntry(EngineData::PHYSICS_QUEUE_DATA QData);
	void processQueueEntry(GraphicsData::DRAW_DATA QData);
	void processQueues();
	void determinePotentialCollisions();
	void populatePhysicsQueue();

};

