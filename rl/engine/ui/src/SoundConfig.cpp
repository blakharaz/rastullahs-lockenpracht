/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2008 Team Pantheon. http://www.team-pantheon.de
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
#include "stdinc.h" //precompiled header

#include "SoundConfig.h"

#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/widgets/ListboxTextItem.h>

#include "Exception.h"
#include "SoundDriver.h"
#include "SoundDriverConfigComponent.h"
#include "SoundManager.h"

using namespace CEGUI;
using namespace Ogre;

namespace rl
{

    SoundConfig::SoundConfig()
        : AbstractWindow("soundconfig.xml", WIT_MOUSE_INPUT | WIT_KEYBOARD_INPUT)
        , mDriverBox(NULL)
        , mVolumeSound(0)
        , mVolumeMusic(0)
        , mVolumeMaster(0)
        , mCurrentConfig(NULL)
        , mDriverConfigs()
    {
        getWindow()->subscribeEvent(FrameWindow::EventCloseClicked, &SoundConfig::handleClose, this);
        getPushButton("Cancel")->subscribeEvent(PushButton::EventMouseClick, &SoundConfig::handleClose, this);

        getWindow("OK")->subscribeEvent(Window::EventMouseClick, &SoundConfig::handleOK, this);

        mVolumeSound = getSlider("VolumeSound");
        mVolumeSound->setMaxValue(1.0);
        mVolumeSound->setCurrentValue(SoundManager::getSingleton().getActiveDriver()->getDefaultSoundVolume());
        mVolumeSound->subscribeEvent(Slider::EventValueChanged, &SoundConfig::handleVolumeSoundChanged, this);

        mVolumeMusic = getSlider("VolumeMusic");
        mVolumeMusic->setMaxValue(1.0);
        mVolumeMusic->setCurrentValue(SoundManager::getSingleton().getActiveDriver()->getDefaultMusicVolume());
        mVolumeMusic->subscribeEvent(Slider::EventValueChanged, &SoundConfig::handleVolumeMusicChanged, this);

        mVolumeMaster = getSlider("VolumeMaster");
        mVolumeMaster->setMaxValue(1.0);
        mVolumeMaster->setCurrentValue(SoundManager::getSingleton().getActiveDriver()->getMasterVolume());
        mVolumeMaster->subscribeEvent(Slider::EventValueChanged, &SoundConfig::handleVolumeMasterChanged, this);

        mDriverBox = getCombobox("Table");
        mDriverBox->subscribeEvent(Combobox::EventListSelectionAccepted, &SoundConfig::handleSelectDriver, this);

        mDriverConfig = getWindow("DriverSettings");

        centerWindow();
    }

    SoundConfig::~SoundConfig()
    {
    }

    bool SoundConfig::handleOK()
    {
        ListboxTextItem* item = dynamic_cast<ListboxTextItem*>(mDriverBox->getSelectedItem());
        if (item != 0)
        {
            SoundDriver* activeDriver = SoundManager::getSingleton().getActiveDriver();
            if (item->getText() != activeDriver->getName())
            {
                // Nicht der aktive Treiber, also �ndern.
                SoundDriver* driver = SoundManager::getSingleton().getDriverByName(item->getText().c_str());
                if (driver != NULL)
                {
                    SoundManager::getSingleton().setActiveDriver(driver);
                }
            }
        }
        mCurrentConfig->apply();
        setVisible(false);
        destroyWindow();
        return true;
    }

    bool SoundConfig::handleVolumeMusicChanged()
    {
        SoundManager::getSingleton().getActiveDriver()->setDefaultMusicVolume(mVolumeMusic->getCurrentValue());
        return true;
    }

    bool SoundConfig::handleVolumeSoundChanged()
    {
        SoundManager::getSingleton().getActiveDriver()->setDefaultSoundVolume(mVolumeSound->getCurrentValue());
        return true;
    }

    bool SoundConfig::handleVolumeMasterChanged()
    {
        SoundManager::getSingleton().getActiveDriver()->setMasterVolume(mVolumeMaster->getCurrentValue());
        return true;
    }

    void SoundConfig::registerDriverConfig(SoundDriverConfigComponent* wnd)
    {
        mDriverConfigs.push_back(wnd);
        wnd->addTo(mDriverConfig);

        mDriverBox->addItem(new ListboxTextItem(wnd->getDriverName(), mDriverBox->getItemCount(), wnd));
    }

    bool SoundConfig::handleClose()
    {
        setVisible(false);
        return true;
    }

    bool SoundConfig::handleSelectDriver()
    {
        if (mDriverBox->getSelectedItem() != NULL)
        {
            setDriverPage(mDriverBox->getSelectedItem()->getText());
            mCurrentConfig->readDriverData();
            return true;
        }

        return false;
    }

    void SoundConfig::setVisible(bool visible, bool destroyAfterHide)
    {
        AbstractWindow::setVisible(visible, destroyAfterHide);
        if (visible)
        {
            update();
        }
    }

    void SoundConfig::update()
    {
        setDriverPage(SoundManager::getSingleton().getActiveDriver()->getName());
        mCurrentConfig->readDriverData();
    }

    void SoundConfig::setDriverPage(const CeGuiString& drivername)
    {
        for (std::list<SoundDriverConfigComponent*>::iterator it = mDriverConfigs.begin(); it != mDriverConfigs.end();
             it++)
        {
            SoundDriverConfigComponent* curr = *it;
            if (drivername == curr->getDriverName() && mCurrentConfig != curr)
            {
                if (mCurrentConfig != NULL)
                {
                    mCurrentConfig->setVisible(false);
                }
                curr->setVisible(true);
                mCurrentConfig = curr;
                return;
            }
        }
    }
}
