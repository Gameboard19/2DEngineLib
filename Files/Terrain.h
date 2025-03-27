#pragma once

#ifndef ACTOR_H
#include "Actor.h"
#endif

class Terrain :
    public Actor
{
public:
    ActorData::ACTOR_TYPE getActorType() { return ActorData::TERRAIN; };
};

