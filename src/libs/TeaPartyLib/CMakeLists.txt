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
    Archetypes/NodeCamera.h
    Components/ActionController.h
    Components/Image.h
    Components/Keyboard.h
    Components/PlayerReference.h
    Components/Position.h
    Components/Speed.h
    Components/Sprite.h
    Game.h
    Level.h
    Systems/CameraController.h
    Systems/Display.h
    Systems/Input.h
    Systems/KeyboardController.h
    Systems/Move.h
    Vec2.h
    globals.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    Archetypes/NodeCamera.cpp
    Components/PlayerReference.cpp
    Game.cpp
    Level.cpp
    Systems/CameraController.cpp
    Systems/Display.cpp
    Systems/Input.cpp
    Systems/KeyboardController.cpp
    Systems/Move.cpp
)

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
