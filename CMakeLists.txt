cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

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

add_library(memtrace STATIC
        src/memtrace.cpp src/memtrace.h)
target_compile_features(memtrace PRIVATE cxx_std_98)
target_compile_definitions(memtrace PUBLIC
        $<$<BOOL:${CPP_ENABLE_MEMTRACE}>:MEMTRACE>)

add_library(minesweeper OBJECT
        src/Board.cpp
        src/Board.h
        src/Button.cpp
        src/Button.h
        src/Cell.cpp
        src/Cell.h
        src/CustomDiffState.cpp
        src/CustomDiffState.h
        src/DifficultyState.cpp
        src/DifficultyState.h
        src/Game.cpp
        src/Game.h
        src/GameState.cpp
        src/GameState.h
        src/main.cpp
        src/MainMenuState.cpp
        src/MainMenuState.h
        src/Slider.cpp
        src/Slider.h
        src/State.cpp
        src/State.h
        src/StateInterfaces.hpp
        src/Stepper.cpp
        src/Stepper.h
)
target_link_libraries(minesweeper PUBLIC memtrace)

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
        src/StateInterfaces.hpp
        src/memtrace.cpp
        src/memtrace.h
        src/memtrace.h
        src/gtest_lite.h
        src/Debug.hpp
        src/Debug.hpp
        src/BombCell.cpp
        src/BombCell.h
        src/BombCell.h
        src/ZeroCell.cpp
        src/ZeroCell.h
        src/ZeroCell.h
        src/NumCell.cpp
        src/NumCell.h
        src/NumCell.h)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics memtrace)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

# Generate warning flags appropriate to the currently used compiler.
include("${CMAKE_CURRENT_SOURCE_DIR}/generate_warnings.cmake")



if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
