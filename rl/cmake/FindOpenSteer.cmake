# Find OpenSteer
#
# This module defines
# OPENSTEER_FOUND       - OpenSteer was found
# OPENSTEER_INCLUDE_DIR - Directory containing OpenSteer header files
# OPENSTEER_LIBRARY     - Library name of OpenSteer library
#
# Copyright (C) 2003-2009 Team Pantheon. http://www.team-pantheon.de
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# On a new cmake run, we do not need to be verbose
IF(OPENSTEER_INCLUDE_DIR AND OPENSTEER_LIBRARY)
	SET(OPENSTEER_FIND_QUIETLY TRUE)
ENDIF(OPENSTEER_INCLUDE_DIR AND OPENSTEER_LIBRARY)

IF(WIN32)

ELSE(WIN32)
	IF(PKG_CONFIG_FOUND)
		PKG_SEARCH_MODULE(OPENSTEER opensteer)
		SET(OPENSTEER_INCLUDE_DIR ${OPENSTEER_INCLUDE_DIRS})
		SET(OPENSTEER_LIBRARY ${OPENSTEER_LIBRARIES})
	ENDIF(PKG_CONFIG_FOUND)
	IF(NOT OPENSTEER_FOUND)
		SET(OPENSTEER_INCLUDE_SEARCH_DIRS
		    /usr/include
		    /usr/local/include
		    /opt/include
		    /opt/OpenSteer/include)
		SET(OPENSTEER_LIBRARY_SEARCH_DIRS
		    /usr/lib
		    /usr/lib64
		    /usr/local/lib
		    /usr/local/lib64
		    /opt/OpenSteer/lib
		    /opt/OpenSteer/lib64)
		SET(OPENSTEER_INC_DIR_SUFFIXES PATH_SUFFIXES OpenSteer)
		FIND_PATH(OPENSTEER_INCLUDE_DIR SteerLibrary.h
		          PATHS ${OPENSTEER_INCLUDE_SEARCH_DIRS}
		          PATH_SUFFIXES ${OPENSTEER_INC_DIR_SUFFIXES})
		FIND_LIBRARY(OPENSTEER_LIBRARY OPENSTEER
		             PATHS ${OPENSTEER_LIBRARY_SEARCH_DIRS}
		             PATH_SUFFIXES ${OPENSTEER_LIB_DIR_SUFFIXES}})
	ENDIF(NOT OPENSTEER_FOUND)
ENDIF(WIN32)

SET(OPENSTEER_INCLUDE_DIR ${OPENSTEER_INCLUDE_DIR} CACHE STRING "Directory containing OpenSteer header files")
SET(OPENSTEER_LIBRARY ${OPENSTEER_LIBRARY} CACHE STRING "Library name of OpenSteer library")

IF(OPENSTEER_INCLUDE_DIR AND OPENSTEER_LIBRARY)
	SET(OPENSTEER_FOUND TRUE)
ENDIF(OPENSTEER_INCLUDE_DIR AND OPENSTEER_LIBRARY)

IF(OPENSTEER_FOUND)
	IF(NOT OPENSTEER_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries: ${OPENSTEER_LIBRARY} from ${OPENSTEER_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes: ${OPENSTEER_INCLUDE_DIR}")
	ENDIF(NOT OPENSTEER_FIND_QUIETLY)
ELSE(OPENSTEER_FOUND)
	IF(NOT OPENSTEER_LIBRARY)
		MESSAGE(SEND_ERROR, "OpenSteer library could not be found.")
	ENDIF(NOT OPENSTEER_LIBRARY)
	IF(NOT OPENSTEER_INCLUDE_DIR)
		MESSAGE(SEND_ERROR "OpenSteer include files could not be found.")
	ENDIF(NOT OPENSTEER_INCLUDE_DIR)
ENDIF(OPENSTEER_FOUND)