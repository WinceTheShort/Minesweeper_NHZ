cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject src/main.cpp
        src/Board.cpp
        src/Board.h
        src/Button.cpp
        src/Button.h
        src/Button.h
        src/Cell.cpp
        src/Cell.h
        src/Cell.h
        src/Game.cpp
        src/Game.h
        src/Game.h
        src/Slider.cpp
        src/Slider.h
        src/Slider.h
        src/Stepper.cpp
        src/Stepper.h
        src/Stepper.h
        src/CustomDiffState.cpp
        src/CustomDiffState.h
        src/DifficultyState.cpp
        src/DifficultyState.h
        src/GameState.cpp
        src/GameState.h
        src/MainMenuState.cpp
        src/MainMenuState.h
        src/MainMenuState.h
        src/State.cpp
        src/State.h
        src/State.h
        src/StateInterfaces.hpp
        src/StateInterfaces.hpp)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
