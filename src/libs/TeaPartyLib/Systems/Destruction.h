#ifndef _Systems_Destruction_
#define _Systems_Destruction_

#include <aunteater/System.h>
#include <aunteater/Engine.h>

namespace TeaParty { namespace System {
	class Destruction : public aunteater::System
{
public:
    Destruction();

    virtual void addedToEngine(aunteater::Engine &aEngine);
    virtual void update(double time);

private:
    aunteater::Nodes mToDestroy;
    aunteater::Engine *mEngine;
};

}}

#endif  // #ifdef