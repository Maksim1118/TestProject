cmake_minimum_required(VERSION 3.16)
project(testSolution LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include_directories(src)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(testSolution
	src/main.cpp
	src/Baraban.cpp
	src/BarabanManager.cpp
	src/Button.cpp
	src/Combination.cpp
	src/Game.cpp
	src/StateMachine.cpp
	src/Symbol.cpp	
	src/WaitingAction.cpp
	src/SpinningReels.cpp
	src/ShowingWin.cpp
 )

target_link_libraries(testSolution sfml-graphics)
target_compile_features(testSolution PRIVATE cxx_std_17)

file(COPY res/Fonts DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

install(TARGETS testSolution) 
