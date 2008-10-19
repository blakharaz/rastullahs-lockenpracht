#################################################
 # Copyright (C) 2008  Stefan Stammberger
 #
 # This library is free software; you can redistribute it and/or
 # modify it under the terms of the GNU Lesser General Public
 # License as published by the Free Software Foundation; either
 # version 2.1 of the License, or (at your option) any later version.
 #
 # This library is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 # Lesser General Public License for more details.
 #
 # You should have received a copy of the GNU Lesser General Public
 # License along with this library; if not, write to the Free Software
 # Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 #################################################


import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import ogre.renderer.OGRE as og

class SceneExplorer(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.sceneTreeView = QTreeView()

        vBoxLayout = QVBoxLayout()
        vBoxLayout.addWidget(self.sceneTreeView)

        self.setLayout(vBoxLayout)

