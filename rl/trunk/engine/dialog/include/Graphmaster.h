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

#ifndef __Rl_DialogGraphMaster_H__
#define __Rl_DialogGraphMaster_H__

//--	Graphmaster.h
#include "Match.h"
#include "DialogPrerequisites.h"

#include <string>



using namespace std;


namespace rl
{
	class Nodemaster;

	class _RlDialogExport Graphmaster
	{
	public:
		Graphmaster();
		virtual ~Graphmaster();
	
		Nodemaster* add(const string &context, const string &pattern, const string &that, const string &topic,const string &templateValue);
		Match* match(const string &context, const string &pattern, const string &that, const string &topic);
	private:
		Match* match(Nodemaster *node, Nodemaster *parent, component which, const string &input, const string &star, const string &path);
	
		Nodemaster* mRoot;
		string mName;	// name of the aiml-file the graphmaster contains
	};
}
#endif
