# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/fusion/Rastullah/rl/editors/Lockenwickler/ui files/MyTerrainManagerDock.ui'
#
# Created: Sat May 30 17:08:29 2009
#      by: PyQt4 UI code generator 4.4.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_TerrainManagerUi(object):
    def setupUi(self, TerrainManagerUi):
        TerrainManagerUi.setObjectName("TerrainManagerUi")
        TerrainManagerUi.resize(380, 769)
        self.gridLayout_4 = QtGui.QGridLayout(TerrainManagerUi)
        self.gridLayout_4.setMargin(1)
        self.gridLayout_4.setSpacing(1)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.terrainListComboBox = QtGui.QComboBox(TerrainManagerUi)
        self.terrainListComboBox.setObjectName("terrainListComboBox")
        self.terrainListComboBox.addItem(QtCore.QString())
        self.gridLayout_4.addWidget(self.terrainListComboBox, 0, 0, 1, 1)
        self.toggleTerrainVisibilityButton = QtGui.QToolButton(TerrainManagerUi)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/iconsPref/14_layer_invisible.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        icon.addPixmap(QtGui.QPixmap(":/iconsPref/14_layer_visible.png"), QtGui.QIcon.Normal, QtGui.QIcon.On)
        self.toggleTerrainVisibilityButton.setIcon(icon)
        self.toggleTerrainVisibilityButton.setCheckable(True)
        self.toggleTerrainVisibilityButton.setObjectName("toggleTerrainVisibilityButton")
        self.gridLayout_4.addWidget(self.toggleTerrainVisibilityButton, 0, 1, 1, 1)
        self.editTerrainButton = QtGui.QToolButton(TerrainManagerUi)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/iconsPref/colors.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.editTerrainButton.setIcon(icon1)
        self.editTerrainButton.setCheckable(True)
        self.editTerrainButton.setObjectName("editTerrainButton")
        self.gridLayout_4.addWidget(self.editTerrainButton, 0, 2, 1, 1)
        self.deleteTerrainButton = QtGui.QToolButton(TerrainManagerUi)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/iconsPref/editdelete.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.deleteTerrainButton.setIcon(icon2)
        self.deleteTerrainButton.setObjectName("deleteTerrainButton")
        self.gridLayout_4.addWidget(self.deleteTerrainButton, 0, 3, 1, 1)
        self.toolBox = QtGui.QToolBox(TerrainManagerUi)
        self.toolBox.setFrameShape(QtGui.QFrame.NoFrame)
        self.toolBox.setFrameShadow(QtGui.QFrame.Sunken)
        self.toolBox.setObjectName("toolBox")
        self.page = QtGui.QWidget()
        self.page.setGeometry(QtCore.QRect(0, 0, 378, 654))
        self.page.setObjectName("page")
        self.gridLayout = QtGui.QGridLayout(self.page)
        self.gridLayout.setMargin(1)
        self.gridLayout.setSpacing(1)
        self.gridLayout.setObjectName("gridLayout")
        self.label_6 = QtGui.QLabel(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_6.sizePolicy().hasHeightForWidth())
        self.label_6.setSizePolicy(sizePolicy)
        self.label_6.setAlignment(QtCore.Qt.AlignCenter)
        self.label_6.setObjectName("label_6")
        self.gridLayout.addWidget(self.label_6, 0, 0, 1, 2)
        self.label = QtGui.QLabel(self.page)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 1, 0, 1, 1)
        self.nameLineEdit = QtGui.QLineEdit(self.page)
        self.nameLineEdit.setObjectName("nameLineEdit")
        self.gridLayout.addWidget(self.nameLineEdit, 1, 1, 1, 1)
        self.label_2 = QtGui.QLabel(self.page)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 2, 0, 1, 1)
        self.sizeComboBox = QtGui.QComboBox(self.page)
        self.sizeComboBox.setObjectName("sizeComboBox")
        self.sizeComboBox.addItem(QtCore.QString())
        self.sizeComboBox.addItem(QtCore.QString())
        self.sizeComboBox.addItem(QtCore.QString())
        self.sizeComboBox.addItem(QtCore.QString())
        self.sizeComboBox.addItem(QtCore.QString())
        self.sizeComboBox.addItem(QtCore.QString())
        self.sizeComboBox.addItem(QtCore.QString())
        self.sizeComboBox.addItem(QtCore.QString())
        self.gridLayout.addWidget(self.sizeComboBox, 2, 1, 1, 1)
        self.positionSpinBoxX = QtGui.QDoubleSpinBox(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.positionSpinBoxX.sizePolicy().hasHeightForWidth())
        self.positionSpinBoxX.setSizePolicy(sizePolicy)
        self.positionSpinBoxX.setMinimum(-999999999.0)
        self.positionSpinBoxX.setMaximum(999999999.0)
        self.positionSpinBoxX.setProperty("value", QtCore.QVariant(0.0))
        self.positionSpinBoxX.setObjectName("positionSpinBoxX")
        self.gridLayout.addWidget(self.positionSpinBoxX, 3, 1, 1, 1)
        self.label_11 = QtGui.QLabel(self.page)
        self.label_11.setObjectName("label_11")
        self.gridLayout.addWidget(self.label_11, 4, 0, 1, 1)
        self.positionSpinBoxY = QtGui.QDoubleSpinBox(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.positionSpinBoxY.sizePolicy().hasHeightForWidth())
        self.positionSpinBoxY.setSizePolicy(sizePolicy)
        self.positionSpinBoxY.setMinimum(-999999999.0)
        self.positionSpinBoxY.setMaximum(999999999.0)
        self.positionSpinBoxY.setObjectName("positionSpinBoxY")
        self.gridLayout.addWidget(self.positionSpinBoxY, 4, 1, 1, 1)
        self.positionSpinBoxZ = QtGui.QDoubleSpinBox(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.positionSpinBoxZ.sizePolicy().hasHeightForWidth())
        self.positionSpinBoxZ.setSizePolicy(sizePolicy)
        self.positionSpinBoxZ.setMinimum(-999999999.0)
        self.positionSpinBoxZ.setMaximum(999999999.0)
        self.positionSpinBoxZ.setObjectName("positionSpinBoxZ")
        self.gridLayout.addWidget(self.positionSpinBoxZ, 5, 1, 1, 1)
        self.extendsSpinBoxX = QtGui.QSpinBox(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.extendsSpinBoxX.sizePolicy().hasHeightForWidth())
        self.extendsSpinBoxX.setSizePolicy(sizePolicy)
        self.extendsSpinBoxX.setCorrectionMode(QtGui.QAbstractSpinBox.CorrectToNearestValue)
        self.extendsSpinBoxX.setMinimum(0)
        self.extendsSpinBoxX.setMaximum(10000)
        self.extendsSpinBoxX.setProperty("value", QtCore.QVariant(128))
        self.extendsSpinBoxX.setObjectName("extendsSpinBoxX")
        self.gridLayout.addWidget(self.extendsSpinBoxX, 6, 1, 1, 1)
        self.label_3 = QtGui.QLabel(self.page)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 7, 0, 1, 1)
        self.extendsSpinBoxY = QtGui.QSpinBox(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.extendsSpinBoxY.sizePolicy().hasHeightForWidth())
        self.extendsSpinBoxY.setSizePolicy(sizePolicy)
        self.extendsSpinBoxY.setCorrectionMode(QtGui.QAbstractSpinBox.CorrectToNearestValue)
        self.extendsSpinBoxY.setMinimum(0)
        self.extendsSpinBoxY.setMaximum(10000)
        self.extendsSpinBoxY.setProperty("value", QtCore.QVariant(128))
        self.extendsSpinBoxY.setObjectName("extendsSpinBoxY")
        self.gridLayout.addWidget(self.extendsSpinBoxY, 7, 1, 1, 1)
        self.extendsSpinBoxZ = QtGui.QSpinBox(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.extendsSpinBoxZ.sizePolicy().hasHeightForWidth())
        self.extendsSpinBoxZ.setSizePolicy(sizePolicy)
        self.extendsSpinBoxZ.setCorrectionMode(QtGui.QAbstractSpinBox.CorrectToNearestValue)
        self.extendsSpinBoxZ.setMinimum(0)
        self.extendsSpinBoxZ.setMaximum(10000)
        self.extendsSpinBoxZ.setProperty("value", QtCore.QVariant(128))
        self.extendsSpinBoxZ.setObjectName("extendsSpinBoxZ")
        self.gridLayout.addWidget(self.extendsSpinBoxZ, 8, 1, 1, 1)
        self.label_10 = QtGui.QLabel(self.page)
        self.label_10.setObjectName("label_10")
        self.gridLayout.addWidget(self.label_10, 9, 0, 1, 1)
        self.terrainHeightSpinBox = QtGui.QDoubleSpinBox(self.page)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.terrainHeightSpinBox.sizePolicy().hasHeightForWidth())
        self.terrainHeightSpinBox.setSizePolicy(sizePolicy)
        self.terrainHeightSpinBox.setMaximum(1.0)
        self.terrainHeightSpinBox.setSingleStep(0.1)
        self.terrainHeightSpinBox.setProperty("value", QtCore.QVariant(0.5))
        self.terrainHeightSpinBox.setObjectName("terrainHeightSpinBox")
        self.gridLayout.addWidget(self.terrainHeightSpinBox, 9, 1, 1, 1)
        self.createTerrainButton = QtGui.QPushButton(self.page)
        self.createTerrainButton.setObjectName("createTerrainButton")
        self.gridLayout.addWidget(self.createTerrainButton, 10, 0, 1, 2)
        spacerItem = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.gridLayout.addItem(spacerItem, 11, 0, 1, 1)
        self.toolBox.addItem(self.page, "")
        self.page_2 = QtGui.QWidget()
        self.page_2.setGeometry(QtCore.QRect(0, 0, 378, 654))
        self.page_2.setObjectName("page_2")
        self.gridLayout_3 = QtGui.QGridLayout(self.page_2)
        self.gridLayout_3.setMargin(1)
        self.gridLayout_3.setSpacing(1)
        self.gridLayout_3.setObjectName("gridLayout_3")
        spacerItem1 = QtGui.QSpacerItem(20, 451, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.gridLayout_3.addItem(spacerItem1, 6, 1, 1, 1)
        self.label_12 = QtGui.QLabel(self.page_2)
        self.label_12.setObjectName("label_12")
        self.gridLayout_3.addWidget(self.label_12, 1, 0, 1, 1)
        self.editIntensitySlider = QtGui.QSlider(self.page_2)
        self.editIntensitySlider.setMinimum(-50)
        self.editIntensitySlider.setMaximum(50)
        self.editIntensitySlider.setProperty("value", QtCore.QVariant(1))
        self.editIntensitySlider.setOrientation(QtCore.Qt.Horizontal)
        self.editIntensitySlider.setObjectName("editIntensitySlider")
        self.gridLayout_3.addWidget(self.editIntensitySlider, 1, 1, 1, 1)
        self.label_13 = QtGui.QLabel(self.page_2)
        self.label_13.setObjectName("label_13")
        self.gridLayout_3.addWidget(self.label_13, 1, 2, 1, 1)
        self.editBrushButton = QtGui.QPushButton(self.page_2)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.editBrushButton.sizePolicy().hasHeightForWidth())
        self.editBrushButton.setSizePolicy(sizePolicy)
        self.editBrushButton.setMinimumSize(QtCore.QSize(130, 130))
        self.editBrushButton.setObjectName("editBrushButton")
        self.gridLayout_3.addWidget(self.editBrushButton, 3, 1, 1, 1)
        self.label_14 = QtGui.QLabel(self.page_2)
        self.label_14.setObjectName("label_14")
        self.gridLayout_3.addWidget(self.label_14, 3, 0, 1, 1)
        self.label_15 = QtGui.QLabel(self.page_2)
        self.label_15.setObjectName("label_15")
        self.gridLayout_3.addWidget(self.label_15, 2, 0, 1, 1)
        self.label_16 = QtGui.QLabel(self.page_2)
        self.label_16.setObjectName("label_16")
        self.gridLayout_3.addWidget(self.label_16, 2, 2, 1, 1)
        self.editBrushSizeSlider = QtGui.QSlider(self.page_2)
        self.editBrushSizeSlider.setMinimum(1)
        self.editBrushSizeSlider.setMaximum(50)
        self.editBrushSizeSlider.setProperty("value", QtCore.QVariant(2))
        self.editBrushSizeSlider.setOrientation(QtCore.Qt.Horizontal)
        self.editBrushSizeSlider.setObjectName("editBrushSizeSlider")
        self.gridLayout_3.addWidget(self.editBrushSizeSlider, 2, 1, 1, 1)
        self.setHeightButton = QtGui.QPushButton(self.page_2)
        self.setHeightButton.setCheckable(True)
        self.setHeightButton.setObjectName("setHeightButton")
        self.gridLayout_3.addWidget(self.setHeightButton, 4, 0, 1, 3)
        self.editSmoothButton = QtGui.QPushButton(self.page_2)
        self.editSmoothButton.setCheckable(True)
        self.editSmoothButton.setObjectName("editSmoothButton")
        self.gridLayout_3.addWidget(self.editSmoothButton, 5, 0, 1, 3)
        self.toolBox.addItem(self.page_2, "")
        self.page_3 = QtGui.QWidget()
        self.page_3.setGeometry(QtCore.QRect(0, 0, 378, 654))
        self.page_3.setObjectName("page_3")
        self.gridLayout_2 = QtGui.QGridLayout(self.page_3)
        self.gridLayout_2.setMargin(1)
        self.gridLayout_2.setSpacing(1)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.label_21 = QtGui.QLabel(self.page_3)
        self.label_21.setObjectName("label_21")
        self.gridLayout_2.addWidget(self.label_21, 0, 2, 1, 1)
        self.label_18 = QtGui.QLabel(self.page_3)
        self.label_18.setObjectName("label_18")
        self.gridLayout_2.addWidget(self.label_18, 0, 0, 1, 1)
        self.label_20 = QtGui.QLabel(self.page_3)
        self.label_20.setObjectName("label_20")
        self.gridLayout_2.addWidget(self.label_20, 1, 0, 1, 1)
        self.paintIntensitySlider = QtGui.QSlider(self.page_3)
        self.paintIntensitySlider.setMinimum(1)
        self.paintIntensitySlider.setMaximum(40)
        self.paintIntensitySlider.setSingleStep(1)
        self.paintIntensitySlider.setProperty("value", QtCore.QVariant(20))
        self.paintIntensitySlider.setOrientation(QtCore.Qt.Horizontal)
        self.paintIntensitySlider.setObjectName("paintIntensitySlider")
        self.gridLayout_2.addWidget(self.paintIntensitySlider, 0, 1, 1, 1)
        spacerItem2 = QtGui.QSpacerItem(20, 451, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.gridLayout_2.addItem(spacerItem2, 3, 1, 1, 1)
        self.paintBrushSizeSlider = QtGui.QSlider(self.page_3)
        self.paintBrushSizeSlider.setProperty("value", QtCore.QVariant(2))
        self.paintBrushSizeSlider.setOrientation(QtCore.Qt.Horizontal)
        self.paintBrushSizeSlider.setObjectName("paintBrushSizeSlider")
        self.gridLayout_2.addWidget(self.paintBrushSizeSlider, 1, 1, 1, 1)
        self.paintBrushButton = QtGui.QPushButton(self.page_3)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.paintBrushButton.sizePolicy().hasHeightForWidth())
        self.paintBrushButton.setSizePolicy(sizePolicy)
        self.paintBrushButton.setMinimumSize(QtCore.QSize(130, 130))
        self.paintBrushButton.setObjectName("paintBrushButton")
        self.gridLayout_2.addWidget(self.paintBrushButton, 2, 1, 1, 1)
        self.label_17 = QtGui.QLabel(self.page_3)
        self.label_17.setObjectName("label_17")
        self.gridLayout_2.addWidget(self.label_17, 1, 2, 1, 1)
        self.label_19 = QtGui.QLabel(self.page_3)
        self.label_19.setObjectName("label_19")
        self.gridLayout_2.addWidget(self.label_19, 2, 0, 1, 1)
        self.toolBox.addItem(self.page_3, "")
        self.gridLayout_4.addWidget(self.toolBox, 1, 0, 1, 4)
        self.label_6.setBuddy(self.nameLineEdit)
        self.label.setBuddy(self.nameLineEdit)
        self.label_2.setBuddy(self.sizeComboBox)
        self.label_11.setBuddy(self.extendsSpinBoxX)
        self.label_3.setBuddy(self.extendsSpinBoxX)
        self.label_10.setBuddy(self.extendsSpinBoxX)
        self.label_12.setBuddy(self.editIntensitySlider)
        self.label_14.setBuddy(self.editBrushButton)
        self.label_15.setBuddy(self.editIntensitySlider)
        self.label_18.setBuddy(self.editIntensitySlider)
        self.label_20.setBuddy(self.editIntensitySlider)
        self.label_19.setBuddy(self.editBrushButton)

        self.retranslateUi(TerrainManagerUi)
        self.toolBox.setCurrentIndex(2)
        self.sizeComboBox.setCurrentIndex(3)
        QtCore.QObject.connect(self.editIntensitySlider, QtCore.SIGNAL("sliderMoved(int)"), self.label_13.setNum)
        QtCore.QObject.connect(self.editBrushSizeSlider, QtCore.SIGNAL("valueChanged(int)"), self.label_16.setNum)
        QtCore.QObject.connect(self.paintBrushSizeSlider, QtCore.SIGNAL("valueChanged(int)"), self.label_17.setNum)
        QtCore.QObject.connect(self.paintIntensitySlider, QtCore.SIGNAL("valueChanged(int)"), self.label_21.setNum)
        QtCore.QObject.connect(self.setHeightButton, QtCore.SIGNAL("toggled(bool)"), self.editIntensitySlider.setDisabled)
        QtCore.QObject.connect(self.setHeightButton, QtCore.SIGNAL("toggled(bool)"), self.editBrushButton.setDisabled)
        QtCore.QObject.connect(self.setHeightButton, QtCore.SIGNAL("toggled(bool)"), self.editBrushSizeSlider.setDisabled)
        QtCore.QObject.connect(self.setHeightButton, QtCore.SIGNAL("toggled(bool)"), self.editSmoothButton.setDisabled)
        QtCore.QObject.connect(self.editSmoothButton, QtCore.SIGNAL("toggled(bool)"), self.setHeightButton.setDisabled)
        QtCore.QMetaObject.connectSlotsByName(TerrainManagerUi)
        TerrainManagerUi.setTabOrder(self.editIntensitySlider, self.editBrushButton)
        TerrainManagerUi.setTabOrder(self.editBrushButton, self.extendsSpinBoxZ)
        TerrainManagerUi.setTabOrder(self.extendsSpinBoxZ, self.createTerrainButton)
        TerrainManagerUi.setTabOrder(self.createTerrainButton, self.terrainListComboBox)
        TerrainManagerUi.setTabOrder(self.terrainListComboBox, self.positionSpinBoxX)
        TerrainManagerUi.setTabOrder(self.positionSpinBoxX, self.positionSpinBoxY)
        TerrainManagerUi.setTabOrder(self.positionSpinBoxY, self.positionSpinBoxZ)
        TerrainManagerUi.setTabOrder(self.positionSpinBoxZ, self.terrainHeightSpinBox)
        TerrainManagerUi.setTabOrder(self.terrainHeightSpinBox, self.nameLineEdit)
        TerrainManagerUi.setTabOrder(self.nameLineEdit, self.sizeComboBox)
        TerrainManagerUi.setTabOrder(self.sizeComboBox, self.extendsSpinBoxX)
        TerrainManagerUi.setTabOrder(self.extendsSpinBoxX, self.extendsSpinBoxY)

    def retranslateUi(self, TerrainManagerUi):
        TerrainManagerUi.setWindowTitle(QtGui.QApplication.translate("TerrainManagerUi", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.terrainListComboBox.setItemText(0, QtGui.QApplication.translate("TerrainManagerUi", "No Terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.toggleTerrainVisibilityButton.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Delete the current terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.toggleTerrainVisibilityButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.editTerrainButton.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Delete the current terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.editTerrainButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.deleteTerrainButton.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Delete the current terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.deleteTerrainButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.label_6.setText(QtGui.QApplication.translate("TerrainManagerUi", "Geometry", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Name of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("TerrainManagerUi", "&Name", None, QtGui.QApplication.UnicodeUTF8))
        self.nameLineEdit.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Name of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Vertex density", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("TerrainManagerUi", "&Size", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Vertex density", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(0, QtGui.QApplication.translate("TerrainManagerUi", "8", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(1, QtGui.QApplication.translate("TerrainManagerUi", "16", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(2, QtGui.QApplication.translate("TerrainManagerUi", "32", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(3, QtGui.QApplication.translate("TerrainManagerUi", "64", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(4, QtGui.QApplication.translate("TerrainManagerUi", "128", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(5, QtGui.QApplication.translate("TerrainManagerUi", "256", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(6, QtGui.QApplication.translate("TerrainManagerUi", "512", None, QtGui.QApplication.UnicodeUTF8))
        self.sizeComboBox.setItemText(7, QtGui.QApplication.translate("TerrainManagerUi", "1024", None, QtGui.QApplication.UnicodeUTF8))
        self.positionSpinBoxX.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Position of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.positionSpinBoxX.setPrefix(QtGui.QApplication.translate("TerrainManagerUi", "X:", None, QtGui.QApplication.UnicodeUTF8))
        self.label_11.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Position of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.label_11.setText(QtGui.QApplication.translate("TerrainManagerUi", "&Position", None, QtGui.QApplication.UnicodeUTF8))
        self.positionSpinBoxY.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Position of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.positionSpinBoxY.setPrefix(QtGui.QApplication.translate("TerrainManagerUi", "Y:", None, QtGui.QApplication.UnicodeUTF8))
        self.positionSpinBoxZ.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "Position of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.positionSpinBoxZ.setPrefix(QtGui.QApplication.translate("TerrainManagerUi", "Z:", None, QtGui.QApplication.UnicodeUTF8))
        self.extendsSpinBoxX.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The extends of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.extendsSpinBoxX.setPrefix(QtGui.QApplication.translate("TerrainManagerUi", "X:", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The extends of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("TerrainManagerUi", "&Extends", None, QtGui.QApplication.UnicodeUTF8))
        self.extendsSpinBoxY.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The extends of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.extendsSpinBoxY.setPrefix(QtGui.QApplication.translate("TerrainManagerUi", "Y:", None, QtGui.QApplication.UnicodeUTF8))
        self.extendsSpinBoxZ.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The extends of the terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.extendsSpinBoxZ.setPrefix(QtGui.QApplication.translate("TerrainManagerUi", "Z:", None, QtGui.QApplication.UnicodeUTF8))
        self.label_10.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This value means how high the vertices are placed in relation to the terrain extend in Y.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This means when you have a terrain extend in Y by 100 and the terrain height is 0.5</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">the vertices are placed in at height 50.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/helpPref/TerrainExtends1.png\" /></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_10.setText(QtGui.QApplication.translate("TerrainManagerUi", "&Height", None, QtGui.QApplication.UnicodeUTF8))
        self.terrainHeightSpinBox.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This value means how high the vertices are placed in relation to the terrain extend in Y.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This means when you have a terrain extend in Y by 100 and the terrain height is 0.5</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">the vertices are placed in at height 50.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/helpPref/TerrainExtends1.png\" /></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.createTerrainButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "Create Terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.toolBox.setItemText(self.toolBox.indexOf(self.page), QtGui.QApplication.translate("TerrainManagerUi", "Create Terrain", None, QtGui.QApplication.UnicodeUTF8))
        self.label_12.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The intensity wich is applied to the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_12.setText(QtGui.QApplication.translate("TerrainManagerUi", "Intensity", None, QtGui.QApplication.UnicodeUTF8))
        self.editIntensitySlider.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The intensity wich is applied to the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_13.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The intensity wich is applied to the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_13.setText(QtGui.QApplication.translate("TerrainManagerUi", "2", None, QtGui.QApplication.UnicodeUTF8))
        self.editBrushButton.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The brush that is applied", None, QtGui.QApplication.UnicodeUTF8))
        self.editBrushButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "PushButton", None, QtGui.QApplication.UnicodeUTF8))
        self.label_14.setText(QtGui.QApplication.translate("TerrainManagerUi", "Brush Type  ", None, QtGui.QApplication.UnicodeUTF8))
        self.label_15.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The diameter of the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_15.setText(QtGui.QApplication.translate("TerrainManagerUi", "Brush Size", None, QtGui.QApplication.UnicodeUTF8))
        self.label_16.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The diameter of the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_16.setText(QtGui.QApplication.translate("TerrainManagerUi", "2", None, QtGui.QApplication.UnicodeUTF8))
        self.editBrushSizeSlider.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The diameter of the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.setHeightButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "Set Height", None, QtGui.QApplication.UnicodeUTF8))
        self.editSmoothButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "Smooth", None, QtGui.QApplication.UnicodeUTF8))
        self.toolBox.setItemText(self.toolBox.indexOf(self.page_2), QtGui.QApplication.translate("TerrainManagerUi", "ModifyTerrain", None, QtGui.QApplication.UnicodeUTF8))
        self.label_21.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The intensity wich is applied to the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_21.setText(QtGui.QApplication.translate("TerrainManagerUi", "2", None, QtGui.QApplication.UnicodeUTF8))
        self.label_18.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The intensity wich is applied to the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_18.setText(QtGui.QApplication.translate("TerrainManagerUi", "Intensity", None, QtGui.QApplication.UnicodeUTF8))
        self.label_20.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The diameter of the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_20.setText(QtGui.QApplication.translate("TerrainManagerUi", "Brush Size", None, QtGui.QApplication.UnicodeUTF8))
        self.paintIntensitySlider.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The intensity wich is applied to the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.paintBrushSizeSlider.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The diameter of the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.paintBrushButton.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The brush that is applied", None, QtGui.QApplication.UnicodeUTF8))
        self.paintBrushButton.setText(QtGui.QApplication.translate("TerrainManagerUi", "PushButton", None, QtGui.QApplication.UnicodeUTF8))
        self.label_17.setToolTip(QtGui.QApplication.translate("TerrainManagerUi", "The diameter of the tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_17.setText(QtGui.QApplication.translate("TerrainManagerUi", "2", None, QtGui.QApplication.UnicodeUTF8))
        self.label_19.setText(QtGui.QApplication.translate("TerrainManagerUi", "Brush Type  ", None, QtGui.QApplication.UnicodeUTF8))
        self.toolBox.setItemText(self.toolBox.indexOf(self.page_3), QtGui.QApplication.translate("TerrainManagerUi", "PaintTerrain", None, QtGui.QApplication.UnicodeUTF8))

import help_rc
import icons_rc

if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    TerrainManagerUi = QtGui.QWidget()
    ui = Ui_TerrainManagerUi()
    ui.setupUi(TerrainManagerUi)
    TerrainManagerUi.show()
    sys.exit(app.exec_())

