#ifndef _Systems_PointVisualisation_
#define _Systems_PointVisualisation_

#include <aunteater/System.h>
#include <aunteater/Engine.h>

namespace TeaParty { namespace System {
	class PointVisualisation : public aunteater::System
{
public:
    PointVisualisation();

    virtual void addedToEngine(aunteater::Engine &aEngine);
    virtual void update(double time);

private:
    aunteater::Nodes mPointCount;
};

}}

#endif  // #ifdef