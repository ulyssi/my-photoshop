#-------------------------------------------------
#
# Project created by QtCreator 2012-01-05T23:44:45
#
#-------------------------------------------------

QT       += core gui

TARGET = my-photoshop
TEMPLATE = app


SOURCES += \
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
    src/Application.cc \
    src/graphics/tool/RescaleOperationChooser.cc \
    src/graphics/tool/OperationChooser.cc \
    src/graphics/tool/ConvolveOperationChooser.cc \
    src/graphics/tool/ColorConvertOperationChooser.cc \
    src/graphics/tool/ColorChooser.cc \
    src/graphics/tool/AlgebricOperationChooser.cc \
    src/graphics/tool/AffineOperationChooser.cc \
    src/model/Tracing.cc \
    src/model/Picture.cc \
    src/model/operation/Operation.cc \
    src/model/operation/ConvolveOperation.cc \
    src/model/operation/ColorConvertOperation.cc \
    src/model/util/FileManager.cc

HEADERS  += \
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
    src/model/Tracing.hh \
    src/model/Picture.hh \
    src/model/operation/Operation.hh \
    src/model/operation/ConvolveOperation.hh \
    src/model/operation/ColorConvertOperation.hh \
    src/model/util/FileManager.hh
