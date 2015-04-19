//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__InputSystem__
#define __aunteater__InputSystem__

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Node.h>
#include <aunteater/Engine.h>

#include <list>

#define BASE_SPEED 10.0

#include <set>
#include <typeinfo>

namespace TeaParty { namespace System {
class Input : public aunteater::System
{
public:
	Input();
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mNodeList;
};
}}

#endif /* defined(__aunteater__InputSystem__) */