//
//  Image.h
//
//  Created by Adrien David.
//
//

#ifndef Component_Image_h
#define Component_Image_h

#include "../Vec2.h"

#include <Polycode.h>

#include <aunteater/Component.h>

#include <memory>

namespace TeaParty { namespace Component {

struct Image : public aunteater::Component
{
    Image(const std::string &aFile) :
            polyImage(std::make_shared<Polycode::SceneImage>(aFile))
    {}

    std::shared_ptr<Polycode::SceneImage> polyImage;
private:
    COMP_CLONE(Image)
};

}} // namespace TeaParty::Component

#endif