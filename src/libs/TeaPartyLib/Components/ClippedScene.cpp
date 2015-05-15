#include "ClippedScene.h"

using namespace TeaParty;
using namespace Component;

ClippedScene::ClippedScene(int row, int column) :
            polyScene(std::make_shared<Polycode::Scene>(1 /*Polycode::Scene::SCENE_2D*/)) // Why a linker error here ? (and not in Display)
{
        polyScene->getActiveCamera()->setProjectionMode(Polycode::Camera::ORTHO_SIZE_MANUAL);
        polyScene->getActiveCamera()->setOrthoSize(CAM_WIDTH*VP_COLS, CAM_HEIGHT*VP_ROWS);

        polyScene->rootEntity.enableScissor = true;

        // The clipping box is expressed in window's coordinates, origin being top left
        // y going positive in the down direction
        double clippingWidth = X_RES/VP_COLS;
        double clippingHeight = Y_RES/VP_ROWS;
        polyScene->rootEntity.scissorBox = {column*clippingWidth, row*clippingHeight, clippingWidth, clippingHeight};

        // The displacement of the scene is expressed in the scene coordinates, origin at the center of the window
        // y going positive in the up direction
        double lowerBoundX = - X_ROOM/2 * (VP_COLS-1);
        double lowerBoundY = Y_ROOM/2 * (VP_ROWS-1);
        polyScene->rootEntity.setPositionX(lowerBoundX + column*X_ROOM);
        polyScene->rootEntity.setPositionY(lowerBoundY - row*Y_ROOM);
}