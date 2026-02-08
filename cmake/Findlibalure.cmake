#inspired from basic findPackage 


#    - Useful Result from shell cmd : 
#    - apt-file list libalure-dev : 
# libalure-dev: /usr/include/AL/alure.h     
# libalure-dev: /usr/lib/x86_64-linux-gnu/libalure-static.a
# libalure-dev: /usr/lib/x86_64-linux-gnu/libalure.so
# libalure-dev: /usr/lib/x86_64-linux-gnu/pkgconfig/alure.pc
# libalure-dev: /usr/share/doc/libalure-dev/changelog.Debian.gz
# libalure-dev: /usr/share/doc/libalure-dev/copyright
# libalure-dev: /usr/share/doc/libalure-dev/examples/alurecdplay.c
# libalure-dev: /usr/share/doc/libalure-dev/examples/alureplay.c
# libalure-dev: /usr/share/doc/libalure-dev/examples/alurestream.c


#IF(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#	message(STATUS "build type : " ${CMAKE_BUILD_TYPE})
#	message(STATUS "Tuning Debug library names...")	
#ELSE()
#ENDIF()

FIND_PATH(LIB_ALURE_INCLUDE_DIR AL/alure.h  # find AL/alure.h and set it in ALLURE_INCLUDE
  HINTS
  PATH_SUFFIXES include  # postfix the path 'include' when searching the paths below for 'AL/alure.h'
  PATHS
  #$ENV{LIB_ALURE}  # Use environment variable LIB_ALURE and see if $LIB_ALURE/include/AL/alure.h exists
  #/usr/local
  /usr
)

# dyn library version found :
FIND_LIBRARY(LIB_ALURE_LIBRARY alure
  HINTS
  #PATH_SUFFIXES lib lib64 libs/Win32 libs/Win64
  PATH_SUFFIXES x86_64-linux-gnu # build  # VA fix
  PATHS
  #$ENV{RMLUI} # Use environment variable RMLUI and see if $RMLUI/build contains  RmlCore lib
  #/usr/local
  /usr/lib
)


  
SET(LIB_ALURE_FOUND "NO")
IF(LIB_ALURE_LIBRARY AND LIB_ALURE_INCLUDE_DIR)
  SET(LIB_ALURE_FOUND "YES")
  
#default linking (optimized): 
 #SET(LIB_ALURE_LIBRARIES "optimized" ${LIB_ALURE_LIBRARY})
 SET(LIB_ALURE_LIBRARIES ${LIB_ALURE_LIBRARY})
  # message(STATUS "linking library : " ${LIB_ALURE_LIBRARIES})
 
ENDIF()

