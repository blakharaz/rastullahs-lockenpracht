/************************************************************************
    filename:   RLTabButton.cpp
    created:    11/08/2004
    author:     Steve Streeting
    
    purpose:    Implementation of Taharez look Tab Button widget.
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://crayzedsgui.sourceforge.net)
    Copyright (C)2004 Paul D Turner (crayzed@users.sourceforge.net)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
#include "RLTabButton.h"
#include "CEGUIImageset.h"
#include "CEGUIFont.h"


// Start of CEGUI namespace section
namespace CEGUI
{
/*************************************************************************
    Constants
*************************************************************************/
// type name for this widget
const utf8  RLTabButton::WidgetTypeName[]   = "TaharezLook/TabButton";

const utf8  RLTabButton::ImagesetName[]                 = "TaharezLook";
const utf8  RLTabButton::LeftNormalImageName[]          = "TabButtonLeftNormal";
const utf8  RLTabButton::MiddleNormalImageName[]        = "TabButtonMiddleNormal";
const utf8  RLTabButton::RightNormalImageName[]         = "TabButtonRightNormal";
const utf8  RLTabButton::UpperRightNormalImageName[]    = "TabButtonUpperRightNormal";
const utf8  RLTabButton::UpperLeftNormalImageName[]     = "TabButtonUpperLeftNormal";
const utf8  RLTabButton::UpperNormalImageName[]         = "TabButtonUpperNormal";
const utf8  RLTabButton::LowerNormalImageName[]         = "TabButtonLowerNormal";
const utf8  RLTabButton::LowerRightNormalImageName[]    = "TabButtonLowerRightNormal";
const utf8  RLTabButton::LowerLeftNormalImageName[]     = "TabButtonLowerLeftNormal";
const utf8  RLTabButton::LeftSelectedImageName[]        = "TabButtonLeftSelected";
const utf8  RLTabButton::MiddleSelectedImageName[]      = "TabButtonMiddleSelected";
const utf8  RLTabButton::RightSelectedImageName[]       = "TabButtonRightSelected";
const utf8  RLTabButton::UpperRightSelectedImageName[]  = "TabButtonUpperRightSelected";
const utf8  RLTabButton::UpperLeftSelectedImageName[]   = "TabButtonUpperLeftSelected";
const utf8  RLTabButton::UpperSelectedImageName[]       = "TabButtonUpperSelected";
const utf8  RLTabButton::LowerSelectedImageName[]       = "TabButtonLowerSelected";


/*************************************************************************
    Constructor
*************************************************************************/
RLTabButton::RLTabButton(const String& type, const String& name) :
    TabButton(type, name)
{
    Imageset* iset = ImagesetManager::getSingleton().getImageset(ImagesetName);

    // setup cache of image pointers
    d_leftSectionNormal         = &iset->getImage(LeftNormalImageName);
    d_middleSectionNormal       = &iset->getImage(MiddleNormalImageName);
    d_rightSectionNormal        = &iset->getImage(RightNormalImageName);
    d_upperLeftSectionNormal    = &iset->getImage(UpperLeftNormalImageName);
    d_upperRightSectionNormal   = &iset->getImage(UpperRightNormalImageName);
    d_upperSectionNormal        = &iset->getImage(UpperNormalImageName);
    d_lowerSectionNormal        = &iset->getImage(LowerNormalImageName);
    d_lowerLeftSectionNormal    = &iset->getImage(LowerLeftNormalImageName);
    d_lowerRightSectionNormal   = &iset->getImage(LowerRightNormalImageName);

    d_leftSectionSelected       = &iset->getImage(LeftSelectedImageName);
    d_middleSectionSelected     = &iset->getImage(MiddleSelectedImageName);
    d_rightSectionSelected      = &iset->getImage(RightSelectedImageName);
    d_upperLeftSectionSelected  = &iset->getImage(UpperLeftSelectedImageName);
    d_upperRightSectionSelected = &iset->getImage(UpperRightSelectedImageName);
    d_upperSectionSelected      = &iset->getImage(UpperSelectedImageName);
    d_lowerSectionSelected      = &iset->getImage(LowerSelectedImageName);

}


