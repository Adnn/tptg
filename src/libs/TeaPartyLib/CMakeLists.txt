project(TeaPartyLib)

# Configure (and thus copy) the template export file to the build dir
# The export file will be added to the project headers list (and installed with them)
configure_file(${CMAKE_SOURCE_DIR}/cmake/Export.h.in
        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
        @ONLY
)

# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
    ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
    Animation.h
    Archetypes/Colliders.h
    Archetypes/NodeCamera.h
    Archetypes/TriggersActors.h
    Components/ActionController.h
    Components/AnimationList.h
    Components/AnimationStillFrame.h
    Components/BallsPoint.h
    Components/CallbackNoParam.h
    Components/CallbackOnActor.h
    Components/ClippedScene.h
    Components/Controller.h
    Components/Displacement.h
    Components/Extent.h
    Components/GamePhase.h
    Components/HudItem.h
    Components/Image.h
    Components/Index.h
    Components/Inventory.h
    Components/Keyboard.h
    Components/Pendular.h
    Components/Physics.h
    Components/PlayerReference.h
    Components/PointsTarget.h
    Components/Position.h
    Components/Score.h
    Components/SelectedPhase.h
    Components/Speed.h
    Components/Sprite.h
    Components/Static.h
    Components/TriggeringAction.h
    Components/Tween.h
    Components/IWantToDie.h
    Game.h
    InventoryStruct.h
    Level.h
    Systems/AnimationDispatcher.h
    Systems/CameraController.h
    Systems/CollisionSolver.h
    Systems/ControllerController.h
    Systems/Display.h
    Systems/Friction.h
    Systems/HudDisplay.h
    Systems/Input.h
    Systems/Inventory.h
    Systems/InventoryLayout.h
    Systems/KeyboardController.h
    Systems/Move.h
    Systems/PendulumPhysics.h
    Systems/PhaseController.h
    Systems/Physics.h
    Systems/PointCounter.h
    Systems/PointVisualisation.h
    Systems/PointsTrigger.h
    Systems/ScoreDisplay.h
    Systems/Trigger.h
    Systems/Tween.h
    Systems/Utilities.h
    Systems/Destruction.h
    Vec2.h
    globals.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    Archetypes/Colliders.cpp
    Archetypes/NodeCamera.cpp
    Archetypes/TriggersActors.cpp
    Components/CallbackNoParam.cpp
    Components/ClippedScene.cpp
    Components/GamePhase.cpp
    Components/Index.cpp
    Components/Pendular.cpp
    Components/PlayerReference.cpp
    Components/PointsTarget.cpp
    Components/Score.cpp
    Components/SelectedPhase.cpp
    Game.cpp
    Level.cpp
    Systems/AnimationDispatcher.cpp
    Systems/CameraController.cpp
    Systems/CollisionSolver.cpp
    Systems/ControllerController.cpp
    Systems/Display.cpp
    Systems/Friction.cpp
    Systems/HudDisplay.cpp
    Systems/Input.cpp
    Systems/Inventory.cpp
    Systems/InventoryLayout.cpp
    Systems/KeyboardController.cpp
    Systems/Move.cpp
    Systems/PendulumPhysics.cpp
    Systems/PhaseController.cpp
    Systems/Physics.cpp
    Systems/PointCounter.cpp
    Systems/PointVisualisation.cpp
    Systems/PointsTrigger.cpp
    Systems/ScoreDisplay.cpp
    Systems/Trigger.cpp
    Systems/Tween.cpp
    Systems/Destruction.cpp
)

source_group("Header Files\\Archetypes" REGULAR_EXPRESSION Archetypes/.*\\.h)
source_group("Header Files\\Components" REGULAR_EXPRESSION Components/.*\\.h)
source_group("Header Files\\Systems" REGULAR_EXPRESSION Systems/.*\\.h)

source_group("Source Files\\Archetypes" REGULAR_EXPRESSION Archetypes/.*\\.cpp)
source_group("Source Files\\Components" REGULAR_EXPRESSION Components/.*\\.cpp)
source_group("Source Files\\Systems" REGULAR_EXPRESSION Systems/.*\\.cpp)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
)

include_directories(${Polycode_INCLUDE_DIR} ${Polycode_VIEW_DIR} ${Polycode_DEPENDENCIES_INCLUDE_DIR})
## Adds the library headers themselves to the interface include directory
target_include_directories(${PROJECT_NAME} INTERFACE 
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
                           $<INSTALL_INTERFACE:include>
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${Polycode_INCLUDE_DIR}
    ${Polycode_DEPENDENCIES_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${Polycode_LIBRARIES}
    aunteater
)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
        PUBLIC_HEADER "${${PROJECT_NAME}_HEADERS}" )

# Generate the export set for the target
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
        RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${ARCHIVE_OUTPUT_DIRECTORY}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)

# Install the headers
install(FILES ${${PROJECT_NAME}_HEADERS}
        DESTINATION include/${PROJECT_NAME})
    
# Generate config files in the build tree.
configure_file(${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
               @ONLY)

# Custom variable holding the destination folder for package configuration files
set (ConfigPackageLocation cmake/)

# Install the config file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION ${ConfigPackageLocation})

# Exports
# TODO : change namespace
install(EXPORT ${PROJECT_NAME}Targets NAMESPACE AD::
        DESTINATION ${ConfigPackageLocation}) #install tree
export(EXPORT ${PROJECT_NAME}Targets NAMESPACE AD::) #build tree
