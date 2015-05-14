//
//  PointCounter.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SytemPointCounter__
#define __aunteater__SytemPointCounter__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>


namespace TeaParty { namespace System {

class PointCounter : public aunteater::System
{
public:
	virtual void addedToEngine(aunteater::Engine &aEngine);
	virtual void update(double time);

public:
	aunteater::Nodes mNodeList;
};

}}

#endif /* defined(__aunteater__SystemPointCounter__) */