/*************************************************************************
    Destructor
*************************************************************************/
RLTabButton::~RLTabButton(void)
{
}
/*************************************************************************
    render Widget in normal state   
*************************************************************************/
void RLTabButton::drawNormal(float z)
{
    const uint INDENT = 3;
    Rect clipper(getPixelRect());

    // do nothing if the widget is totally clipped.
    if (clipper.getWidth() == 0)
    {
        return;
    }

    // get the destination screen rect for this window
    Rect absrect(getUnclippedPixelRect());

    // calculate colours to use.
    float alpha_comp = getEffectiveAlpha();
    ColourRect colours(colour(1, 1, 1, alpha_comp));

    // calculate widths for the button segments
    float leftWidth     = d_leftSectionNormal->getWidth();
    float rightWidth    = d_rightSectionNormal->getWidth();
    float topHeight     = d_upperSectionNormal->getWidth();
    float lowerHeight   = d_lowerSectionNormal->getWidth();
    float midWidth      = absrect.getWidth() - leftWidth - rightWidth;
    float midHeight     = absrect.getHeight() - topHeight - lowerHeight;

    //
    // draw the images
    //
    Vector3 pos;
    Size    sz;
    pos.d_z = z;
    pos.d_x = absrect.d_left;
    pos.d_y = absrect.d_top + INDENT;
    sz.d_width = leftWidth;
    sz.d_height = topHeight;
    d_upperLeftSectionNormal->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = midHeight - INDENT;
    d_leftSectionNormal->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = lowerHeight;
    d_lowerLeftSectionNormal->draw(pos, sz, clipper, colours);

    pos.d_x = absrect.d_left + leftWidth;
    pos.d_y = absrect.d_top + INDENT;
    sz.d_width = midWidth;
    sz.d_height = topHeight;
    d_upperSectionNormal->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = midHeight - INDENT;
    d_middleSectionNormal->draw(pos, sz, clipper, colours);

    pos.d_x = absrect.d_right - rightWidth;
    pos.d_y = absrect.d_top + INDENT;
    sz.d_width = rightWidth;
    sz.d_height = topHeight;
    d_upperRightSectionNormal->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = midHeight - INDENT;
    d_rightSectionNormal->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = lowerHeight;
    d_lowerRightSectionNormal->draw(pos, sz, clipper, colours);


    // Do bottom section
    pos.d_x = absrect.d_left + leftWidth;
    pos.d_y = absrect.d_bottom - lowerHeight ;
    sz.d_width = midWidth;
    sz.d_height = lowerHeight;
    d_lowerSectionNormal->draw(pos, sz, clipper, colours);
        

    //
    // Draw label text
    //
    absrect.d_top += (absrect.getHeight() - getFont()->getLineSpacing()) / 2;
    colours.setColours(d_normalColour);
    colours.setAlpha(alpha_comp);
    getFont()->drawText(getText(), absrect, System::getSingleton().getRenderer()->getZLayer(2), clipper, Centred, colours);
}

/*************************************************************************
render Widget in selected state 
*************************************************************************/
void RLTabButton::drawPushed(float z)
{
    Rect clipper(getPixelRect());

    // do nothing if the widget is totally clipped.
    if (clipper.getWidth() == 0)
    {
        return;
    }

    // get the destination screen rect for this window
    Rect absrect(getUnclippedPixelRect());

    // calculate colours to use.
    float alpha_comp = getEffectiveAlpha();
    ColourRect colours(colour(1, 1, 1, alpha_comp));

    // calculate widths for the button segments
    float leftWidth     = d_leftSectionSelected->getWidth();
    float rightWidth    = d_rightSectionSelected->getWidth();
    float topHeight     = d_upperSectionSelected->getWidth();
    float lowerHeight   = d_lowerSectionSelected->getWidth();
    float midWidth      = absrect.getWidth() - leftWidth - rightWidth;
    float midHeight     = absrect.getHeight() - topHeight - lowerHeight;

    //
    // draw the images
    //
    Vector3 pos;
    Size    sz;
    pos.d_z = z;
    pos.d_x = absrect.d_left;
    pos.d_y = absrect.d_top;
    sz.d_width = leftWidth;
    sz.d_height = topHeight;
    d_upperLeftSectionSelected->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = midHeight + lowerHeight;
    d_leftSectionSelected->draw(pos, sz, clipper, colours);

    pos.d_x = absrect.d_left + leftWidth;
    pos.d_y = absrect.d_top;
    sz.d_width = midWidth;
    sz.d_height = topHeight;
    d_upperSectionSelected->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = midHeight + lowerHeight;
    d_middleSectionSelected->draw(pos, sz, clipper, colours);

    pos.d_x = absrect.d_right - rightWidth;
    pos.d_y = absrect.d_top;
    sz.d_width = rightWidth;
    sz.d_height = topHeight;
    d_upperRightSectionSelected->draw(pos, sz, clipper, colours);

    pos.d_y += sz.d_height;
    sz.d_height = midHeight + lowerHeight;
    d_rightSectionSelected->draw(pos, sz, clipper, colours);

    // Do bottom section
    pos.d_x = absrect.d_left + leftWidth;
    pos.d_y = absrect.d_bottom - lowerHeight ;
    sz.d_width = midWidth;
    sz.d_height = lowerHeight;
    d_lowerSectionSelected->draw(pos, sz, clipper, colours);

    //
    // Draw label text
    //
    absrect.d_top += (absrect.getHeight() - getFont()->getLineSpacing()) / 2;
    colours.setColours(d_pushedColour);
    colours.setAlpha(alpha_comp);
    getFont()->drawText(getText(), absrect, System::getSingleton().getRenderer()->getZLayer(2), clipper, Centred, colours);
}

//////////////////////////////////////////////////////////////////////////
/*************************************************************************

    Factory Methods

*************************************************************************/
//////////////////////////////////////////////////////////////////////////
/*************************************************************************
    Create, initialise and return a RLTabButton
*************************************************************************/
Window* RLTabButtonFactory::createWindow(const String& name)
{
    RLTabButton* wnd = new RLTabButton(d_type, name);
    wnd->initialise();

    return wnd;
}

} // End of  CEGUI namespace section
