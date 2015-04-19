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

namespace aunteater
{
    class Engine;
    class System;
}

namespace TeaParty {

class Game
{
public:
    Game();
    ~Game();
    void update();

private:
    std::unique_ptr<aunteater::Engine> mEngine;
    std::vector<std::unique_ptr<aunteater::System> > mSystems;
};

} // namespace TeaParty

#endif
