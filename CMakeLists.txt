cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(SFML_STATIC_LIBRARIES TRUE)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(Main
        src/main.cpp
        src/maze.cpp
        src/maze.h
        src/MazeSolver.h
        src/MazeSolver.cpp
        src/DFS.cpp
        src/DFS.h
)
target_link_libraries(Main PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(Main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET Main
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Main>
            VERBATIM)
endif()

add_custom_command(
        TARGET Main
        COMMENT "Copy resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Main>/resources
)

add_executable(tests
        test/test.cpp
        src/maze.cpp
        src/maze.h
        src/MazeSolver.h
        src/MazeSolver.cpp
        src/DFS.cpp
        src/DFS.h
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_custom_command(
        TARGET tests
        COMMENT "Copy resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Main>/resources
)