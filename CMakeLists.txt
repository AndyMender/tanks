# TODO: set to 3.16 - the version actually used?
cmake_minimum_required(VERSION 3.10...3.18)

# TODO: bump when needed
project(Tanks
		VERSION 0.1
		DESCRIPTION "Tutorial Game Project in Allegro5"
		LANGUAGES C CXX)

# enforce C++ standard and disallow non-portable compiler extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO: make this step platform-dependent
include_directories(
	"/usr/include"
	"include"
)

# TODO: make this step platform-dependent
link_directories("/usr/lib64")

# configure headers
configure_file(
	"${PROJECT_SOURCE_DIR}/include/main.h.in"
	"${PROJECT_SOURCE_DIR}/include/main.hpp")

# find all libraries needed by the project
# TODO: wrap in a loop to reduce redundancy?
find_library(ALLEGRO5 allegro)
find_library(ALLEGRO5_COLOR allegro_color)
find_library(ALLEGRO5_DIALOG allegro_dialog)
find_library(ALLEGRO5_FONT allegro_font)
find_library(ALLEGRO5_TTF allegro_ttf)
find_library(ALLEGRO5_PRIMITIVES allegro_primitives)

if(ALLEGRO5 AND ALLEGRO5_COLOR AND ALLEGRO5_DIALOG AND ALLEGRO5_FONT AND ALLEGRO5_TTF AND ALLEGRO5_PRIMITIVES)
	message(STATUS "Found required allegro5 modules.")
else()
	message(FATAL_ERROR "Couldn't find all needed allegro5 modules. Make sure it's fully installed and INCLUDEd.")
endif()

# add source code subdirs
add_subdirectory("src")
add_subdirectory("src/entities")

# bells and whistles

# link-time optimization (LTO)
include(CheckIPOSupported)
check_ipo_supported(RESULT LTO_SUPPORTED)

if(LTO_SUPPORTED)
	set(INTERPROCEDURAL_OPTIMIZATION ON)
else()
	message(STATUS "LTO not supported on this platform.")
endif()