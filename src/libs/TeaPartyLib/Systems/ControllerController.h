#ifndef _Systems_ControllerController_
#define _Systems_ControllerController_

#include <aunteater/System.h>
#include <aunteater/Engine.h>

namespace TeaParty { namespace System {
	class ControllerController : public aunteater::System
{
public:
    ControllerController();

    virtual void addedToEngine(aunteater::Engine &aEngine);
    virtual void update(double time);

private:
    aunteater::Nodes mControllerActionControllers;
};

}}

#endif  // #ifdef