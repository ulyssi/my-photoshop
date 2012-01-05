# Add more folders to ship with the application, here
folder_01.source = qml/myphotoshop
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE1A31E8B

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    src/graphics/Utils.cc \
    src/graphics/UserInterfaceToolBar.cc \
    src/graphics/UserInterfaceMenu.cc \
    src/graphics/UserInterfaceAction.cc \
    src/graphics/UserInterface.cc \
    src/graphics/TracingManager.cc \
    src/graphics/ToolMaker.cc \
    src/graphics/PictureViewer.cc \
    src/graphics/PictureModifier.cc \
    src/graphics/PictureManager.cc \
    src/graphics/PictureButton.cc \
    src/graphics/PictureArea.cc \
    src/graphics/tool/RescaleOperationChooser.cc \
    src/graphics/tool/OperationChooser.cc \
    src/graphics/tool/ConvolveOperationChooser.cc \
    src/graphics/tool/ColorConvertOperationChooser.cc \
    src/graphics/tool/ColorChooser.cc \
    src/graphics/tool/AlgebricOperationChooser.cc \
    src/graphics/tool/AffineOperationChooser.cc \
    src/model/operation/Operation.cc \
    src/model/operation/ConvolveOperation.cc \
    src/model/operation/ColorConvertOperation.cc \
    src/model/util/FileManager.cc

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    myphotoshop64.png

HEADERS += \
    src/graphics/Utils.hh \
    src/graphics/UserInterface.hh \
    src/graphics/TracingManager.hh \
    src/graphics/ToolMaker.hh \
    src/graphics/PictureViewer.hh \
    src/graphics/PictureModifier.hh \
    src/graphics/PictureManager.hh \
    src/graphics/PictureButton.hh \
    src/graphics/PictureArea.hh \
    src/graphics/tool/RescaleOperationChooser.hh \
    src/graphics/tool/OperationChooser.hh \
    src/graphics/tool/ConvolveOperationChooser.hh \
    src/graphics/tool/ColorConvertOperationChooser.hh \
    src/graphics/tool/ColorChooser.hh \
    src/graphics/tool/AlgebricOperationChooser.hh \
    src/graphics/tool/AffineOperationChooser.hh \
    src/model/operation/Operation.hh \
    src/model/operation/ConvolveOperation.hh \
    src/model/operation/ColorConvertOperation.hh \
    src/model/util/FileManager.hh
