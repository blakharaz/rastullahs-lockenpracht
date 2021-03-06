# Find MeshMagick
#
# This module defines
# MESHMAGICK_FOUND       - MeshMagick was found
# MESHMAGICK_INCLUDE_DIR - Directory containing MeshMagick header files
# MESHMAGICK_LIBRARY     - Library name of MeshMagick library
#
# Copyright (C) 2003-2009 Team Pantheon. http://www.team-pantheon.de
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# On a new cmake run, we do not need to be verbose
IF(MESHMAGICK_INCLUDE_DIR AND MESHMAGICK_LIBRARY)
	SET(MESHMAGICK_FIND_QUIETLY TRUE)
ENDIF(MESHMAGICK_INCLUDE_DIR AND MESHMAGICK_LIBRARY)

# Search for headers and libraries
IF(WIN32)

ELSE(WIN32)
	IF(PKG_CONFIG_FOUND)
		PKG_SEARCH_MODULE(MESHMAGICK meshmagick)
		SET(MESHMAGICK_INCLUDE_DIR ${MESHMAGICK_INCLUDE_DIRS})
		SET(MESHMAGICK_LIBRARY ${MESHMAGICK_LIBRARIES})
	ENDIF(PKG_CONFIG_FOUND)
	IF(NOT MESHMAGICK_FOUND)
		SET(MESHMAGICK_INCLUDE_SEARCH_DIRS
		    /usr/include
		    /usr/local/include
		    /opt/include
		    /opt/meshmagick/include)
		SET(MESHMAGICK_LIBRARY_SEARCH_DIRS
		    /usr/lib
		    /usr/lib64
		    /usr/local/lib
		    /usr/local/lib64
		    /opt/meshmagick/lib
		    /opt/meshmagick/lib64)
		SET(MESHMAGICK_INC_DIR_SUFFIXES PATH_SUFFIXES meshmagick)
		FIND_PATH(MESHMAGICK_INCLUDE_DIR MeshMagickPrerequisites.h
		          PATHS ${MESHMAGICK_INCLUDE_SEARCH_DIRS}
		          PATH_SUFFIXES ${MESHMAGICK_INC_DIR_SUFFIXES})
		FIND_LIBRARY(MESHMAGICK_LIBRARY meshmagick
		             PATHS ${MESHMAGICK_LIBRARY_SEARCH_DIRS}
		             PATH_SUFFIXES ${MESHMAGICK_LIB_DIR_SUFFIXES}})
	ENDIF(NOT MESHMAGICK_FOUND)
ENDIF(WIN32)

SET(MESHMAGICK_INCLUDE_DIR ${MESHMAGICK_INCLUDE_DIR} CACHE STRING "Directory containing MeshMagick header files")
SET(MESHMAGICK_LIBRARY ${MESHMAGICK_LIBRARY} CACHE STRING "Library name of MeshMagick library")

IF(MESHMAGICK_INCLUDE_DIR AND MESHMAGICK_LIBRARY)
	SET(MESHMAGICK_FOUND TRUE)
ENDIF(MESHMAGICK_INCLUDE_DIR AND MESHMAGICK_LIBRARY)

IF(MESHMAGICK_FOUND)
	IF(NOT MESHMAGICK_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries: ${MESHMAGICK_LIBRARY} from ${MESHMAGICK_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes: ${MESHMAGICK_INCLUDE_DIR}")
	ENDIF(NOT MESHMAGICK_FIND_QUIETLY)
ELSE(MESHMAGICK_FOUND)
	IF(MeshMagick_FIND_REQUIRED)
		IF(NOT MESHMAGICK_LIBRARY)
			MESSAGE(SEND_ERROR, "MeshMagick library could not be found.")
		ENDIF(NOT MESHMAGICK_LIBRARY)
		IF(NOT MESHMAGICK_INCLUDE_DIR)
			MESSAGE(SEND_ERROR "MeshMagick include files could not be found.")
		ENDIF(NOT MESHMAGICK_INCLUDE_DIR)
	ENDIF(MeshMagick_FIND_REQUIRED)
ENDIF(MESHMAGICK_FOUND)