# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(SpaceRescueMission LANGUAGES CXX)

# Require C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# =========================================================================
# DEPENDENCIES
# =========================================================================
add_subdirectory(external/ftxui)

# =========================================================================
# APPLICATION
# =========================================================================

# Define the source file
set(PROJECT_SOURCES
  src/graph.cpp
  src/stationNetwork.cpp
  src/utils.cpp
  src/logger.cpp
  src/dataLoader.cpp
  src/dijkstra.cpp
  src/main.cpp
)

# Create the executable target
add_executable(space-rescue-mission ${PROJECT_SOURCES})

# Include the include directory
target_include_directories(space-rescue-mission PRIVATE include)

# Link the executable against the vendored ftxui library
target_link_libraries(space-rescue-mission PRIVATE
  ftxui::screen
  ftxui::dom
  ftxui::component
)

# Static libraries so there's no external DLL dependencies
set(CMAKE_EXE_LINKER_FLAGS "-static")