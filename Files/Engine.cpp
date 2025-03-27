#include "Engine.h"

Engine::Engine() {
	graphics_ = new Graphics;
	physics_ = new Physics;
	createdGAndP_ = true;
}
Engine::Engine(Graphics* setGraphics, Physics* setPhysics) {
	graphics_ = setGraphics;
	physics_ = setPhysics;
	createdGAndP_ = false;
}
Engine::~Engine() {
	if (createdGAndP_) {
		delete graphics_;
		delete physics_;
	}
}
bool Engine::initGraphics(HWND hWnd) {
	return graphics_->Init(hWnd);
}
void Engine::processQueueEntry(EngineData::PHYSICS_QUEUE_DATA physQ) {
	switch (physQ.instructions) {
	case EngineData::QUEUE_DATA_INSTRUCTIONS::UNPACK:
		EngineData::PHYSICS_PROCESS_ENTRY actor1_processEntry, actor2_processEntry;
		//TODO: create the function for physics object to process collisions.
		actor1_processEntry.actor = physQ.collisionEntry.actor1;
		PhysicsData::COLLISION_RESULTS collisionResults;
		if (collisionResults.collisionOccurred) {
			//TODO: process to follow if collision occurred
		}
		break;
	case EngineData::QUEUE_DATA_INSTRUCTIONS::PROCESS:
		break;
	}
}
void Engine::determinePotentialCollisions() {
	//TODO: review this and give it a LGTM. 
	for (int i = 0; i < actorRegistry_.size(); i++) {
		for (int j = i, k = actorRegistry_.size() - 1; j < k; j++, k--) {
			if (actorRegistry_.at(i)->getDistanceTo(actorRegistry_.at(j)->getShapeData().pos) <= this->getCollisionCheckingThreshold() && i != j) {
				EngineData::COLLISION_ENTRY cEntry;
				cEntry.actor1 = actorRegistry_.at(i);
				cEntry.actor2 = actorRegistry_.at(j);
				cEntry.cData.actor1_physIn = cEntry.actor1->sendPhysIn();
				cEntry.cData.actor2_physIn = cEntry.actor2->sendPhysIn();
				physQ_.push(EngineData::physQData(cEntry));
			}
			if (actorRegistry_.at(i)->getDistanceTo(actorRegistry_.at(k)->getShapeData().pos) <= this->getCollisionCheckingThreshold() && i != k) {
				EngineData::COLLISION_ENTRY cEntry;
				cEntry.actor1 = actorRegistry_.at(i);
				cEntry.actor2 = actorRegistry_.at(k);
				cEntry.cData.actor1_physIn = cEntry.actor1->sendPhysIn();
				cEntry.cData.actor2_physIn = cEntry.actor2->sendPhysIn();
				physQ_.push(EngineData::physQData(cEntry));
			}
		}
	}
}
void Engine::populatePhysicsQueue() {
	//TODO: make this
	//the idea is to have each actor in registry send physIn, have physics object process it, and then ship that off to the queue.
}
EngineData::PHYSICS_QUEUE_DATA EngineData::physQData(PHYSICS_PROCESS_ENTRY processEntry) {
	PHYSICS_QUEUE_DATA returnedValue;
	returnedValue.instructions = PROCESS;
	returnedValue.processEntry = processEntry;
	return returnedValue;
}
EngineData::PHYSICS_QUEUE_DATA EngineData::physQData(COLLISION_ENTRY collisionEntry) {
	PHYSICS_QUEUE_DATA returnedValue;
	returnedValue.instructions = UNPACK;
	returnedValue.collisionEntry = collisionEntry;
	return returnedValue;
}