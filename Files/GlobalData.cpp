#include "GlobalData.h"

/*
* GLOBALDATA.CPP
* --------------------
* This is where I define any methods or functions or other that I may need.
* This file is yet to be necessary. 
*/

//ActorData functions
//PhysicsData functions
PhysicsData::VELOCITY PhysicsData::Velocity(float x, float y, float angular) {
	PhysicsData::VELOCITY returnedValue;
	returnedValue.x = x;
	returnedValue.y = y;
	returnedValue.angular = angular;
	return returnedValue;

}
PhysicsData::COLLISION_DATA PhysicsData::CollisionData(
	PhysicsData::PHYSICS_INPUT actor1_physIn,
	PhysicsData::PHYSICS_INPUT actor2_physIn
) {
	PhysicsData::COLLISION_DATA returnedValue;
	returnedValue.actor1_physIn = actor1_physIn;
	returnedValue.actor2_physIn = actor2_physIn;
	return returnedValue;
}
inline float GraphicsData::LINE::length() {
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}
inline radians PhysicsData::getAngleOfLine(D2D1_POINT_2F point1, D2D1_POINT_2F point2) {
	float
		xDifference = point2.x - point1.x,
		yDifference = point2.y - point1.y;
	return atan2f(yDifference, xDifference);
}
PhysicsData::TRIANGLE_ANGLES PhysicsData::getTriangleAngles(
	D2D1_POINT_2F pointA,
	D2D1_POINT_2F pointB,
	D2D1_POINT_2F pointC
) {
	//this part of the code determines which line is the hypotenuse
	float
		lineA = findDistance(pointB, pointC),
		lineB = findDistance(pointA, pointC),
		lineC = findDistance(pointA, pointB);
	//commenting this out because I don't believe it's necessary.
	//float& hypotenuse = (line1_2 > line2_3 ? (line1_2 > line1_3 ? line1_2 : line1_3) : (line2_3 > line1_3 ? line2_3 : line1_3));
	TRIANGLE_ANGLES rValue; //tired of typing returnedValue. rValue it is
	rValue.pointAAngle = acosf((pow(lineB, 2) + pow(lineC, 2) - pow(lineA, 2)) / (2.0f * lineB * lineC));
	rValue.pointBAngle = acosf((pow(lineA, 2) + pow(lineC, 2) - pow(lineB, 2)) / (2.0f * lineA * lineC));
	rValue.pointCAngle = acosf((pow(lineA, 2) + pow(lineB, 2) - pow(lineC, 2)) / (2.0f * lineA * lineB));
}
inline float PhysicsData::findDistance(D2D1_POINT_2F point1, D2D1_POINT_2F point2) {
	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}
//TODO: findEllipsePerimeter_closestPointToTarget needs this function to work.
D2D1_POINT_2F PhysicsData::findMidpoint(D2D1_POINT_2F point1, D2D1_POINT_2F point2) {
	return D2D1::Point2F((point1.x + point2.x) / 2, (point1.y + point2.y) / 2);
}
float PhysicsData::findFocalDistanceSum(D2D1_POINT_2F point, GraphicsData::ELLIPSE_FOCI foci) {
	return PhysicsData::findDistance(point, foci.point1) + PhysicsData::findDistance(point, foci.point2);
}