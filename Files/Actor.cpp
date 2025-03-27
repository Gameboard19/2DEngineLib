#include "Actor.h"


D2D1_RECT_F Actor::getUnalteredRect() {
	try {
		if (shapeData_.type != ActorData::RECT) throw(shapeData_.type); 
		D2D1_RECT_F returnedValue;
		returnedValue.top = shapeData_.rUnion.rect.top - shapeData_.rUnion.pos.y;
		returnedValue.bottom = shapeData_.rUnion.rect.bottom - shapeData_.rUnion.pos.y;
		returnedValue.left = shapeData_.rUnion.rect.left - shapeData_.rUnion.pos.x;
		returnedValue.right = shapeData_.rUnion.rect.right - shapeData_.rUnion.pos.y;
		return returnedValue;
	}
	catch (ActorData::SHAPE_TYPE caughtType) {
		//HAHA! thats what you  get for doing rect math on an ellipse. Loser.
	}
}
D2D1_RECT_F Actor::applyTranslationToUnalteredRect(D2D1_POINT_2F newPos) {
	D2D1_RECT_F returnedValue(getUnalteredRect());
	returnedValue.top += newPos.y;
	returnedValue.bottom += newPos.y;
	returnedValue.left += newPos.x;
	returnedValue.right += newPos.x;
	return returnedValue;
}

void Actor::setPos(D2D1_POINT_2F newPos) {
	switch (shapeData_.type) {
	case ActorData::RECT:
		shapeData_.rUnion.rect = applyTranslationToUnalteredRect(newPos);
		this->shapeData_.rUnion.pos.x = newPos.x;
		this->shapeData_.rUnion.pos.y = newPos.y;
		return;
		break;
	case ActorData::ELLIPSE:
		this->shapeData_.eUnion.ellipse.point.x = newPos.x;
		this->shapeData_.eUnion.ellipse.point.y = newPos.y;
	}
}
void Actor::setPos(float x, float y) {
	switch (shapeData_.type) {
	case ActorData::RECT:
		shapeData_.rUnion.rect = applyTranslationToUnalteredRect(D2D1::Point2F(x, y));
		this->shapeData_.rUnion.pos.x = x;
		this->shapeData_.rUnion.pos.y = y;
		return;
		break;
	case ActorData::ELLIPSE:
		this->shapeData_.eUnion.ellipse.point.x = x;
		this->shapeData_.eUnion.ellipse.point.y = y;
	}
}
void Actor::setRotationDeg(degrees newRotationDeg) {
	this->shapeData_.rotation = newRotationDeg;
	return;
}
void Actor::setRotationRad(radians newRotationRad) {
	this->shapeData_.rotation = TO_DEGREES(newRotationRad);
	return;
}
PhysicsData::PHYSICS_INPUT Actor::sendPhysIn() {
	PhysicsData::PHYSICS_INPUT returnedValue;
	returnedValue.type = this->getActorType();
	returnedValue.data = this->getShapeData();
	returnedValue.velocity = this->getVelocity();
	return returnedValue;
}
GraphicsData::DRAW_DATA Actor::sendDrawData() {
	GraphicsData::DRAW_DATA returnedValue;
	returnedValue.shapeData = this->getShapeData();
	returnedValue.color = this->getColor();
	return returnedValue;
}
void Actor::recievePhysOut(PhysicsData::PHYSICS_OUTPUT physOut) {
	this->setPos(physOut.newPos);
	this->setRotationDeg(physOut.newRotationDeg);
	this->setVelocity(physOut.newVelocity);
}
float Actor::getDistanceTo(D2D1_POINT_2F targetPoint) {
	return sqrt(pow(targetPoint.x - this->shapeData_.pos.x, 2) + pow(targetPoint.y - this->shapeData_.pos.y, 2));
}