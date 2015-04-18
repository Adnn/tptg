//
// Polycode template. Write your code here.
//

#import <PolycodeView.h>
#include <Polycode.h>

class PolycodeTemplateEntryPoint {
public:
    PolycodeTemplateEntryPoint(PolycodeView *view);
    ~PolycodeTemplateEntryPoint();
    
    bool Update();
    
private:
    Polycode::Core *core;
};