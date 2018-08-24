cmake_minimum_required(VERSION 3.9)
project(Wurms)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(Wurms ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(Wurms pthread)
TARGET_LINK_LIBRARIES(Wurms Box2D)
TARGET_LINK_LIBRARIES(Wurms stdc++fs)
TARGET_LINK_LIBRARIES(Wurms sfml-system)
TARGET_LINK_LIBRARIES(Wurms sfml-audio)
TARGET_LINK_LIBRARIES(Wurms sfml-graphics)
TARGET_LINK_LIBRARIES(Wurms sfml-window)
TARGET_LINK_LIBRARIES(Wurms sfml-network)
TARGET_LINK_LIBRARIES(Wurms m)
