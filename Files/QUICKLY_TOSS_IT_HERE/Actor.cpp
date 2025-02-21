#include "Actor.h"

ActorData::COLLISION_DATA Actor::getCollisionDetails(Actor* actor) {
	switch (this->getShape()) {
	case SHAPE_TYPE::ELLIPSE:
		switch (actor->getShape()) {
		case SHAPE_TYPE::ELLIPSE:
			break;
		case SHAPE_TYPE::RECT:
			break;
		default:
			break;
		}
		break;
	case SHAPE_TYPE::RECT:
		switch (actor->getShape()) {
		case SHAPE_TYPE::ELLIPSE:
			break;
		case SHAPE_TYPE::RECT:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}