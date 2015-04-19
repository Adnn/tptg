#ifndef _IDG_AE_SystemKeyboardControl
#define _IDG_AE_SystemKeyboardControl

#include <aunteater/System.h>
#include <aunteater/Engine.h>

namespace TeaParty { namespace System {
	class KeyboardController : public aunteater::System
{
public:
    KeyboardController();

    virtual void addedToEngine(aunteater::Engine &aEngine);
    virtual void update(double time);

private:
    aunteater::Nodes mKeyboardActionControllers;
};

}}

#endif  // #ifdef