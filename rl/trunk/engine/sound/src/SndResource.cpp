#include <string>
#include <iostream>
#include "SoundManager.h"
#include "SndResource.h"
#include "boost/thread/xtime.hpp"
#include "Sleep.h"

using namespace std;
using namespace Ogre;
using namespace boost;

namespace rl {
/**
 * @author JoSch
 * @date 07-23-2004
 */
SndResource::SndResource(const String &name):
    Resource(),
    mFadeInThread(this, true),
    mFadeOutThread(this, false),
    mShouldFadeIn(false),
    mShouldFadeOut(false)
{
    mName = name;
    alGenSources(1, &mSource);
    check();
    setGain(1.0f);
    setPosition(Vector3(0.0, 0.0, 0.0));
    setVelocity(Vector3(0.0, 0.0, 0.0));
    setDirection(Vector3(0.0, 0.0, 0.0));
}

/**
 * @author JoSch
 * @date 07-24-2004
 */
SndResource::~SndResource()
{
    alDeleteBuffers(mBufferCount, mBuffers);
    delete[] mBuffers;
    alDeleteSources(1, &mSource);
}

/**
 * @return Die aktuelle Richtung der Soundquelle
 * @author JoSch
 * @date 07-23-2004
 */
const Vector3 SndResource::getDirection() const throw (RuntimeException)
{
    Vector3 result;
    alGetSource3f(mSource, AL_DIRECTION,
        &result.x, &result.y, &result.z);
    check();
    return result;
}

/**
 * @param direction Die neue Richtung der Soundquelle.
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::setDirection (const Vector3& direction) throw (RuntimeException)
{
    alSource3f(mSource, AL_DIRECTION,
        direction[0], direction[1], direction[2]);
    check();
}

/**
 * @return Die aktuelle Position der Soundquelle
 * @author JoSch
 * @date 07-23-2004
 */
const Vector3 SndResource::getPosition() const throw (RuntimeException)
{
    Vector3 result;
    alGetSource3f(mSource, AL_POSITION,
        &result.x, &result.y, &result.z);
    check();
    return result;
}

/**
 * @param position Die neue Position der Soundquelle.
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::setPosition(const Vector3& position) throw (RuntimeException)
{
    alSource3f(mSource, AL_POSITION,
        position[0], position[1], position[2]);
    check();
}

/**
 * @return Die aktuelle Geschwindigkeit der Soundquelle
 * @author JoSch
 * @date 07-23-2004
 */
const Vector3 SndResource::getVelocity() const throw (RuntimeException)
{
    Vector3 result;
    alGetSource3f(mSource, AL_VELOCITY,
        &result.x, &result.y, &result.z);
    check();
    return result;
}

/**
 * @param velocity Die neue Geschwindigkeit der Soundquelle.
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::setVelocity(const Vector3& velocity) throw (RuntimeException)
{
    alSource3f(mSource, AL_VELOCITY,
        velocity[0], velocity[1], velocity[2]);
    check();
}

/**
 * @return Die aktuelle Lautstaerke der Soundquelle
 * @author JoSch
 * @date 07-23-2004
 */
const ALfloat SndResource::getGain() const throw (RuntimeException)
{
    mGainMutex.lock();
    ALfloat result;
    mGainMutex.lock();
    alGetSourcef(mSource, AL_GAIN, &result);
    mGainMutex.unlock();
    check();
    return result;
}

/**
 * @param gain Die neue Lautstarke der Soundquelle.
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::setGain(const ALfloat gain) throw (RuntimeException)
{
    mGainMutex.lock();
    alSourcef(mSource, AL_GAIN, gain);
    mGainMutex.unlock();
    check();
}

/** Entlaedt die Soundquelle und setzt die Werte.
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::unload()
{
    if (mIsLoaded)
    {
        stop();
        alSourceUnqueueBuffers(mSource, mBufferCount, mBuffers);
        // Fehler zuruecksetzen.
        alGetError();
    }
    mIsLoaded = false;
}

/**
 * @author JoSch
 * @date 09-17-2004
 */
void SndResource::fadeIn(unsigned int msec)
{
    if (msec != 0)
    {
        mFadeInThread.mDuration = msec;
        mFadeInThread.start();
        mShouldFadeIn = false;
    }
}
/**
 * @author JoSch
 * @date 09-15-2004
 */
void SndResource::fadeOut(unsigned int msec)
{
    if (msec != 0 )
    {
        mFadeOutThread.mDuration = msec;
        mFadeOutThread.start();
        mShouldFadeOut = false;
    }
}
/**
 * @author JoSch
 * @date 09-15-2004
 */
void SndResource::play(unsigned int msec) throw (RuntimeException)
{
    if (getState() != AL_PLAYING)
    {
        // Abspielen.
        alSourcePlay(mSource);
        check();
        fadeIn(msec);
    }
}

/**
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::pause() throw (RuntimeException)
{
    alSourcePause(mSource);
    check();
}

/**
 * @author JoSch
 * @date 09-15-2004
 */
void SndResource::stop(unsigned int msec) throw (RuntimeException)
{
    fadeOut(msec);
}

/**
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::rewind() throw (RuntimeException)
{
    alSourceRewind(mSource);
    check();
}

/**
 * @return Der momentane Zustand der Soundquelle.
 * @author JoSch
 * @date 07-23-2004
 */
const ALenum SndResource::getState() const throw (RuntimeException)
{
    ALenum result;
    alGetSourcei(mSource, AL_SOURCE_STATE, &result);    
    check();
    return result;
}

/**
 * @return Ueberprueft, ob Fehler aufgetreten ist, ansonsten Exception.
 * @author JoSch
 * @date 07-23-2004
 */
void SndResource::check() const throw (RuntimeException)
{
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        Throw(RuntimeException, string((char*)alGetString(error)));
    }
}

