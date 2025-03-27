#pragma once

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif

#include <vector>
#include <cmath>
#include <queue>
#include <fstream>

/*TODO
* --------------------
* Clean this header up. it's a pigsty.
*/

/*
* GlobalData.h
* --------------------
* I wanted to avoid any complications that may arise from including my headers into eachother.
*	- Trying to prevent any complications that may arise from something such as
*	  including actor into physics, physics into graphics, and graphics into actor
*		- Not that I would do that...
* My solution to this is GlobalData.h.
*	- Contains various structs, enums, unions, and functions that are shared between the 
* 	  different headers.
*		- Allows tho to effectively share necessary information with eachother without
*		  being included in eachother.
* While this does make things a bit more complicated for me to code, I believe the end result 
* will be worth it.
* 
* unfortunately, I will need a processor that DOES Include them, so that I may actually execute stuff.
*	- So, Engine.h must exist, and serves both to process all needed information and almost as a
*	  front end for the user.
*/

//ifndefs are used to improve compatibility with other libraries
#ifndef PI
#define PI 3.141592f //screw doubles all my homies are float values
#endif

#ifndef TO_DEGREES(x)
#define TO_DEGREES(x) x * (180.0f/PI) //yes,
#endif

#ifndef TO_RADIANS(x)
#define TO_RADIANS(x) x * (PI/180.0f)
#endif

typedef float degrees;
typedef float radians;

//namespace that holds various things relevant to the processing and creating of Actor related code
namespace ActorData {
	//exists as a return value for Actor::getActorType() and related methods
	enum AXIS_INTENDED_DIRECTION {
		NEGATIVE,
		NONE,
		POSITIVE
	};
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
	struct AXIS_DIRECTIONS {
		AXIS_INTENDED_DIRECTION xDirection;
		AXIS_INTENDED_DIRECTION yDirection;
	};

	//this exist to make it easier to pass the relevant information to the fields that require it.
	struct SHAPE_DATA {
		//pos being here out here with ellipse also having a midpoint is redundant.
		//I'm throwing it in with rect in rectUnion.
		//FIXME: whatever the hell probably just broke when I did that (check on Actor->setPos()).

		SHAPE_TYPE type;
		radians rotation;
		//I'm sorry
		union {
			struct {
				D2D1_RECT_F rect;
				D2D1_POINT_2F pos;
			} rUnion;
			struct {
				D2D1_ELLIPSE ellipse;
				float focalDistanceSum_reference;
			} eUnion;
		};
	};

	//the idea for how I'm going to do this is getting more and more complex as we go but trust the process
	
	enum PATH_DATA_TYPE {
		ARC,
		LINE
	};
	//these functions exist to make life easier
	struct PATH_DATA {
		PATH_DATA_TYPE pathDType;
		union {
			D2D1_ARC_SEGMENT arc;
			GraphicsData::LINE line;
		};
	};
	SHAPE_DATA ShapeData(
		D2D1_POINT_2F pos,
		D2D1_RECT_F rect,
		D2D1_MATRIX_3X2_F transform
	);
	SHAPE_DATA ShapeData(
		D2D1_POINT_2F pos,
		D2D1_ELLIPSE ellipse,
		D2D1_MATRIX_3X2_F transform
	);
}
//bunch of stuff used in Physics processes
namespace PhysicsData {
	
	struct RECT_CORNERS {
		D2D1_POINT_2F
			topLeft,
			bottomRight,
			topRight,
			bottomLeft;
	};

	struct TRIANGLE_ANGLES {
		radians
			pointAAngle,
			pointBAngle,
			pointCAngle;
	};

	struct VELOCITY {
		float x;
		float y;
		float angular; //still undetermined what unit angles will be measured in.
		float totalVelocity;
	};

	struct PHYSICS_INPUT {
		ActorData::ACTOR_TYPE type;
		ActorData::SHAPE_DATA data;
		VELOCITY velocity;
		float mass;
	};

	struct PHYSICS_OUTPUT {
		D2D1_POINT_2F newPos;
		VELOCITY newVelocity;
		float newRotationDeg;
	};

	struct COLLISION_DATA {
		PhysicsData::PHYSICS_INPUT actor1_physIn;
		PhysicsData::PHYSICS_INPUT actor2_physIn;
	};
	struct COLLISION_RESULTS {
		bool collisionOccurred;
		PhysicsData::PHYSICS_OUTPUT actor1_physOut;
		PhysicsData::PHYSICS_OUTPUT actor2_physOut;
	};
	
	COLLISION_DATA CollisionData(
		PhysicsData::PHYSICS_INPUT actor1_physIn,
		PhysicsData::PHYSICS_INPUT actor2_physIn
	);
	VELOCITY Velocity(
		float x, 
		float y,
		float angular
	);
	PHYSICS_INPUT PhysIn(
		ActorData::ACTOR_TYPE type, 
		ActorData::SHAPE_DATA data,
		VELOCITY velocity,
		float mass
	);
	inline radians getAngleOfLine(D2D1_POINT_2F point1, D2D1_POINT_2F point2);
	TRIANGLE_ANGLES getTriangleAngles(
		D2D1_POINT_2F pointA,
		D2D1_POINT_2F pointB,
		D2D1_POINT_2F pointC
	);
	inline float findDistance(D2D1_POINT_2F point1, D2D1_POINT_2F point2);
	D2D1_POINT_2F findMidpoint(D2D1_POINT_2F point1, D2D1_POINT_2F point2);
	float findFocalDistanceSum(D2D1_POINT_2F point, GraphicsData::ELLIPSE_FOCI foci);
}

namespace GraphicsData {
	struct LINE {
		D2D1_POINT_2F point1;
		D2D1_POINT_2F point2;
		inline float length();
	};
	//why did I put ELLIPSE_FOCI in GraphicsData? Graphics doesn't even use ELLIPSE_FOCI.
	//FIXME: throw ELLIPSE_FOCI in PhysicsData and fix what breaks
	typedef LINE ELLIPSE_FOCI;
	struct DRAW_DATA {
		ActorData::SHAPE_DATA shapeData;
		D2D1_COLOR_F color;
	};
	//I'm not gonna give getAngle() a LGTM until I can test it but it **should** work.
	//I'm using LINE to reduce unnecessary structures
	//why define a new struct when line holds the exact same information (+ length(), but that doesn't matter)
}