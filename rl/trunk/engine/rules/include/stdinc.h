/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2007 Team Pantheon. http://www.team-pantheon.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Clarified Artistic License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Clarified Artistic License for more details.
 *
 *  You should have received a copy of the Clarified Artistic License
 *  along with this program; if not you can get it here
 *  http://www.jpaulmorrison.com/fbp/artistic2.htm.
 */

/*
 * This file is used for precompiled header generation. You have to
 * include it in all cpp files which have "Use Precompiled Header"
 * set in their C/C++ properties. It shall never be included in other
 * headers.
 *
 * The content of this file should be limited to the following include
 * types:
 *   - stdlib headers
 *   - stl headers
 *   - all types of external dependencies which will never be changed by us
 *
 * Every sub project should have it's own copy of this file and may have
 * project specific modifications
 */

#ifndef __stdinc_h__
#define __stdinc_h__

#ifdef RL_USE_PCH

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

#include <iostream>
#include <sstream>

#include <functional>
#include <algorithm>
#include <utility>

#include <OgreCommon.h>
#include <OgreConfigFile.h>
#include <OgreString.h>
#include <OgreStringConverter.h>
#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreSingleton.h>
#include <OgreLog.h>
#include <OgreLogManager.h>
#include <OgreDataStream.h>
#include <OgreSharedPtr.h>
#include <OgreResource.h>
#include <OgreResourceGroupManager.h>
#include <OgreResourceManager.h>
#include <OgreUserDefinedObject.h>
#include <OgreMovableObject.h>
#include <OgreManualObject.h>
#include <OgreNode.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include <OgreTimer.h>
#include <OgreLight.h>
#include <OgreQuaternion.h>
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <OgreRenderable.h>
#include <OgreParticleSystem.h>
#include <OgreSceneQuery.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>
#include <OgreRay.h>
#include <OgreMeshManager.h>
#include <OgreBillboardParticleRenderer.h>
#include <OgreTextureManager.h>
#include <OgreException.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRenderWindow.h>

#include <OgreNewt.h>
#include <OgreNewt_ContactCallback.h>
#include <OgreNewt_Collision.h>
#include <OgreNewt_RayCast.h>

#include <CEGUIString.h>
#include <CEGUILogger.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/any.hpp>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#  include <Windows.h>
#endif

#endif//RL_USE_PCH
#endif