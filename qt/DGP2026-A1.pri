#
# vim:filetype=qmake sw=4 ts=4 expandtab nospell
#

FORMS = \
        $$FORMSDIR/GuiMainWindow.ui \
        $$FORMSDIR/GuiToolsWidget.ui \
        $$(NULL)

RESOURCES = \
	$$ASSETSDIR/assets.qrc

CORE_DIR = $$SOURCEDIR/core
GUI_DIR  = $$SOURCEDIR/gui
IO_DIR   = $$SOURCEDIR/io
UTIL_DIR = $$SOURCEDIR/util
WRL_DIR  = $$SOURCEDIR/wrl

SOURCES += \
	$$SOURCEDIR/core/Faces.cpp \
	$$SOURCEDIR/gui/GuiAboutDialog.cpp \
	$$SOURCEDIR/gui/GuiGLBuffer.cpp \
	$$SOURCEDIR/gui/GuiGLHandles.cpp \
	$$SOURCEDIR/gui/GuiGLShader.cpp \
	$$SOURCEDIR/gui/GuiGLWidget.cpp \
	$$SOURCEDIR/gui/GuiMainWindow.cpp \
	$$SOURCEDIR/gui/GuiQtLogo.cpp \
	$$SOURCEDIR/gui/GuiToolsWidget.cpp \
	$$SOURCEDIR/gui/GuiViewerApp.cpp \
	$$SOURCEDIR/gui/GuiViewerData.cpp \
	$$SOURCEDIR/io/AppLoader.cpp \
	$$SOURCEDIR/io/AppSaver.cpp \
	$$SOURCEDIR/io/LoaderStl.cpp \
	$$SOURCEDIR/io/LoaderWrl.cpp \
	$$SOURCEDIR/io/SaverStl.cpp \
	$$SOURCEDIR/io/SaverWrl.cpp \
	$$SOURCEDIR/io/Tokenizer.cpp \
	$$SOURCEDIR/io/TokenizerFile.cpp \
	$$SOURCEDIR/io/TokenizerString.cpp \
	$$SOURCEDIR/util/BBox.cpp \
	$$SOURCEDIR/util/StaticRotation.cpp \
	$$SOURCEDIR/wrl/Appearance.cpp \
	$$SOURCEDIR/wrl/Group.cpp \
	$$SOURCEDIR/wrl/ImageTexture.cpp \
	$$SOURCEDIR/wrl/IndexedFaceSet.cpp \
	$$SOURCEDIR/wrl/IndexedLineSet.cpp \
	$$SOURCEDIR/wrl/Material.cpp \
	$$SOURCEDIR/wrl/Node.cpp \
	$$SOURCEDIR/wrl/PixelTexture.cpp \
	$$SOURCEDIR/wrl/Rotation.cpp \
	$$SOURCEDIR/wrl/SceneGraph.cpp \
	$$SOURCEDIR/wrl/SceneGraphProcessor.cpp \
	$$SOURCEDIR/wrl/SceneGraphTraversal.cpp \
	$$SOURCEDIR/wrl/Shape.cpp \
	$$SOURCEDIR/wrl/Transform.cpp \
        $$(NULL)

HEADERS += \
	$$SOURCEDIR/core/Faces.hpp \
	$$SOURCEDIR/gui/GuiAboutDialog.hpp \
	$$SOURCEDIR/gui/GuiGLBuffer.hpp \
	$$SOURCEDIR/gui/GuiGLHandles.hpp \
	$$SOURCEDIR/gui/GuiGLShader.hpp \
	$$SOURCEDIR/gui/GuiGLWidget.hpp \
	$$SOURCEDIR/gui/GuiMainWindow.hpp \
	$$SOURCEDIR/gui/GuiQtLogo.hpp \
	$$SOURCEDIR/gui/GuiStrings.hpp \
	$$SOURCEDIR/gui/GuiToolsWidget.hpp \
	$$SOURCEDIR/gui/GuiViewerData.hpp \
	$$SOURCEDIR/io/AppLoader.hpp \
	$$SOURCEDIR/io/AppSaver.hpp \
	$$SOURCEDIR/io/Loader.hpp \
	$$SOURCEDIR/io/LoaderStl.hpp \
	$$SOURCEDIR/io/LoaderWrl.hpp \
	$$SOURCEDIR/io/Saver.hpp \
	$$SOURCEDIR/io/SaverStl.hpp \
	$$SOURCEDIR/io/SaverWrl.hpp \
	$$SOURCEDIR/io/StrException.hpp \
	$$SOURCEDIR/io/Tokenizer.hpp \
	$$SOURCEDIR/io/TokenizerFile.hpp \
	$$SOURCEDIR/io/TokenizerString.hpp \
	$$SOURCEDIR/util/BBox.hpp \
	$$SOURCEDIR/util/StaticRotation.hpp \
	$$SOURCEDIR/wrl/Appearance.hpp \
	$$SOURCEDIR/wrl/Group.hpp \
	$$SOURCEDIR/wrl/ImageTexture.hpp \
	$$SOURCEDIR/wrl/IndexedFaceSet.hpp \
	$$SOURCEDIR/wrl/IndexedLineSet.hpp \
	$$SOURCEDIR/wrl/Material.hpp \
	$$SOURCEDIR/wrl/Node.hpp \
	$$SOURCEDIR/wrl/PixelTexture.hpp \
	$$SOURCEDIR/wrl/Rotation.hpp \
	$$SOURCEDIR/wrl/SceneGraph.hpp \
	$$SOURCEDIR/wrl/SceneGraphProcessor.hpp \
	$$SOURCEDIR/wrl/SceneGraphTraversal.hpp \
	$$SOURCEDIR/wrl/Shape.hpp \
	$$SOURCEDIR/wrl/Transform.hpp \
	$$(NULL)

# $$EIGEN_DIR
INCLUDEPATH += $$SOURCEDIR $$CORE_DIR $$GUI_DIR $$IO_DIR $$UTIL_DIR $$WRL_DIR 

message(INCLUDEPATH = $$INCLUDEPATH)

