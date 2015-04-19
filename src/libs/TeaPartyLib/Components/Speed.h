//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentSpeed__
#define __aunteater__ComponentSpeed__

#include <aunteater/Component.h>
#include <memory>

namespace TeaParty { namespace Component {
class Speed : public aunteater::Component
{
public:
	Speed() :
		vX(0)
	{}
public:
	double vX;
private:
    COMP_CLONE(Speed)
};
}}
#endif /* defined(__aunteater__ComponentSpeed__) */