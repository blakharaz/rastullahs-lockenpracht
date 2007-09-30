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

#include "stdinc.h"

#include "SaveGameFileWriter.h"

#include "SaveGameManager.h"

#include <XmlProcessor.h>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <Properties.h>

#include <OgreResourceManager.h>
#include <CEGUIPropertyHelper.h>
#include <CoreSubsystem.h>
#include <ContentModule.h>
#include <TimeSource.h>

#include <ctime>

using namespace XERCES_CPP_NAMESPACE;
using namespace Ogre;

namespace rl
{
    void SaveGameFileWriter::buildSaveGameFile(SaveGameFile *file, const SaveGameDataSet &set)
    {
        //@toto: build
        initializeXml();

        XMLCh tempStr[100];
        XMLString::transcode("LS", tempStr, 99);
        mImplementation = DOMImplementationRegistry::getDOMImplementation(tempStr);
        mWriter = static_cast<DOMImplementationLS*>(mImplementation)->createDOMWriter();
        mTarget = file->getFormatTarget();
        mDocument = static_cast<DOMImplementation*>(mImplementation)->createDocument(0, XMLString::transcode("SaveGameFile"), 0);

        if (mWriter->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, true))
            mWriter->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, true);

        if (mWriter->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
             mWriter->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);

        mDocument->setNodeValue(XMLString::transcode("SaveGameFile")); //Set name of document root node

        //Write SaveGameVersion
        setAttributeValueAsString(mDocument->getDocumentElement(), "Version", "0.1");

        //Write modul of save game
        DOMElement* header = appendChildElement(mDocument, mDocument->getDocumentElement(), "header");
        
        PropertySet* headerSet = file->getAllProperties();
        for(PropertySetMap::const_iterator it_header = headerSet->begin(); it_header != headerSet->end(); it_header++)
        {
            this->processProperty(header, PropertyEntry(it_header->first.c_str(), it_header->second));
        }

        //Write globals
        DOMElement* globals = appendChildElement(mDocument, mDocument->getDocumentElement(), "globals");
        DOMElement* gameTime = appendChildElement(mDocument, globals, "gametime");
        TimeSource* gameTimeSource = TimeSourceManager::getSingleton().getTimeSource(TimeSource::GAMETIME);
        setAttributeValueAsInteger(gameTime, "milliseconds", gameTimeSource->getClock());

        for(SaveGameDataSet::const_iterator data_iter = set.begin(); data_iter != set.end(); data_iter++)
        {
            (*data_iter)->writeData(this);
        }

        mWriter->writeNode(mTarget, *mDocument);


        mWriter->release();

        delete mDocument;
        delete mTarget;

        shutdownXml();
    }
}