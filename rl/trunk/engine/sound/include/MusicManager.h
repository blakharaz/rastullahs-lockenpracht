/* MusicManager.h - Spielt eine Playlist ab.
 * (C) 2004. Team Pantheon. www.team-pantheon.de
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Perl Artistic License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Perl Artistic License for more details.
 *
 *  You should have received a copy of the Perl Artistic License
 *  along with this program; if not you can get it here
 *  http://www.perldoc.com/perl5.6/Artistic.html.
 */

#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include "SoundPrerequisites.h"

#include <OgreString.h>
#include <list>
#include <stdexcept>
#include <OpenThreads/Thread>
#include "ResourceManager.h"
#include "SoundResource.h"

using namespace OpenThreads;

namespace rl {
 
    typedef std::list<Ogre::String> StringList;

/** Diese Klasse verwaltet eine Liste von Musikstuecken, die
 * abgespielt werden koennen.
 * @author JoSch
 * @version 1.0
 * @date 04-12-2004
 * @version 1.1
 * @date 06-17-2004
 * @version 1.2
 * @date 07-25-2004
 */
class _RlSoundExport MusicManager : public ResourceManager, public Ogre::Singleton<MusicManager> {
    private:
        /// Finde den Nachfolger des Songs mit diesem Namen.
        SoundResource* findNextSong();
        
        /// Die aktuelle Musikresource
        SoundResource *mSource;
        /// Flag, ob automatisch weitergeschaltet werden soll.
        bool mAuto;
        /// Flag, ob die Lsite weiderholt werden soll.
        bool mLooping;
        /// Internes Flag, ob tatsaechlich abgespielt werden soll.
        bool mShouldPlay;
        /// Ob der Thread beendet werden soll. WICHTIG: Hat nicht mit dem Abspielen zu tun.
        bool mShouldExit;
        /// Unterklasse, die den Thread enth�lt
        class MusicThread : public Thread {
            public:
                MusicThread();
                ~MusicThread();
                void run();
        };
        /// Die Instanz des Threads.
        MusicThread mMusicThread;
        // MSVC6 braucht das
        friend class MusicThread;
       
    
    protected:
        /// Welche Dateiendung soll verwendet werden.
        virtual StringList getExtension();
            
    public:
        /// Gibt das Singleton zurueck.
        static MusicManager& getSingleton(void);
        /// Gibt einen Zeiger auf das Singleton zurueck.
        static MusicManager* getSingletonPtr(void);
        /// Der Standard-Konstruktor.
        MusicManager();
        /// Der Standard-Destruktor.
        ~MusicManager();
        /// Den aktuellen Song abspielen.
        void playSong();
        /// Das Spielen des aktuellen Songs abbrechen.
        void stopSong();
        /// Den Zustand des Songs zurueckgeben.
        const bool isSourcePlaying() const;
        /// Ueberpruefen, wie der Zustand des Musikmanagers ist.
        const bool isPlaying() const;
        /// Den naechsten Song in der Liste setzen.
        void setNextSong();
        /// Relative Lautstarke setzen.
        void setGain(ALfloat newGain);
        /// Relative Lautstaerke holen.
        ALfloat getGain();
        /// Eine Resource erzeugen
        Resource* create(const String& resName);
        /// Ob die Songliste wiederholt abgespielt werden soll.
        bool isLooping();
        /// Setzt, ob die Songliste wiederholt werden soll.
        void setLooping(bool looping = true);
        /// Zurueck auf Anfang der Liste.
        void rewind();
        /// Ob der MusicManager selbststaendig weiterschaltet.
        bool isAuto();
        /// Setzt, ob der MusicManger selbst weiterschaltet.
        void setAuto(bool isAuto = true);
        /// Alle Sounds l�schen.
        void clearList();
        
};

}
#endif
