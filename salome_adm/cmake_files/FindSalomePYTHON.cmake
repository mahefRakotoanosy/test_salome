
# Python detection for Salome

set(PYTHON_ROOT_DIR $ENV{PYTHON_ROOT_DIR} CACHE PATH "Path to Python directory")
if(EXISTS ${PYTHON_ROOT_DIR})
  set(CMAKE_INCLUDE_PATH ${PYTHON_ROOT_DIR}/include)
  set(CMAKE_LIBRARY_PATH ${PYTHON_ROOT_DIR}/lib)
  set(CMAKE_PROGRAM_PATH ${PYTHON_ROOT_DIR}/bin)
endif(EXISTS ${PYTHON_ROOT_DIR})
find_package(PythonInterp REQUIRED)
# Set PythonLibs_FIND_VERSION To avoid problems when several versions are in the system
SET(PythonLibs_FIND_VERSION ${PYTHON_VERSION_STRING})
if(EXISTS ${PYTHON_ROOT_DIR})
  set(PYTHON_INCLUDE_DIR ${PYTHON_ROOT_DIR}/include/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})
  set(PYTHON_LIBRARY ${PYTHON_ROOT_DIR}/lib/libpython${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}${CMAKE_SHARED_LIBRARY_SUFFIX})
endif(EXISTS ${PYTHON_ROOT_DIR})
find_package(PythonLibs REQUIRED)
MESSAGE("Python includes : " ${PYTHON_INCLUDE_DIR})
MESSAGE("Python library  : " ${PYTHON_LIBRARY})
MESSAGE("Python binary   : " ${PYTHON_EXECUTABLE})
set(PYLOGLEVEL WARNING)
