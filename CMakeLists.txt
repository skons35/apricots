# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.9) # allow use of FindOpenAL, ... <<  tested with CMAKE 3.28

project ("apricots" VERSION 0.2.9 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# search for locally installed RmlUi lib :
#set(RMLUI_STATIC true)

# Not avail / usable on MorphOS : set it as optional for now (we'll replace its use)
#find_package(OpenAL REQUIRED)
find_package(OpenAL QUIET)
message(STATUS "OpenAL FOUND :" ${OPENAL_FOUND}) 
if(OPENAL_FOUND)
	message(STATUS "OpenAL INCLUDE dir.:"  ${OPENAL_INCLUDE_DIR}) 
	message(STATUS "OpenAL libraries   :"  ${OPENAL_LIBRARY}) 
	include_directories(${OPENAL_INCLUDE_DIR})
endif(OPENAL_FOUND)

# Use our own package finder for libalure and SDL2 (MorphOS):
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Not avail / usable on MorphOS : set it as optional for now (we'll replace its use)
#find_package(libalure REQUIRED)
find_package(libalure QUIET)
message(STATUS "lib alure FOUND :" ${LIB_ALURE_FOUND}) 
if(LIB_ALURE_FOUND)
	message(STATUS "lib alure include dir.:"  ${LIB_ALURE_INCLUDE_DIR}) 
	message(STATUS "lib alure libraries   :"  ${ALURE_LIBRARIES}) 
	include_directories(${ALURE_INCLUDE_DIR})
endif(LIB_ALURE_FOUND)

# search for usual installed SDL2 libs :
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

message(STATUS "SDL2 FOUND :" ${SDL2_FOUND}) 
message(STATUS "SDL2 include dir.:"  ${SDL2_INCLUDE_DIR}) 
message(STATUS "SDL2_LIBRARIES :"  ${SDL2_LIBRARIES} ) 

message(STATUS "SDL2_MIXER FOUND :" ${SDL2_MIXER_FOUND}) 
message(STATUS "SDL2_MIXER include dir.:"  ${SDL2_MIXER_INCLUDE_DIR}) 
message(STATUS "SDL2_MIXER_LIBRARIES :"  ${SDL2_MIXER_LIBRARIES} ) 

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})


#find_package(Freetype REQUIRED)

#message(STATUS "Freetype include dir.:"  ${FREETYPE_INCLUDE_DIRS}) 
#message(STATUS "Freetype  library :" ${FREETYPE_LIBRARIES})

#include_directories(${FREETYPE_INCLUDE_DIRS})


#Adding display of platform infos :
message(STATUS "Platform :"  ${CMAKE_HOST_SYSTEM_NAME})     # for instance : MorphOS, Linux, ...
#message(STATUS "System   :"  ${CMAKE_SYSTEM})              # for instance : MorphOS-3.13 , ...

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/apricots)
message(STATUS "INCLUDE_DIRECTORIES :" ${CMAKE_SOURCE_DIR}/apricots)  

#FILE(GLOB sources ${CMAKE_SOURCE_DIR}/apricots/*.cpp)
FILE(GLOB sources ${CMAKE_SOURCE_DIR}/apricots/ai.cpp ${CMAKE_SOURCE_DIR}/apricots/drak.cpp         
                  ${CMAKE_SOURCE_DIR}/apricots/fall.cpp ${CMAKE_SOURCE_DIR}/apricots/game.cpp       
                  ${CMAKE_SOURCE_DIR}/apricots/menu.cpp ${CMAKE_SOURCE_DIR}/apricots/SDLfont.cpp    
                  ${CMAKE_SOURCE_DIR}/apricots/shape.cpp ${CMAKE_SOURCE_DIR}/apricots/all.cpp       
                  ${CMAKE_SOURCE_DIR}/apricots/collide.cpp ${CMAKE_SOURCE_DIR}/apricots/drawall.cpp 
                  ${CMAKE_SOURCE_DIR}/apricots/finish.cpp ${CMAKE_SOURCE_DIR}/apricots/init.cpp     
                  ${CMAKE_SOURCE_DIR}/apricots/sampleio.cpp ${CMAKE_SOURCE_DIR}/apricots/setup.cpp )
ADD_LIBRARY(apricotsLib ${sources})

# main prog :
ADD_EXECUTABLE(apricots ${CMAKE_SOURCE_DIR}/apricots/apricots.cpp)

#target_link_libraries(apricots apricotsLib ${OPENAL_LIBRARY} ${LIB_ALURE_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})


if(NOT "${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "MorphOS")
    target_link_libraries(apricots apricotsLib ${OPENAL_LIBRARY} ${ALURE_LIBRARIES} ${SDL2_LIBRARY} ${SDL2MIXER_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2IMAGE_LIBRARY})
else(NOT "${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "MorphOS")
    message(STATUS "Morphos specific tweaking : libs c and m linking, and add link flag -noixemul")
	target_link_libraries(apricots apricotsLib ${SDL2_LIBRARY} ${SDL2MIXER_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2IMAGE_LIBRARY} GL c m)
	SET_TARGET_PROPERTIES(apricots PROPERTIES LINK_FLAGS -noixemul)
    # target_link_libraries(sceneTester sceneTestsLib m Gl glut)
endif(NOT "${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "MorphOS")


# install part related :

SET_PROPERTY(TARGET apricots
  PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
 
INSTALL(TARGETS apricotsLib DESTINATION lib)
INSTALL(TARGETS apricots DESTINATION bin)

# could also copy an EXISITNG 'run' folder into destination folder : ('run' must exist, or cmake error)
#INSTALL(DIRECTORY run DESTINATION ${CMAKE_BINARY_DIR}/run)
