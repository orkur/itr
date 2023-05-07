# CMakeList.txt : CMake project for itr, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# find required packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
# Add source to this project's executable.
add_executable (itr "main.cpp" "MainMenu.cpp" "Texture.cpp" "MenuItem.cpp")

# link executable to required libraries
target_link_libraries(itr ${SDL2_LIBRARIES} SDL2_image SDL2_ttf GL)

# TODO: Add tests and install targets if needed.
