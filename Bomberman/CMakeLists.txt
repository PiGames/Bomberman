cmake_minimum_required(VERSION 3.16)
project(Bomberman LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(
    bomberman
    main.cpp

    Animator.cpp
    Animator.h

    Bomb.h
    Bomb.cpp

    BombManager.h
    BombManager.cpp

    Button.h
    Button.cpp

    Game.h
    Game.cpp

    GUI.h
    GUI.cpp

    Level.h
    Level.cpp

    LevelView.h
    LevelView.cpp

    Menu.h
    Menu.cpp

    Option.h
    Option.cpp

    PhysicalBody.h
    PhysicalBody.cpp

    PhysicsEngine.h
    PhysicsEngine.cpp

    Player.h
    Player.cpp

    Ray.h
    Ray.cpp

    Slider.h
    Slider.cpp

    TextureAtlas.h
    TextureAtlas.cpp

    Types.h
)
target_link_libraries(bomberman PRIVATE sfml-graphics sfml-audio)
target_compile_features(bomberman PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET bomberman
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
