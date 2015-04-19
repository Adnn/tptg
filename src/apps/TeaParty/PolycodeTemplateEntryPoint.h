//
// Polycode template. Write your code here.
//

#import <PolycodeView.h>
#include <Polycode.h>

#import <TeaPartyLib/Game.h>

class PolycodeTemplateEntryPoint {
public:
    PolycodeTemplateEntryPoint(PolycodeView *view);
    ~PolycodeTemplateEntryPoint();
    
    bool Update();
    
private:
    Polycode::Core *core;
    TeaParty::Game mGame;
    //Polycode::Scene *mScene;
};