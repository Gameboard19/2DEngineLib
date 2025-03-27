#pragma once

#ifndef ACTOR_H
#include "Actor.h"
#endif

class Object :
    public Actor
{
public:
    ActorData::ACTOR_TYPE getActorType() { return ActorData::OBJECT; };
};

