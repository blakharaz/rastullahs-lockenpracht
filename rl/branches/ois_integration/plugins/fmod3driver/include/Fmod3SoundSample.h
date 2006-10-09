/* This source file is part of Rastullahs Lockenpracht.
* Copyright (C) 2003-2005 Team Pantheon. http://www.team-pantheon.de
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

#ifndef __Fmod3SoundSample_H__
#define __Fmod3SoundSample_H__

#include "Fmod3DriverPrerequisites.h"
#include "Fmod3Sound.h"

extern "C" {
    #include <fmod.h>
}

namespace rl {
	
   /** Diese Klasse dient der Interaktion mit Ogre3D
    * @author Josch
    * @date 07-03-2005
    * @version 1.0
    */
    class _RlFmod3DriverExport Fmod3SoundSample : public Fmod3Sound
    {
    public:
        /// Konstruktor
        Fmod3SoundSample(Fmod3Driver* driver, const SoundResourcePtr &soundres);
        /// Destruktor
        virtual ~Fmod3SoundSample();

        /// Laedt den Sound.
        virtual void load() throw (RuntimeException);
        /// Entlaedt den Sound.
        virtual void unload() throw (RuntimeException);
         // Wir geben zur�ck, wie lange der Sound ist.
		virtual float getLength() const;

	protected:
        // Sind wir gueltig?
        virtual bool isValid() const throw (RuntimeException);
        // Wir erzeugen einen Channel f�r SoundChannel
        virtual int createChannel() throw (RuntimeException);

    private:
        FSOUND_SAMPLE *mSample;
    }; 

    class _RlFmod3DriverExport Fmod3SoundSamplePtr :
        public Ogre::SharedPtr<Fmod3SoundSample>
    {
    public:
        Fmod3SoundSamplePtr() : Ogre::SharedPtr<Fmod3SoundSample>() {}
        explicit Fmod3SoundSamplePtr(Fmod3SoundSample* rep) : Ogre::SharedPtr<Fmod3SoundSample>(rep) {}
        Fmod3SoundSamplePtr(const Fmod3SoundSamplePtr& res) : Ogre::SharedPtr<Fmod3SoundSample>(res) {}
    protected:
        void destroy();
    };

}
#endif