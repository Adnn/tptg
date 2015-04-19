//
//  Sprite.h
//
//  Created by Adrien David.
//
//

#ifndef Component_Sprite_h
#define Component_Sprite_h

#include "../Vec2.h"

#include <Polycode.h>

#include <aunteater/Component.h>

#include <memory>

namespace TeaParty { namespace Component {

struct Sprite : public aunteater::Component
{
    Sprite(Polycode::SpriteSet *aSpriteSet) :
            polySprite(std::make_shared<Polycode::SceneSprite>(aSpriteSet))
    {}

    std::shared_ptr<Polycode::SceneSprite> polySprite;
private:
    COMP_CLONE(Sprite)
};

}} // namespace TeaParty::Component

#endif