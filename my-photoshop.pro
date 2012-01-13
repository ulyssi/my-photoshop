######################################################################
# Automatically generated by qmake (2.01a) ven. janv. 13 10:03:05 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              src \
              src/graphics \
              src/model \
              src/graphics/picture \
              src/graphics/tool \
              src/graphics/util \
              src/model/operation
INCLUDEPATH += . \
               src/graphics \
               src/model \
               src/graphics/tool \
               src/graphics/util \
               src/graphics/picture \
               src/model/operation

# Input
HEADERS += src/graphics/TabPanel.hh \
           src/graphics/TabWidget.hh \
           src/graphics/UserInterface.hh \
           src/model/Matrix.hh \
           src/model/Picture.hh \
           src/model/PixelMod.hh \
           src/model/Tracing.hh \
           src/model/Treatment.hh \
           src/graphics/picture/PictureButton.hh \
           src/graphics/picture/PictureManager.hh \
           src/graphics/picture/PictureModifier.hh \
           src/graphics/picture/PictureViewer.hh \
           src/graphics/tool/AffineOperationChooser.hh \
           src/graphics/tool/AlgebricOperationChooser.hh \
           src/graphics/tool/ColorChooser.hh \
           src/graphics/tool/ColorConvertOperationChooser.hh \
           src/graphics/tool/ConvolveOperationChooser.hh \
           src/graphics/tool/Histogram.hh \
           src/graphics/tool/RescaleOperationChooser.hh \
           src/graphics/tool/TracingManager.hh \
           src/graphics/util/MPushButton.hh \
           src/model/operation/AffineTransformationOperation.hh \
           src/model/operation/ColorConvertOperation.hh \
           src/model/operation/ConvolveOperation.hh \
           src/model/operation/MergeOperation.hh \
           src/model/operation/Operation.hh \
           src/model/operation/RescaleOperation.hh
SOURCES += src/Application.cc \
           src/graphics/TabPanel.cc \
           src/graphics/TabWidget.cc \
           src/graphics/UserInterface.cc \
           src/graphics/UserInterfaceAction.cc \
           src/graphics/UserInterfaceMenu.cc \
           src/graphics/UserInterfaceToolBars.cc \
           src/graphics/UserInterfaceToolBox.cc \
           src/model/Picture.cc \
           src/model/Tracing.cc \
           src/model/Treatment.cc \
           src/graphics/picture/PictureButton.cc \
           src/graphics/picture/PictureManager.cc \
           src/graphics/picture/PictureModifier.cc \
           src/graphics/picture/PictureViewer.cc \
           src/graphics/tool/AffineOperationChooser.cc \
           src/graphics/tool/AlgebricOperationChooser.cc \
           src/graphics/tool/ColorChooser.cc \
           src/graphics/tool/ColorConvertOperationChooser.cc \
           src/graphics/tool/ConvolveOperationChooser.cc \
           src/graphics/tool/Histogram.cc \
           src/graphics/tool/RescaleOperationChooser.cc \
           src/graphics/tool/TracingManager.cc \
           src/graphics/util/MPushButton.cc \
           src/model/operation/AffineTransformationOperation.cc \
           src/model/operation/ColorConvertOperation.cc \
           src/model/operation/ConvolveOperation.cc \
           src/model/operation/MergeOperation.cc \
           src/model/operation/Operation.cc \
           src/model/operation/RescaleOperation.cc
