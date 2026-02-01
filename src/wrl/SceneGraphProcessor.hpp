//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:46:08 taubin>
//------------------------------------------------------------------------
//
// SceneGraphProcessor.hpp
//
// Software developed for the University course
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

#ifndef _SceneGraphProcessor_hpp_
#define _SceneGraphProcessor_hpp_

#include <iostream>
#include "SceneGraph.hpp"
#include "Shape.hpp"
#include "IndexedFaceSet.hpp"
#include "IndexedLineSet.hpp"

class SceneGraphProcessor {

public:

  SceneGraphProcessor(SceneGraph& wrl);
  ~SceneGraphProcessor();

  void normalClear();
  void normalInvert();
  void computeNormalPerFace();
  void computeNormalPerVertex();
  void computeNormalPerCorner();

  void bboxAdd(int depth=0, float scale=1.0f, bool isCube=true);
  void bboxRemove();
  bool hasBBox();

  void edgesAdd();
  void edgesRemove();
  bool hasEdges();

  bool hasIndexedFaceSetFaces();
  bool hasIndexedFaceSetNormalNone();
  bool hasIndexedFaceSetNormalPerFace();
  bool hasIndexedFaceSetNormalPerVertex();
  bool hasIndexedFaceSetNormalPerCorner();

  bool hasIndexedLineSetColorNone();
  bool hasIndexedLineSetColorPerVertex();
  bool hasIndexedLineSetColorPerPolyline();

  bool hasIndexedFaceSetShown();
  bool hasIndexedFaceSetHidden();
  bool hasIndexedLineSetShown();
  bool hasIndexedLineSetHidden();

  void shapeIndexedFaceSetShow();
  void shapeIndexedFaceSetHide();
  void shapeIndexedLineSetShow();
  void shapeIndexedLineSetHide();

  void removeSceneGraphChild(const string& name);
  void pointsRemove();
  void surfaceRemove();


private:

  SceneGraph&    _wrl;

  void        _applyToIndexedFaceSet(IndexedFaceSet::Operator p);

  // IndexedFaceSet::Operator
  static void _normalClear(IndexedFaceSet& ifs);
  static void _normalInvert(IndexedFaceSet& ifs);
  static void _computeNormalPerFace(IndexedFaceSet& ifs);
  static void _computeNormalPerVertex(IndexedFaceSet& ifs);
  static void _computeNormalPerCorner(IndexedFaceSet& ifs);

  static void _computeFaceNormal
              (vector<float>& coord, vector<int>&   coordIndex,
               int i0, int i1, Vec3f& n, bool normalize);

  bool        _hasShapeProperty(Shape::Property p);
  bool        _hasIndexedFaceSetProperty(IndexedFaceSet::Property p);
  bool        _hasIndexedLineSetProperty(IndexedLineSet::Property p);

  // Shape::Property
  static bool _hasEdges(Shape& shape);
  static bool _hasIndexedFaceSetShown(Shape& shape);
  static bool _hasIndexedFaceSetHidden(Shape& shape);
  static bool _hasIndexedLineSetShown(Shape& shape);
  static bool _hasIndexedLineSetHidden(Shape& shape);

  // IndexedFaceSet::Property
  static bool _hasFaces(IndexedFaceSet& ifs);
  static bool _hasNormalNone(IndexedFaceSet& ifs);
  static bool _hasNormalPerFace(IndexedFaceSet& ifs);
  static bool _hasNormalPerVertex(IndexedFaceSet& ifs);
  static bool _hasNormalPerCorner(IndexedFaceSet& ifs);
    
  // IndexedLineSet::Property
  static bool _hasColorNone(IndexedLineSet& ils);
  static bool _hasColorPerVertex(IndexedLineSet& ils);
  static bool _hasColorPerPolyline(IndexedLineSet& ils);

  IndexedFaceSet* _getNamedShapeIFS(const string& name, bool create);
};

#endif /* _SceneGraphProcessor_hpp_ */
