//
//  Tween.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef _System_Tween_h
#define _System_Tween_h

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Node.h>
#include <aunteater/Engine.h>

namespace TeaParty { namespace System {
class Tween : public aunteater::System
{
public:
	Tween()
	{}
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mNodeList;
};
}}

#endif /* defined(__aunteater__InputSystem__) */