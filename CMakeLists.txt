cmake_minimum_required(VERSION 3.25.2)
project(pb)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Lägg till SFML:s include- och bibliotekssökvägar
include_directories("C:/msys64/mingw64")
link_directories("C:/msys64/mingw64/lib")

# Skapa exekverbart program
add_executable(main main.cpp)

# Länka mot SFML-biblioteken
target_link_libraries(main sfml-graphics sfml-window sfml-system)
