/************************************************************************
    filename:   RLCombobox.h
    created:    12/6/2004
    author:     Paul D Turner
    
    purpose:    Interface to Rastullah look combo box class
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
#ifndef _RLCombobox_h_
#define _RLCombobox_h_

#include "RLModule.h"
#include "elements/CEGUICombobox.h"
#include "CEGUIWindowFactory.h"

// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
    Combobox class for the Rastullah look Gui scheme
*/
class RASTULLAHLOOK_API RLCombobox : public Combobox
{
public:
    /*************************************************************************
        Constants
    *************************************************************************/
    // type name for this widget
    static const utf8   WidgetTypeName[];               //!< The unique typename of this widget

    // image / imageset related
    static const utf8   ImagesetName[];             //!< Name of the imageset to use for rendering.
    static const utf8   ButtonNormalImageName[];    //!< Name of the image to use for rendering the button normally
    static const utf8   ButtonHighlightedImageName[];   //!< Name of the image to use for rendering the button highlighted.

    // component widget type names
    static const utf8*  EditboxTypeName;            //!< Type name of widget to be created as the edit box.
    static const utf8*  DropListTypeName;           //!< Type name of widget to be created as the drop list.
    static const utf8*  ButtonTypeName;             //!< Type name of widget to be created as the push button.


    /*************************************************************************
        Construction and Destruction
    *************************************************************************/
    /*!
    \brief
        Constructor for Rastullah Combobox
    */
    RLCombobox(const String& type, const String& name);


    /*!
    \brief
        Destructor for Rastullah Combobox
    */
    virtual ~RLCombobox(void);


protected:
    /*************************************************************************
        Overridden Implementation Rendering Functions
    *************************************************************************/
    /*!
    \brief
        Perform rendering for this widget
    */
    virtual void    drawSelf(float z);


    /*************************************************************************
        Implementation methods
    *************************************************************************/
    /*!
    \brief
        Setup size and position for the component widgets attached to this Combobox.

    \return
        Nothing.
    */
    virtual void    layoutComponentWidgets();


    /*!
    \brief
        Create, initialise, and return a pointer to an Editbox widget to be used as part
        of this Combobox.

    \return
        Pointer to an Editbox derived class.
    */
    virtual Editbox*    createEditbox(void) const;


    /*!
    \brief
        Create, initialise, and return a pointer to a PushButton widget to be used as part
        of this Combobox.

    \return
        Pointer to a PushButton derived class.
    */
    virtual PushButton* createPushButton(void) const;


    /*!
    \brief
        Create, initialise, and return a pointer to a ComboDropList widget to be used as part
        of this Combobox.

    \return
        Pointer to a ComboDropList derived class.
    */
    virtual ComboDropList*  createDropList(void) const;


    /*************************************************************************
        Implementation Data
    *************************************************************************/
};

/*!
\brief
    Factory class for producing RLCombobox objects
*/
class RASTULLAHLOOK_API RLComboboxFactory : public WindowFactory
{
public:
    /*************************************************************************
        Construction and Destruction
    *************************************************************************/
    RLComboboxFactory(void) : WindowFactory(RLCombobox::WidgetTypeName) { }
    ~RLComboboxFactory(void){}


    /*!
    \brief
        Create a new Window object of whatever type this WindowFactory produces.

    \param name
        A unique name that is to be assigned to the newly created Window object

    \return
        Pointer to the new Window object.
    */
    Window* createWindow(const String& name);


    /*!
    \brief
        Destroys the given Window object.

    \param window
        Pointer to the Window object to be destroyed.

    \return
        Nothing.
    */
    virtual void    destroyWindow(Window* window)    { if (window->getType() == d_type) delete window; }
};

} // End of  CEGUI namespace section

#endif  // end of guard _RLCombobox_h_
