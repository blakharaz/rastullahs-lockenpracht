/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2005 Team Pantheon. http://www.team-pantheon.de
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

#ifndef SYSTEM_PROCESSOR_H
#define SYSTEM_PROCESSOR_H

#include "DialogPrerequisites.h"
#include "../AimlProcessor.h"
#include "../NaturalLanguageProcessor.h"
#include "../AimlParser.h"
#include "../DialogSubsystem.h"

#include <string>
using namespace std;

namespace rl
{
	class SystemProcessor : public AimlProcessor
	{
	public:
		SystemProcessor(){};
		~SystemProcessor() { }
	
		string process(DOMNode* node,Match* m, const char *str, NaturalLanguageProcessor* nlp)
		{
			char* cmd=XmlHelper::getAttributeValueAsString( (DOMElement*)node,XMLString::transcode("command") );
			DialogSubsystem::getSingletonPtr()->log("SYSTEM");
			DialogSubsystem::getSingletonPtr()->log(cmd);
			if(!static_cast<string>(cmd).compare("exit"))
				nlp->mExit=true;
			if(!static_cast<string>(cmd).compare("reload"))
			{
				DialogSubsystem::getSingletonPtr()->log("RELOOOAAAD");
				nlp->processOption("load","*.aiml");
			}
			XMLString::release(&cmd);
			return "";
		}
	};
}
#endif
