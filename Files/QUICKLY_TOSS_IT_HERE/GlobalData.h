#pragma once

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif

//struct used for the collision of actors
namespace ActorData {
	struct VELOCITY {
		float x;
		float y;
	};

	struct COLLISION_DATA {
		//actor 1 is always the actor that is sending this data
		D2D1_POINT_2F actor1_pos;
		D2D1_POINT_2F actor2_pos;
		VELOCITY actor1_velocity;
		VELOCITY actor2_velocity;
	};
}