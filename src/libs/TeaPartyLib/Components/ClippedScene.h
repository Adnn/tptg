//
//  ClippedScene.h
//
//  Created by Adrien David.
//
//

#ifndef Component_ClippedScene_h
#define Component_ClippedScene_h

#include "../Vec2.h"

#include "../globals.h"

#include <Polycode.h>

#include <aunteater/Component.h>

#include <memory>

namespace TeaParty { namespace Component {

// ClippedScene actually stores the clipping rectangle (over the window) in the PolycodeScene (cf. ctor)
// This clipping rectangle plus a displacmenent allow to simulate viewports.
struct ClippedScene : public aunteater::Component
{
    ClippedScene(int row, int column);
    
    // Attempt with unique ptr did not work : clone requires to leave aRhs unmodified, which is a sane thing to assume.
//    // Old school auto_ptr semantic : the copy destination assume sole ownership of the scene !
//    // (has to be done because the polycode scene does not have a working copy semantic, yet the copy is not disallowed)
//    ClippedScene(ClippedScene &aRhs) :
//            polyScene(aRhs.polyScene.release())
//    {
//        aRhs.polyScene = nullptr;
//    }

    // Need a sharing ownership here, the polycode scene does not have a working copy semantic
    // (note: yet the copy is not disallowed), and components needs to be clonable (requiring copy of their data)
    std::shared_ptr<Polycode::Scene> polyScene;

private:
    COMP_CLONE(ClippedScene)
};

}} // namespace TeaParty::Component

#endif