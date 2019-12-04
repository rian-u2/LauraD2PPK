# Laura++ needs ROOT, we just require that it is a version that exports CMake targets properly
# We may depend on other things in the future, e.g. JSON or YAML for easier configuration of particle properties etc.

if(DEFINED ENV{ROOTSYS})
    list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
endif()

if(LAURA_BUILD_ROOFIT_SLAVE)
	find_package(ROOT 6.14 REQUIRED COMPONENTS EG RooFitCore RooFit)
else()
	find_package(ROOT 6.14 REQUIRED COMPONENTS EG)
endif()

#message(STATUS "ROOT include directories: ${ROOT_INCLUDE_DIRS}")
#message(STATUS "ROOT libraries: ${ROOT_LIBRARIES}")
#message(STATUS "ROOT definitions: ${ROOT_DEFINITIONS}")
#message(STATUS "ROOT CXX flags: ${ROOT_CXX_FLAGS}")
#message(STATUS "ROOT CC flags: ${ROOT_CC_FLAGS}")
#message(STATUS "ROOT use file: ${ROOT_USE_FILE}")
# Don't want to do this because it uses old-style CMake
#include(${ROOT_USE_FILE})

include(${ROOT_DIR}/modules/RootNewMacros.cmake)

