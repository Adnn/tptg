//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SytemMove__
#define __aunteater__SytemMove__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>


namespace TeaParty { namespace System {
class Move : public aunteater::System
{
public:
	Move();
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mNodeList;
};
}}

#endif /* defined(__aunteater__SytemDisplay__) */