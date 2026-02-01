//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:42:17 taubin>
//------------------------------------------------------------------------
//
// GuiMainWindow.hpp
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

#ifndef _GUI_MAIN_WINDOW_HPP_
#define _GUI_MAIN_WINDOW_HPP_

#include <string>

#include <QMainWindow>
#include "ui_GuiMainWindow.h"
#include <QTimer>
// #include <QGridLayout>
#include <io/AppLoader.hpp>
#include <io/AppSaver.hpp>
// #include "GuiGLWidget.hpp"
// #include "GuiToolsWidget.hpp"
#include <string>

QT_FORWARD_DECLARE_CLASS(QOpenGLWidget)

class GuiMainWindow : public QMainWindow, public Ui::GuiMainWindow {

  Q_OBJECT

public:

  GuiMainWindow(QWidget* parent = 0);
  ~GuiMainWindow();

  void timerStop()  { _timer->stop(); }
  void timerStart() { _timer->start(_timerInterval); }
  void showStatusBarMessage(const QString & message);

  int  getGLWidgetWidth();
  int  getGLWidgetHeight();

  GuiViewerData& getData() const;
  SceneGraph*    getSceneGraph();
  void           setSceneGraph(SceneGraph* pWrl, bool resetHomeView);
  SceneGraph*    loadSceneGraph(const char* fname);

  void updateState();
  void refresh();

  static void setLogicalDotsPerInch(int lDPI) {         _lDPI = lDPI; }
  static void setPlatformName(QString& name)  { _platformName = name; }

private slots:

  void on_fileExitAction_triggered();
  void on_fileLoadAction_triggered();
  void on_fileSaveAction_triggered();
  void on_toolsShowAction_triggered();
  void on_toolsHideAction_triggered();
  void on_helpAboutAction_triggered();

protected:

  virtual void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;

private:

  AppLoader       _loader;
  AppSaver        _saver;
  QTimer         *_timer;

  static int      _timerInterval;
  static int      _lDPI;
  static QString  _platformName;
};

#endif // _GUI_MAIN_WINDOW_HPP_
