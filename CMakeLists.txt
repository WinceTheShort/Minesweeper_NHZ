cmake_minimum_required(VERSION 3.25)
project(Minesweeper_NHZ LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include(CheckCXXCompilerFlag)

option(CPP_WARNINGS_TO_ERRORS "Build with -Werror or equivalent flag. [Default: On]" Yes)
option(CPP_ENABLE_MEMTRACE "Enable building with memtrace instrumentation. [Default: On]" Yes)

add_executable(Minesweeper_NHZ src/main.cpp
        src/Board.cpp
        src/Board.hpp
        src/Button.cpp
        src/Button.hpp
        src/Cell.cpp
        src/Cell.hpp
        src/Game.cpp
        src/Game.hpp
        src/Slider.cpp
        src/Slider.hpp
        src/Stepper.cpp
        src/Stepper.hpp
        src/CustomDiffState.cpp
        src/CustomDiffState.hpp
        src/DifficultyState.cpp
        src/DifficultyState.hpp
        src/GameState.cpp
        src/GameState.hpp
        src/MainMenuState.cpp
        src/MainMenuState.hpp
        src/State.cpp
        src/State.hpp
        src/StateInterfaces.hpp
        src/gtest_lite.hpp
        src/Debug.hpp
        src/BombCell.cpp
        src/BombCell.hpp
        src/ZeroCell.cpp
        src/ZeroCell.hpp
        src/NumCell.cpp
        src/NumCell.hpp
        )
target_link_libraries(Minesweeper_NHZ PRIVATE sfml-graphics)
target_compile_features(Minesweeper_NHZ PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Minesweeper_NHZ
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Minesweeper_NHZ>
        VERBATIM)
endif()

install(TARGETS Minesweeper_NHZ)
