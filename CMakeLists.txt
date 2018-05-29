
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(muon)

# Find Geant4 package, activating all available UI and Vis drivers by default

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "${ENV{CXXFLAGS} -O3 -Wall")

# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


# Add the executable, and link it to the Geant4 libraries
#
add_executable(muon main.cc ${sources} ${headers})
target_link_libraries(muon ${Geant4_LIBRARIES})


# Copy all scripts to the build directory,

set(muon_SCRIPTS
 ./macro/init_vis.mac
 ./macro/vis.mac 
 ./macro/otherdrive.mac 
 ./macro/run.mac
 ./macro/run_gear.mac
 ./muon.tg 
 ./material.tg
  )

foreach(_script ${muon_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


add_custom_target(muonbin DEPENDS muon)


# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS muon DESTINATION bin)
