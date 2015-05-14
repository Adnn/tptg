#ifndef _TeaParty_Component_Physics_h
#define _TeaParty_Component_Physics_h

#include "../Vec2.h"

#include <aunteater/Component.h>
#include <vector>

namespace TeaParty { namespace Component {
class Physics : public aunteater::Component
{
public:
	Physics(double aMass=0) :
		aIsOnGround(true),
		mass(aMass)
	{}

	void addForce(Vec2 aForce)
	{
		mForces.push_back(aForce);
	}

	bool aIsOnGround;
	std::vector<Vec2> mForces;
    double mass;

private:
	COMP_CLONE(Physics)
};
}}
#endif  // #ifdef