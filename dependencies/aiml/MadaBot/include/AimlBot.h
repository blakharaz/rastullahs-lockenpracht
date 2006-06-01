/**
 * Copyright (c) 2006 Philipp Walser
 * 
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef AIML_BOT_H
#define AIML_BOT_H

#include <list>
#include "AimlUtility.h"
#include "Match.h"
#include "AimlNode.h"
#include "Response.h"
#include "AimlInterpreter.h"

namespace MadaBot
{
	template <class S> class AimlCore;
	template <class S> class AimlGraphMaster;
	template <class S> class Predicates;

	/**
	 * This class represents a dialog enabled bot
	 * The Bot uses a List of GraphMasters as LanguageData.
	 * The Graphmasters are managed by an AimlCore intance
	 * TODO: bot does not need Graphmaster-Pointers if he has access to AimlCore. Only names are needed
	 * TODO: maybe AimlCore should have pointers to its AimlBots, so if AimlCore gets deleted,
	 * all Bots get deleted, too. Without AimlCore, Bots won't work nevertheless.
	 */
	template <class S> class AimlBot
	{
	public:
		/**
		 * Constructor
		 * @param  pName name of the bot
		 * @param  pParent pointer to the parent object
		 */
		AimlBot(const S& pName, AimlCore<S>* pParent) : mName(pName), mParent(pParent){}

		/**
		 * Destructor
		 */
		virtual ~AimlBot(){}
		/**
		 * Adds a pointer to an existent GraphMaster to the bot. 
		 * All AIML dialog definitions in this GraphMaster are available for the bot
		 * @param  pGraph pointer to a loaded GraphMaster
		 */
		bool addGraphMaster(AimlGraphMaster<S>* pGraph);

		/**
		 * Respond to a user defined Message
		 * @param  pInput input string that should be responded to,
		 * @return a response, should be a pointer because it should habe polymorphical behaviour
		 */
		Response<S> respond(const S& pInput);
		
		/** 
		 * @param  pType type of the predicates
		 * @return the predicates access class for the given type
		 */
		Predicates<S>* getPredicates(const S& pType) { return NULL; }

		/**
		 * Set an folder or archive name that contains the soundfiles for voice response
		 * @param  pName name of the folder or archive
		 */
		void setVoice(const S& pName){ mVoice = pName; }
		
		/**
		* deprecated???
		 * @return the current match from a user input or NULL if no match/user input
		 */
	//	aiml::Match<S>* getCurrentMatch(){return mCurrentMatch;}

	private:
		S mName;
		S mVoice;
		typedef std::map<S, Predicates<S>*> PredicatesMap;
		PredicatesMap mPredicates;
		typedef std::list<AimlGraphMaster<S>*> GraphList;
		GraphList mGraphList;
		Match<S>* mCurrentMatch;
		AimlCore<S>* mParent;
	};

	template <class S> bool AimlBot<S>::addGraphMaster(AimlGraphMaster<S>* pGraph)
	{
		if(pGraph)
		{
			GraphList::iterator itr = mGraphList.begin();
			for(; itr != mGraphList.end(); ++itr)
			{
				if((*itr) == pGraph)
				{
					// should throw an exception
					return false;
				}
			}
			mGraphList.push_back(pGraph);
			return true;
		}
		return false;
	}

	template <class S> Response<S> AimlBot<S>::respond(const S& pInput)
	{
		Response<S> response;
		GraphPath<S> path;
		mCurrentMatch = NULL;
		// vorher noch SentenceSplittern
		path.setPattern(pInput);
		// have to set <that>, this is what the bot said before (or is it?)
		path.setThat(AimlUtility::ASTERISK);
		GraphList::iterator itr = mGraphList.begin();
		for(; itr != mGraphList.end(); ++itr)
		{
			mCurrentMatch = (*itr)->match(path);
			if(mCurrentMatch != NULL)
			{
				break;
			}
		}
		if(mCurrentMatch!= NULL)
		{
		//  TODO: interpreter shouldn't be created for every response. 
		//  Instead, create an instance in AimlCore und use that
		//  proceed in the same way with the other interpreters
			AimlInterpreter<S> interpreter;
			
			response = interpreter.process(mCurrentMatch->getNode(), this);
			//debug
			S resStr = response.getResponse();
			resStr.c_str();
		}
		else
		{
			// no match
		}
		return response;
	}
}
#endif;
