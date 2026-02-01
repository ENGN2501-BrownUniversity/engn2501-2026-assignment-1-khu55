//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:42:17 taubin>
//------------------------------------------------------------------------
//
// GuiMainWindow.cpp
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

#include <iostream>

#include "GuiStrings.hpp"
#include "GuiMainWindow.hpp"
#include "GuiGLWidget.hpp"
#include "GuiAboutDialog.hpp"

#include <QApplication>
#include <QMenuBar>
#include <QGroupBox>
#include <QStatusBar>
#include <QFileDialog>
#include <QRect>
#include <QMargins>

#include "io/LoaderWrl.hpp"
#include "io/SaverWrl.hpp"

#include "io/LoaderStl.hpp"
#include "io/SaverStl.hpp"

int     GuiMainWindow::_timerInterval = 20;
int     GuiMainWindow::_lDPI          = 96;
QString GuiMainWindow::_platformName  = "unknown";

//////////////////////////////////////////////////////////////////////
GuiMainWindow::GuiMainWindow(QWidget* parent):
  QMainWindow(parent) {
  setupUi(this);
  setWindowIcon(QIcon("qt.icns"));
  setWindowTitle(QString("DGP2026-A1 | Student : %1").arg(STUDENT_NAME));

  LoaderWrl* wrlLoader = new LoaderWrl();
  _loader.registerLoader(wrlLoader);
  SaverWrl* wrlSaver = new SaverWrl();
  _saver.registerSaver(wrlSaver);

  LoaderStl* stlLoader = new LoaderStl();
  _loader.registerLoader(stlLoader);
  SaverStl* stlSaver = new SaverStl();
  _saver.registerSaver(stlSaver);

  // for animation
  _timer = new QTimer(this);
  _timer->setInterval(_timerInterval);
  connect(_timer, SIGNAL(timeout()), glWidget, SLOT(update()));

  int tHeight = (_lDPI<=96)?600:(_lDPI<=144)?900:1200;
  int tWidth = (_lDPI<=96)?400:(_lDPI<=144)?600:800;
  int gHeight = tHeight;
  int gWidth = tHeight; // 3*tHeight/2;

  // glWidget->setBackgroundColor(qRgb(75, 100, 150));
  glWidget->setBackgroundColor(qRgb(200,200,200));
  glWidget->setMaterialColor(qRgb(225, 150, 75));
  glWidget->setMainWindow(this);
  glWidget->resizeGL(gWidth,gHeight);
  glWidget->show();

  toolsWidget->setMainWindow(this);
  toolsWidget->setMinimumWidth(tWidth);
  toolsWidget->setMaximumWidth(tWidth);
  toolsWidget->setMinimumHeight(tHeight);
  // toolsWidget->hide();
  toolsWidget->show();

  showStatusBarMessage("");
  // glWidget->setFocus();
}

//////////////////////////////////////////////////////////////////////
GuiMainWindow::~GuiMainWindow() {
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::showStatusBarMessage(const QString & message) {
  statusBar()->showMessage(message);
}

//////////////////////////////////////////////////////////////////////
SceneGraph* GuiMainWindow::loadSceneGraph(const char* fname) {
  static char str[1024];
  snprintf(str,1024,"Trying to load \"%s\" ...",fname);
  showStatusBarMessage(QString(str));
  SceneGraph* pWrl = new SceneGraph();
  if(_loader.load(fname,*pWrl)) { // if success
    snprintf(str,1024,"Loaded \"%s\"",fname);
    pWrl->updateBBox();
    glWidget->setSceneGraph(pWrl,true);
    toolsWidget->updateState();
  } else {
    snprintf(str,1024,"Unable to load \"%s\"",fname);
    delete pWrl;
    pWrl = (SceneGraph*)0;
  }
  showStatusBarMessage(QString(str));
  return pWrl;
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::on_fileLoadAction_triggered() {

  std::string filename;

  // stop animation
  _timer->stop();

  QFileDialog fileDialog(this);
  fileDialog.setFileMode(QFileDialog::ExistingFile); // allowed to select only one 
  fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog.setNameFilter(tr("3D Files (*.wrl *.stl)"));
  QStringList fileNames;
  if(fileDialog.exec()) {
    fileNames = fileDialog.selectedFiles();
    if(fileNames.size()>0)
      filename = fileNames.at(0).toStdString();
  }

  if (filename.empty()) {
    showStatusBarMessage("load filename is empty");
  } else {
    loadSceneGraph(filename.c_str());
  } 

  // restart animation
  _timer->start(_timerInterval);
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::on_fileSaveAction_triggered() {

  std::string filename;

  // stop animation
  _timer->stop();

  QFileDialog fileDialog(this);
  fileDialog.setFileMode(QFileDialog::AnyFile); // allowed to select only one 
  fileDialog.setAcceptMode(QFileDialog::AcceptSave);

  // TODO Sat Sep 10 22:18:57 2016
  // get list of file extensions from registered Savers

  fileDialog.setNameFilter(tr("3D Files (*.wrl *.stl)"));
  QStringList fileNames;
  if(fileDialog.exec()) {
    fileNames = fileDialog.selectedFiles();
    if(fileNames.size()>0)
      filename = fileNames.at(0).toStdString();
  }

  // restart animation
  _timer->start(_timerInterval);

  if (filename.empty()) {
    showStatusBarMessage("save filename is empty");
  } else {

    static char str[1024];

    snprintf(str,1024,"Saving \"%s\" ...",filename.c_str());
    showStatusBarMessage(QString(str));

    SceneGraph* pWrl = glWidget->getSceneGraph();

    if(_saver.save(filename.c_str(),*pWrl)) {
      snprintf(str,1024,"Saved \"%s\"", filename.c_str());
    } else {
      snprintf(str,1024,"Unable to save \"%s\"",filename.c_str());
    }

    showStatusBarMessage(QString(str));
  }
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::on_fileExitAction_triggered() {
  close();
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::on_toolsShowAction_triggered() {
  toolsWidget->show();
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::on_toolsHideAction_triggered() {
    toolsWidget->hide();
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::on_helpAboutAction_triggered() {
    GuiAboutDialog dialog;
  dialog.exec();
}

//////////////////////////////////////////////////////////////////////
void GuiMainWindow::resizeEvent(QResizeEvent* event) {
  (void) event;
  toolsWidget->updateState();
}

//////////////////////////////////////////////////////////////////////
int GuiMainWindow::getGLWidgetWidth() {
  return glWidget->size().width();
}

//////////////////////////////////////////////////////////////////////
int GuiMainWindow::getGLWidgetHeight() {
  return glWidget->size().height();
}

GuiViewerData& GuiMainWindow::getData() const {
  return glWidget->getData();
}

SceneGraph* GuiMainWindow::getSceneGraph() {
  return glWidget->getSceneGraph();
}

void GuiMainWindow::setSceneGraph(SceneGraph* pWrl, bool resetHomeView) {
  glWidget->setSceneGraph(pWrl,resetHomeView);
}

void GuiMainWindow::updateState() {
  toolsWidget->updateState();
}

void GuiMainWindow::refresh() {
  glWidget->update();
}
