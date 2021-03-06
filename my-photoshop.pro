######################################################################
# Automatically generated by qmake (3.1) Sat Nov 28 22:08:28 2020
######################################################################

TEMPLATE = app
TARGET = my-photoshop
INCLUDEPATH += .
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/graphics/TabPanel.hh \
           src/graphics/TabWidget.hh \
           src/graphics/UserInterface.hh \
           src/model/Matrix.hh \
           src/model/Picture.hh \
           src/model/PixelMod.hh \
           src/model/Tracing.hh \
           src/model/Treatment.hh \
           src/graphics/picture/PictureArea.hh \
           src/graphics/picture/PictureButton.hh \
           src/graphics/picture/PictureManager.hh \
           src/graphics/picture/PictureModifier.hh \
           src/graphics/picture/PictureViewer.hh \
           src/graphics/picture/SelectionTool.hh \
           src/graphics/tool/AffineOperationChooser.hh \
           src/graphics/tool/AlgebricOperationChooser.hh \
           src/graphics/tool/ColorChooser.hh \
           src/graphics/tool/ColorConvertOperationChooser.hh \
           src/graphics/tool/ConvolveOperationChooser.hh \
           src/graphics/tool/Histogram.hh \
           src/graphics/tool/MatrixGenerator.hh \
           src/graphics/tool/Previewer.hh \
           src/graphics/tool/ToolBoxChooser.hh \
           src/graphics/tool/TracingManager.hh \
           src/graphics/util/MPushButton.hh \
           src/model/operation/AffineTransformationOperation.hh \
           src/model/operation/AlgebricOperation.hh \
           src/model/operation/ColorConvertOperation.hh \
           src/model/operation/ConvolveOperation.hh \
           src/model/operation/CopyOperation.hh \
           src/model/operation/CropOperation.hh \
           src/model/operation/CutOperation.hh \
           src/model/operation/MergeOperation.hh \
           src/model/operation/Operation.hh \
           src/model/operation/SeamCarvingOperation.hh
SOURCES += src/Application.cc \
           src/graphics/TabPanel.cc \
           src/graphics/TabWidget.cc \
           src/graphics/UserInterface.cc \
           src/graphics/UserInterfaceAction.cc \
           src/graphics/UserInterfaceClipBoard.cc \
           src/graphics/UserInterfaceConvolveAction.cc \
           src/graphics/UserInterfaceMenu.cc \
           src/graphics/UserInterfaceToolBars.cc \
           src/graphics/UserInterfaceToolBox.cc \
           src/model/Picture.cc \
           src/model/Tracing.cc \
           src/model/Treatment.cc \
           src/graphics/picture/PictureArea.cc \
           src/graphics/picture/PictureButton.cc \
           src/graphics/picture/PictureManager.cc \
           src/graphics/picture/PictureModifier.cc \
           src/graphics/picture/PictureViewer.cc \
           src/graphics/picture/SelectionTool.cc \
           src/graphics/tool/AffineOperationChooser.cc \
           src/graphics/tool/AlgebricOperationChooser.cc \
           src/graphics/tool/ColorChooser.cc \
           src/graphics/tool/ColorConvertOperationChooser.cc \
           src/graphics/tool/ConvolveOperationChooser.cc \
           src/graphics/tool/Histogram.cc \
           src/graphics/tool/MatrixGenerator.cc \
           src/graphics/tool/Previewer.cc \
           src/graphics/tool/ToolBoxChooser.cc \
           src/graphics/tool/TracingManager.cc \
           src/graphics/util/MPushButton.cc \
           src/model/operation/AffineTransformationOperation.cc \
           src/model/operation/AlgebricOperation.cc \
           src/model/operation/ColorConvertOperation.cc \
           src/model/operation/ColorConvertOperationKernel.cc \
           src/model/operation/ConvolveOperation.cc \
           src/model/operation/ConvolveOperationKernel.cc \
           src/model/operation/CopyOperation.cc \
           src/model/operation/CropOperation.cc \
           src/model/operation/CutOperation.cc \
           src/model/operation/MergeOperation.cc \
           src/model/operation/Operation.cc \
           src/model/operation/SeamCarvingOperation.cc
