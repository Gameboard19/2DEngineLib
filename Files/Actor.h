#pragma once

#include "GlobalData.h"

#ifndef ACTOR_H
#define ACTOR_H
#endif

//an actor is any object, terrain, entity, or other similar thing that can interact with the world around it.
class Actor
{
private:
	Actor(D2D1_RECT_F rect);
	Actor(D2D1_ELLIPSE ellipse);
protected:
	ActorData::SHAPE_DATA shapeData_;
	D2D1_COLOR_F color_;
	PhysicsData::VELOCITY velocity_;
	D2D1::Matrix3x2F matrix_;
	float mass_, longestRadius_;
	//FIXME: just swapped rotation from degrees to radians AND implemented it into shapeData_. 
	//nothing is going to show up as wrong, but somewhere there is probably some equation that *is* wrong.
	//shapeData_ is holding like more than half of all the variables for actor but if it has to do with geometry
	//it goes in the square hole.

public:
	//gets
	virtual ActorData::ACTOR_TYPE getActorType() { return ActorData::ACTOR; };
	//okay so this is really stupid but the way that SHAPE_DATA is set up
	//means that I require the existance of getUnalteredRect();
	D2D1_RECT_F getUnalteredRect();
	//its faster if I have this function exist.
	D2D1_RECT_F applyTranslationToUnalteredRect(D2D1_POINT_2F newPos);
	D2D1_COLOR_F getColor() { return color_; };
	PhysicsData::VELOCITY getVelocity() { return velocity_; };
	ActorData::SHAPE_DATA getShapeData() { return shapeData_; };
	degrees getRotationDeg() { return TO_DEGREES(shapeData_.rotation); };
	radians getRotationRad() { return shapeData_.rotation; };
	float getDistanceTo(D2D1_POINT_2F targetPoint);
	D2D1_MATRIX_3X2_F getRMatrix();
	//sets
	void setColor(D2D1_COLOR_F newColor);
	void setPos(D2D1_POINT_2F newPos);
	void setPos(float x, float y);
	void setRotationDeg(degrees newRotationDeg);
	void setRotationRad(radians newRotationRad);
	void setVelocity(PhysicsData::VELOCITY newVelocity);
	void setShapeData(ActorData::SHAPE_DATA newShapeData);
	//sends		- I don't know what else to call it so I am calling them sends.
	PhysicsData::PHYSICS_INPUT sendPhysIn();
	GraphicsData::DRAW_DATA sendDrawData();
	//recieves
	void recievePhysOut(PhysicsData::PHYSICS_OUTPUT);
	//other
	void turnToFace(D2D1_POINT_2F targetPos); //rotates the actor to look at specified D2D1_POINT_2F 
};