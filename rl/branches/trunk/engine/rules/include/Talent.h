/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2004 Team Pantheon. http://www.team-pantheon.de
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

#ifndef __TALENT_H__
#define __TALENT_H__

#include "RulesPrerequisites.h"

#include "Tripel.h"
#include "Eigenschaft.h"

namespace rl
{
    class _RlRulesExport Talent
    {
    private:
        const int mId;
        const CeGuiString mName;
        const CeGuiString mDescription;
        const EigenschaftTripel mEigenschaften;
        const int mEbe;
		const int mTalentGruppe;
    public:
        Talent(int id,
               const CeGuiString& name,
               const CeGuiString& description,
               const EigenschaftTripel& eigenschaften,
               int ebe,
			   int gruppe);

        bool operator==(const Talent& rhs) const;
        bool operator<(const Talent& rhs) const;
        int getId() const;
        CeGuiString getName() const;
        CeGuiString getDescription() const;
		int getEbe() const;

        /// Berechnet effektive Behinderung bei gegebener Behinderung;
        int calculateEbe(int be) const;
        EigenschaftTripel getEigenschaften() const;
    };
}
#endif
