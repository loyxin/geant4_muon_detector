
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

set(EXAMPLEmuon_SCRIPTS
  init_vis.mac
  vis.mac
  otherdrive.mac
  run.mac
  )

foreach(_script ${EXAMPLEmuon_SCRIPTS})
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
