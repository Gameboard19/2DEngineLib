#include "Physics.h"

Physics::Physics() {
	return;
}
/*
* ELLIPSE COLLISIONS
* --------------------
* Determining the collisions of ellipses was giving me a lot
* of trouble, but I think I have an idea
* THE PROBLEM
* --------------------
* given an ellipse with the given centerpoint p1, width 2a, and height 2b,
* determine the point on the ellipse's perimeter that is closest to given
* point p2
* THE THEORY
* --------------------
* First, decide what the constant
* Draw a line from p1 to p2, then find the midpoint. if the distance to both foci is close to
* the distance we'd expect for a point on the perimeter, we can use it, else we find another midpoint
* based on if it is greater than or less than.
*/
PhysicsData::COLLISION_RESULTS Physics::processCollisionData(PhysicsData::COLLISION_DATA inputData) {
	//TODO: give myself a headache figuring out how I'm going to implement this.
	
	//collisionOccurred is false by default.
	bool collisionOccurred = false;

	// so I like what I'm doing with closest point but that won't work without also taking the rotation of the object into account as well.
	D2D1_POINT_2F actor1RefPoint, actor2RefPoint;
	switch (inputData.actor1_physIn.data.type) {
	case ActorData::SHAPE_TYPE::RECT:
		switch (inputData.actor2_physIn.data.type) {
		case ActorData::SHAPE_TYPE::RECT:
			//that
			break;
		case ActorData::SHAPE_TYPE::ELLIPSE:
			actor2RefPoint = findEllipsePerimeter_closestPointToTarget(inputData.actor2_physIn.data, inputData.actor1_physIn.data.rUnion.pos);
			break;
		}
		break;
	case ActorData::SHAPE_TYPE::ELLIPSE:
		switch (inputData.actor2_physIn.data.type) {
		case ActorData::SHAPE_TYPE::RECT:
			actor1RefPoint = findEllipsePerimeter_closestPointToTarget(inputData.actor1_physIn.data, inputData.actor2_physIn.data.rUnion.pos);
			break;
		case ActorData::SHAPE_TYPE::ELLIPSE:
			actor1RefPoint = findEllipsePerimeter_closestPointToTarget(inputData.actor1_physIn.data, inputData.actor2_physIn.data.eUnion.ellipse.point);
			actor2RefPoint = findEllipsePerimeter_closestPointToTarget(inputData.actor2_physIn.data, inputData.actor1_physIn.data.eUnion.ellipse.point);
			break;
		}
		break;
	}
}
/*
FIXME: This function
This is bad code. I know this is bad code.
The recursion is stupid, and all I get out of it is a point *close* to where the line intersects the perimeter.
to whoever feels like they can improve this: go ahead,
but I'm leaving it as it is because at least then I know what it's doing.
*/
D2D1_POINT_2F Physics::findEllipsePerimeter_closestPointToTarget(
	const ActorData::SHAPE_DATA sData,
	const D2D1_POINT_2F targetPoint
) {
	try {
		if (sData.type != ActorData::SHAPE_TYPE::ELLIPSE) throw(sData.type);
		float fociDistToCenter;
		radians fociRotation = sData.rotation;
		//implementing this here is annoying and will just make the function that much harder to understand. 
		//oh well
		if (sData.eUnion.ellipse.radiusX > sData.eUnion.ellipse.radiusY) {
			fociDistToCenter = sqrt(pow(sData.eUnion.ellipse.radiusX, 2) - pow(sData.eUnion.ellipse.radiusY, 2));
		}
		else {
			fociDistToCenter = sqrt(pow(sData.eUnion.ellipse.radiusY, 2) - pow(sData.eUnion.ellipse.radiusX, 2));
			//this is the dumbest way to dictate the orientation of the foci. whatever
			fociRotation += (PI / 2.0f); 
		}
		GraphicsData::ELLIPSE_FOCI foci(findFoci(sData.eUnion.ellipse.point, fociDistToCenter, fociRotation));
		//FIXME: there has to be a better way to do this.
		//TODO: better names.
		D2D1_POINT_2F comparedPoint1 = sData.eUnion.ellipse.point, comparedPoint2 = targetPoint;
		do {
			//see lines 16 - 21
			if (
				PhysicsData::findFocalDistanceSum(
					PhysicsData::findMidpoint(comparedPoint1, comparedPoint2), foci
				) < sData.eUnion.focalDistanceSum_reference - ellipseCollisionPointAccuracy
			) {
				comparedPoint1 = PhysicsData::findMidpoint(comparedPoint1, comparedPoint2);
			}
			else if (
				PhysicsData::findFocalDistanceSum(
					PhysicsData::findMidpoint(comparedPoint1, comparedPoint2), foci
				) > sData.eUnion.focalDistanceSum_reference + ellipseCollisionPointAccuracy
			) {
				comparedPoint2 = PhysicsData::findMidpoint(comparedPoint1, comparedPoint2);
			}
		} while (
			PhysicsData::findFocalDistanceSum(
				PhysicsData::findMidpoint(
					comparedPoint1,
					comparedPoint2
				),
				foci
			) 
			< 
			sData.eUnion.focalDistanceSum_reference - ellipseCollisionPointAccuracy 
			||
			PhysicsData::findFocalDistanceSum(
				PhysicsData::findMidpoint(
					comparedPoint1,
					comparedPoint2
				),
				foci
			) 
			> 
			sData.eUnion.focalDistanceSum_reference + ellipseCollisionPointAccuracy
		);
		//I hate how I formatted this but if it works and it's legible I don't care.
			
		return PhysicsData::findMidpoint(comparedPoint1, comparedPoint2);
	}
	catch (ActorData::SHAPE_TYPE caughtType) { 
		//TODO: do some fstream bs here and make a .txt file with the error report.
		//maybe abort after too. If this somehow happens then the program deserved to crash. Natural selection
	}
}
//in order for findEllipsePerimeter_closestPointToTarget to work I need to know
//EXACTLY where the foci are.
GraphicsData::ELLIPSE_FOCI Physics::findFoci(
	const D2D1_POINT_2F ellipseCenterpoint,
	const float linearEccentricity,
	const radians ellipseRotation
) {
	try {
		//this circle will help me plot the foci
		GraphicsData::ELLIPSE_FOCI returnedValue;
		returnedValue.point1 = D2D1::Point2F(
			(linearEccentricity * cos(ellipseRotation) + ellipseCenterpoint.x),
			(linearEccentricity * sin(ellipseRotation) + ellipseCenterpoint.y)
		);
		returnedValue.point2 = D2D1::Point2F(
			(linearEccentricity * cos(-ellipseRotation) + ellipseCenterpoint.x),
			(linearEccentricity * sin(-ellipseRotation) + ellipseCenterpoint.y)
		);
		if (returnedValue.length() != linearEccentricity * 2.0f) throw ("MATH ERROR");
		return returnedValue;
	}
	catch (std::string error) {
		//TODO: .txt file log here
	}
}
//Okay so in theory I can repurpose PhysicsData::findFocalDistanceSum() and findEllipsePerimeter_closestPointToTarget
//to create a hellspawn function findRectPerimeter_ClosestPointToTarget()
/*
FIXME: This is the same bs as findEllipsePerimeter_closestPointToTarget.
like actually, I'm using the same approach. different math same issues.
see lines 58 - 62 of this file for the problems
*/
//NOTE: D2D1_RECT_F  defines rects using 2 points ( (left, top), and (right, bottom) )
//also, the data being given to this function hasn' taken rotation into account.
//use a modified form of the function findFoci to determine the four corners, as all four corners can be inscribed on a circle.
D2D1_POINT_2F findRectPerimeter_closestPointToTarget(
	const ActorData::SHAPE_DATA sData,
	const D2D1_POINT_2F targetPoint
) {
	try {
		if (sData.type != ActorData::SHAPE_TYPE::RECT) throw(sData.type);
		D2D1_POINT_2F
			modifiedTopLeft,
			modifiedBottomRight,
			modifiedTopRight,
			modifiedBottomLeft;

	}
	catch (ActorData::ACTOR_TYPE caughtType) {
		//TODO: .txt file report of what happened.
	}
}