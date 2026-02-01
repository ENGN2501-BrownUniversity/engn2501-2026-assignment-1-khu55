//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:42:17 taubin>
//------------------------------------------------------------------------
//
// GuiToolsWidget.hpp
//
// Software developed for the course
// Digital Geometry Processing
// Copyright (c) 2026, Gabriel Taubin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Brown University nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL GABRIEL TAUBIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef _GUI_TOOLS_WIDGET_HPP_
#define _GUI_TOOLS_WIDGET_HPP_

#include "ui_GuiToolsWidget.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>

class GuiMainWindow;

class GuiToolsWidget : public QWidget, public Ui::GuiToolsWidget {

  Q_OBJECT

public:

  GuiToolsWidget(QWidget* parent = 0);
  ~GuiToolsWidget();

public slots:
                   
  void setMainWindow(GuiMainWindow *mw);
  void updateState();

#ifdef _WIN32
  static void setLocalDotsPerInch(const int lDPI) { _lDPI = lDPI; }
#endif

protected:

  virtual void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

private slots:

  // bounding box
  void bboxCube();
  void bboxDepthUp();
  void bboxDepthDown();
  void bboxSetDepth(int depth);
  void on_spinBoxBBoxDepth_valueChanged(int depth);
  void on_pushButtonBBoxAdd_clicked();
  void on_pushButtonBBoxRemove_clicked();
  void on_editBBoxScale_returnPressed();
  void on_checkBoxBBoxCube_stateChanged(int satate);

  // scene graph
  void on_pushButtonSceneGraphNormalNone_clicked();
  void on_pushButtonSceneGraphNormalPerVertex_clicked();
  void on_pushButtonSceneGraphNormalInvert_clicked();
  void on_pushButtonSceneGraphNormalPerFace_clicked();
  void on_pushButtonSceneGraphNormalPerCorner_clicked();
  void on_pushButtonSceneGraphIndexedFaceSetsShow_clicked();
  void on_pushButtonSceneGraphIndexedFaceSetsHide_clicked();
  void on_pushButtonSceneGraphIndexedLineSetsShow_clicked();
  void on_pushButtonSceneGraphIndexedLineSetsHide_clicked();


  // points
  void on_pushButtonPointsRemove_clicked();
  void on_pushButtonPointsShow_clicked();
  void on_pushButtonPointsHide_clicked();

  // edgse
  void on_pushButtonSceneGraphEdgesAdd_clicked();
  void on_pushButtonSceneGraphEdgesRemove_clicked();
  void on_pushButtonSceneGraphEdgesShow_clicked();
  void on_pushButtonSceneGraphEdgesHide_clicked();


  // surface
  void on_pushButtonSurfaceRemove_clicked();
  void on_pushButtonSurfaceShow_clicked();
  void on_pushButtonSurfaceHide_clicked();

private:

  GuiMainWindow*        _mainWindow;

#ifdef _WIN32
  static int _lDPI;
#endif

};

#endif // _GUI_TOOLS_WIDGET_HPP_
