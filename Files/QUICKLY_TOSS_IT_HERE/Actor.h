#pragma once

#include "GlobalData.h"

//this is just here to improve compatibility
#ifndef ACTOR_H
#define ACTOR_H
#endif

/* ENUMS
* These are mostly used as a value that classes can return as a value to simplify determining*/
//used to determine what type of Actor something is
enum ACTOR_TYPE {
	ACTOR,
	OBJECT,
	ENTITY,
	TERRAIN
};

enum SHAPE_TYPE {
	ELLIPSE,
	RECT
};
//an actor is any object, terrain, entity, or other similar thing that can interact with the world around it.
class Actor
{
private:
	Actor(SHAPE_TYPE actorShape);
protected:
	D2D1_POINT_2F pos;
	SHAPE_TYPE shape;
	D2D1_ELLIPSE ellipseShape;
	D2D1_RECT_F rectShape;
	D2D1_COLOR_F color;
	ActorData::VELOCITY velocity;
public:
	D2D1_COLOR_F getColor() { return color; };
	SHAPE_TYPE getShape() { return shape; };
	D2D1_POINT_2F getPos() { return pos; };
	ActorData::VELOCITY getVelocity() { return velocity; };
	ActorData::COLLISION_DATA getCollisionDetails(Actor* actor);
};