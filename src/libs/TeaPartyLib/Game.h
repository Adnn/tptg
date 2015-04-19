//
//  Game.h
//
//  Created by Adrien David.
//
//

#ifndef teaparty_Game_h
#define teaparty_Game_h

#include <memory>
#include <vector>
#include "Animation.h"

namespace aunteater
{
    class Engine;
    class System;
}

namespace TeaParty {

class Level;

class Game
{
public:
    Game();
    ~Game();
    void update();

private:
    void initLevel();

private:
    std::unique_ptr<aunteater::Engine> mEngine;
    std::vector<std::unique_ptr<aunteater::System> > mSystems;
    std::unique_ptr<Level> mLevel;
    std::vector<std::unique_ptr<Structure::Animation> > mAnimations;
};

} // namespace TeaParty

#endif
