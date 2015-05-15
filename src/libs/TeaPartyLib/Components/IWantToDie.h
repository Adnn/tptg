//
//  IWantToDie.h
//
//  created by Franz.
//
//

#ifndef component_iwanttodie_h
#define component_iwanttodie_h

#include <Polycode.h>

#include <aunteater/Component.h>

namespace TeaParty { namespace Component {

struct IWantToDie : public aunteater::Component
{
    IWantToDie(float aDelay) :
    	delay(aDelay)
    {}

    float delay;
private:
    COMP_CLONE(IWantToDie)
};

}} // namespace teaparty::component

#endif