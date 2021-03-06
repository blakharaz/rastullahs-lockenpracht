# Find CEGUI-OGRE (CEGUI Renderer interface module for OGRE)
#
# This module defines
# CEGUIOGRE_FOUND       - OpenSteer was found
# CEGUIOGRE_INCLUDE_DIR - Directory containing CEGUI-OGRE header files
# CEGUIOGRE_LIBRARY     - Library name of CEGUI-OGRE library
#
# Copyright (C) 2003-2009 Team Pantheon. http://www.team-pantheon.de
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# On a new cmake run, we do not need to be verbose
IF(CEGUIOGRE_INCLUDE_DIR AND CEGUIOGRE_LIBRARY)
	SET(CEGUIOGRE_FIND_QUIETLY TRUE)
ENDIF(CEGUIOGRE_INCLUDE_DIR AND CEGUIOGRE_LIBRARY)

IF(WIN32)

ELSE(WIN32)
	IF(PKG_CONFIG_FOUND)
		PKG_SEARCH_MODULE(CEGUIOGRE CEGUI-OGRE)
		SET(CEGUIOGRE_INCLUDE_DIR ${CEGUIOGRE_INCLUDE_DIRS})
		SET(CEGUIOGRE_LIBRARY ${CEGUIOGRE_LIBRARIES})
	ENDIF(PKG_CONFIG_FOUND)
	IF(NOT CEGUIOGRE_FOUND)
		SET(CEGUIOGRE_INCLUDE_SEARCH_DIRS
			/usr/include
			/usr/local/include
			/usr/local/include/cegui-0
			/opt/include
			/opt/OGRE/include)
		SET(CEGUIOGRE_LIBRARY_SEARCH_DIRS
			/usr/lib
			/usr/lib64
			/usr/local/lib
			/usr/local/lib64
			/opt/OGRE/lib
			/opt/OGRE/lib64)
		SET(CEGUIOGRE_INC_DIR_SUFFIXES PATH_SUFFIXES OGRE)
		FIND_PATH(CEGUIOGRE_INCLUDE_DIR 
					NAMES OgreCEGUIRenderer.h CEGUI/RendererModules/Ogre/Renderer.h
					PATHS ${CEGUIOGRE_INCLUDE_SEARCH_DIRS}
					PATH_SUFFIXES ${CEGUIOGRE_INC_DIR_SUFFIXES})
		FIND_LIBRARY(CEGUIOGRE_LIBRARY CEGUIOgreRenderer-0 CEGUIOgreRenderer
					PATHS ${CEGUIOGRE_LIBRARY_SEARCH_DIRS}
					PATH_SUFFIXES ${CEGUIOGRE_LIB_DIR_SUFFIXES}})
	ENDIF(NOT CEGUIOGRE_FOUND)
ENDIF(WIN32)

SET(CEGUIOGRE_INCLUDE_DIR ${CEGUIOGRE_INCLUDE_DIR} CACHE STRING "Directory containing CEGUI-OGRE header files")
SET(CEGUIOGRE_LIBRARY ${CEGUIOGRE_LIBRARY} CACHE STRING "Library name of CEGRUI-OGRE library")

IF(CEGUIOGRE_INCLUDE_DIR AND CEGUIOGRE_LIBRARY)
	SET(CEGUIOGRE_FOUND TRUE)
ENDIF(CEGUIOGRE_INCLUDE_DIR AND CEGUIOGRE_LIBRARY)

IF(CEGUIOGRE_FOUND)
	IF(NOT CEGUIOGRE_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries: ${CEGUIOGRE_LIBRARY} from ${CEGUIOGRE_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes: ${CEGUIOGRE_INCLUDE_DIR}")
	ENDIF(NOT CEGUIOGRE_FIND_QUIETLY)
ELSE(CEGUIOGRE_FOUND)
	IF(NOT CEGUIOGRE_LIBRARY)
		MESSAGE(SEND_ERROR, "CEGRUI-OGRE library could not be found.")
	ENDIF(NOT CEGUIOGRE_LIBRARY)
	IF(NOT CEGUIOGRE_INCLUDE_DIR)
		MESSAGE(SEND_ERROR "CEGRUI-OGRE include files could not be found.")
	ENDIF(NOT CEGUIOGRE_INCLUDE_DIR)
ENDIF(CEGUIOGRE_FOUND)