//
//  HudItem.h
//  aunteater
//
//  Created by Franz on 28/04/15.
//
//

#ifndef _Component_HudItem_h
#define _Component_HudItem_h

#include <Polycode.h>
#include <aunteater/Component.h>

namespace TeaParty { namespace Component {
class HudItem : public aunteater::Component
{
public:
	HudItem(const std::string &aFile) :
            polyImage(std::make_shared<Polycode::SceneImage>(aFile))
    {}

    std::shared_ptr<Polycode::SceneImage> polyImage;

private:
    COMP_CLONE(HudItem)
};
}}
#endif 