/**
 * @param duration. Die Zeit in msek., die der Fade In insgesamt dauern soll.
 * @param time. Die Zeit in msek., wo der Fade In gerade ist
 * @param gain. Der aktuelle Lautstaerkewert, vom dem ausgegangen wird.
 * @author JoSch
 * @09-15-2004
 */
ALfloat SndResource::calculateFadeIn(unsigned RL_LONGLONG duration, unsigned RL_LONGLONG time,
                ALfloat gain)
{
    try {
        ALfloat x = (time * 1.0f) / duration;
        return (1.0f - exp(-x)) * gain;
    } catch(...)
    {
        return gain;
    }
}

/**
 * @param duration. Die Zeit in msek., die der Fade Out insgesamt dauern soll.
 * @param time. Die Zeit in msek., wo der Fade Out gerade ist
 * @param gain. Der aktuelle Lautstaerkewert, vom dem ausgegangen wird.
 * @author JoSch
 * @09-15-2004
 */
ALfloat SndResource::calculateFadeOut(unsigned RL_LONGLONG duration, unsigned RL_LONGLONG time,
                ALfloat gain)
{
    try {
        ALfloat x = (time * 2.0f) / duration;
        return exp(-x) * gain;
    } catch(...)
    {
        return (ALfloat)0.0f;
    }
}

/**
 */
SndResource::FadeThread::FadeThread(SndResource *that, bool fadeIn)
    : that(that),
      mFadeIn(fadeIn)
{
}

/**
 * Fuehrt das Fade aus
 * @author JoSch
 * @date 09-16-2004
 */
void SndResource::FadeThread::run()
{
    if (mFadeIn)
    {
        if (mDuration != 0)
        {
            // Alte Lautstaerke speichern.
            ALfloat gain = that->getGain();
            
            that->setGain(0.0f);
            for(unsigned int time = 0; time <= mDuration; time += 10)
            {
                
                // Warten
                msleep(10);
                ALfloat newgain = that->calculateFadeIn(mDuration, time, gain);
                // Lautstaerke hochsetzen.
                that->setGain((newgain > gain)?gain:newgain);
            }
            that->setGain(gain);
            that->check();
        }
    } else {
        if (mDuration != 0)
        {
            
            // Alte Lautstaerke speichern.
            ALfloat gain = that->getGain();
            
            for (unsigned int time = 0; time <= mDuration; time += 10)
            {
                // Warten
                msleep(1);
                ALfloat newgain = that->calculateFadeOut(mDuration, time, gain);
                // Lautstaerke hochsetzen.
                that->setGain((newgain > gain)?gain:newgain);
            }
            that->setGain(0.0f);
            that->check();
            
        }
        // Stoppen.
        alSourceStop(that->mSource);
        that->check();
    }
    
    
}



}
