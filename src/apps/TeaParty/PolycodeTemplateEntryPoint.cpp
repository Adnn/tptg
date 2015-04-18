//
// Polycode template. Write your code here.
// 

#include "PolycodeTemplateEntryPoint.h"

PolycodeTemplateEntryPoint::PolycodeTemplateEntryPoint(PolycodeView *view)
{
    core = new POLYCODE_CORE(view, 640,480,false,false, 0,0,60);
    Polycode::CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
    Polycode::CoreServices::getInstance()->getResourceManager()->addDirResource("default");

	// Write your code here!
}

PolycodeTemplateEntryPoint::~PolycodeTemplateEntryPoint()
{
    
}

bool PolycodeTemplateEntryPoint::Update()
{
    return core->updateAndRender();
}