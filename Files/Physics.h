#pragma once

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif

#include "GlobalData.h"

#define PHYSICS_FRICTION_DEFAULT 0.75f
#define PHYSICS_VELOCITY_MAX_DEFAULT 10.0f
#define PHYSICS_VELOCITY_TOLERANCE_DEFAULT 0.01f

/* Physics.h
* --------------------
* This object does the calculations for how things are going to behave.
* I'd recommend using it as the other headers are designed with using it in mind.
*/

class Physics
{
private:
	float
		friction_,
		velocityLinearGlobalMax_, 
		velocityStopTolerance_,
		gravityAcceleration_,
		ellipseCollisionPointAccuracy;
	/* collisionPointAccuracy is a value for how close the value returned by
	Physics->findFocalDistanceSum has to be to the ellipse's acual value for findFocalDistanceSum
	the lower this value is, the more accurate the point used for collisions will be.
	the lower this value is, the longer the function will take to decide on a point to use.
	*/

	//these are in private because they are entirely bts functions. they don't deserve to see the sun.
	//FYI reason a lot of these just say point1 and point2 is to make it easier to copypaste code if needed.
	GraphicsData::ELLIPSE_FOCI findFoci(
		D2D1_POINT_2F ellipseCenterpoint,
		float linearEccentricity,
		radians ellipseRotation);
	//I'm sorry for these names, man. 
	D2D1_POINT_2F findEllipsePerimeter_closestPointToTarget(
		const ActorData::SHAPE_DATA sData,
		//passing SHAPE_DATA here feels stupid. Oh well.
		const D2D1_POINT_2F targetPoint
	);
	D2D1_POINT_2F findRectPerimeter_closestPointToTarget(
		const ActorData::SHAPE_DATA sData,
		const D2D1_POINT_2F targetPoint
	);
public:
	//constructors (and destructors, if necessary).
	Physics();
	Physics(
		float friction,
		float vMax,
		float vStopTolerance,
		float gAccel,
		float collisionPointAccuracy
	);
	//gets
	float getFriction() { return friction_; };
	float getVLinearGlobalMax() { return velocityLinearGlobalMax_; };
	float getVStopTolerance() { return velocityStopTolerance_; };
	float getGAccel() { return gravityAcceleration_; };
	//sets
	void setFriction(float newFriction);
	void setVMax(float newVMax);
	void setVStopTolerance(float newVStopTolerance);
	void setGAccel(float newGAccel);
	//physics object calculations
	PhysicsData::COLLISION_RESULTS processCollisionData(PhysicsData::COLLISION_DATA inputData);
	PhysicsData::PHYSICS_OUTPUT processPhysIn(PhysicsData::PHYSICS_INPUT phyIn);
	//other
	
};