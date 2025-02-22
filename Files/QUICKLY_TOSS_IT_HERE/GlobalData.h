#pragma once

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif

/*TODO
* --------------------
* Clean this header up. it's a pigsty.
* It's called GlobalData.h. That isn't bad, but hardly communicates what it is.
*	- Figure out a better name or something, man.
* Decide on better naming conventions.
* Create namespace PhysicsData
*	- COLLISION_DATA will be in here
*	- VELOCITY will be in here
*	- As well as a separate variant of SHAPE_DATA
*		- The difference is that this one doesn't have a D2D1_COLOR_F struct in it
* Implement rotation matrices into physics calculations
*	- AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
*/

/*
* GlobalData.h
* --------------------
* This header holds various structs, enums, and other chunks of code that are used throughout the .lib
* this is in a serparate header to reduce the amount of code that is necessary to be compiled
*/

//namespace that holds various things relevant to the processing and creating of Actor related code

namespace ActorData {
	//exists as a return value for Actor::getActorType() and related methods
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

	//this exist to make it easier to pass the relevant information to the fields that require it.
	struct SHAPE_DATA {
		//pos serves to provide easy access to the midpoint of the shape
		D2D1_POINT_2F			pos;
		SHAPE_TYPE				type;
		union {
			D2D1_RECT_F			rect;
			D2D1_ELLIPSE		ellipse;
		};
	};

	//the idea for how I'm going to do this is getting more and more complex as we go but trust the process
	//this is the information
	struct C_DATA_OUT {
		ACTOR_TYPE type;
		SHAPE_DATA data;
		PhysicsData::VELOCITY velocity;
	};

	struct C_DATA_IN {
		bool					didCollide; //tells actor if it should actually listen
		D2D1_POINT_2F			newPos;
		PhysicsData::VELOCITY	newVelocity;
	};
	//these functions exist to make life easier
	SHAPE_DATA ShapeData(
		D2D1_POINT_2F			pos,
		D2D1_RECT_F				rect
	);
	SHAPE_DATA ShapeData(
		D2D1_POINT_2F			pos,
		D2D1_ELLIPSE			ellipse
	);
}

namespace PhysicsData {
	

	struct VELOCITY {
		float					x;
		float					y;
	};

	struct COLLISION_DATA {
		ActorData::C_DATA_OUT	actor1_cData;
		ActorData::C_DATA_OUT	actor2_cData;
	};

	struct COLLISION_RESULTS {
		ActorData::C_DATA_IN	actor1_cData;
		ActorData::C_DATA_OUT	actor2_cData;
	};

	VELOCITY Velocity(
		float					x, 
		float					y
	);
}

namespace GraphicsData {
	struct SHAPE_DATA {
		ActorData::SHAPE_DATA	shapeData;
		D2D1_COLOR_F			color;
	};
}