cmake_minimum_required( VERSION 3.4.3 )

# Project name and programming language
project( pipenetwork CXX )

# Gather file names and store them in CMake variables
file( GLOB LIBRARY_SOURCE_FILES library/src/*.cpp )
file( GLOB TEST_SOURCE_FILES library/test/*.cpp )
file( GLOB HEADER_FILES library/inc/*.h* )

# Enables exporting all symbols to the dll on windows
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

# When using gcc add fPIC (position independent code) and some other flags.
if( CMAKE_COMPILER_IS_GNUCXX )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -Wall -Wextra" )
endif( CMAKE_COMPILER_IS_GNUCXX )

# Add compilation target for our library. Adding header files here will make 
# them show up in Visual Studio. We still need to set include folders later.
add_library( pipenetwork SHARED ${LIBRARY_SOURCE_FILES} ${HEADER_FILES} )

# Add compilation target for our executables
add_executable( main drivers/main.cpp )
add_executable( pipenetwork_testrunner ${TEST_SOURCE_FILES} )

# Add include dependencies
target_include_directories( pipenetwork PUBLIC library/inc )
target_include_directories( main PUBLIC library/inc )
target_include_directories( pipenetwork_testrunner PUBLIC 
                            library/inc external/catch )

# Add link dependencies
target_link_libraries( pipenetwork_testrunner PUBLIC pipenetwork )
target_link_libraries( main PUBLIC pipenetwork )