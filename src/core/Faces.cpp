//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:42:17 taubin>
//------------------------------------------------------------------------
//
// Faces.cpp
//
// Written by: <Your Name>
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

#include <math.h>
#include "Faces.hpp"
  
Faces::Faces(const int nV, const vector<int>& coordIndex) {
  // 1) copy coordIndex locally (we may append -1)
  _coordIndex = coordIndex;

  // ensure last value is -1 if not empty
  if(!_coordIndex.empty() && _coordIndex.back()!=-1) {
    _coordIndex.push_back(-1);
  }

  const int nC = (int)_coordIndex.size();

  // 2) compute updated number of vertices
  int maxIdx = -1;
  for(int v : _coordIndex) {
    if(v >= 0) maxIdx = std::max(maxIdx, v);
  }
  _nV = std::max(nV, maxIdx + 1);

  // 3) count faces = number of -1s
  _nF = 0;
  for(int v : _coordIndex) {
    if(v == -1) _nF++;
  }

  // allocate tables
  _faceFirstCorner.assign(_nF, -1);
  _faceSize.assign(_nF, 0);
  _cornerFace.assign(nC, -1);
  _nextCorner.assign(nC, -1);

  // 4) build face tables and corner tables
  int iF = 0;
  int start = 0; // first corner index of current face in coordIndex

  for(int iC = 0; iC < nC; iC++) {
    if(_coordIndex[iC] == -1) {
      // finish a face at separator iC
      if(iF < _nF) {
        _faceFirstCorner[iF] = start;
        _faceSize[iF] = iC - start; // number of non-separator corners
      }

      // set cornerFace for corners of this face (excluding separator)
      for(int k = start; k < iC; k++) {
        _cornerFace[k] = iF;
      }

      // set nextCorner cyclically within this face
      if(iC - start >= 1) {
        for(int k = start; k < iC - 1; k++) {
          _nextCorner[k] = k + 1;
        }
        _nextCorner[iC - 1] = start; // last -> first
      }

      // separator corner remains -1 in cornerFace/nextCorner
      // advance to next face
      iF++;
      start = iC + 1;
    }
  }
}
  // TODO

int Faces::getNumberOfVertices() const {
  // TODO
  return _nV;
}

int Faces::getNumberOfFaces() const {
  // TODO
  return _nF;
}

int Faces::getNumberOfCorners() const {
  // TODO
  return (int)_coordIndex.size();
}

int Faces::getFaceSize(const int iF) const {
  if(iF < 0 || iF >= _nF) return 0;
  return _faceSize[iF];
  // TODO
}

int Faces::getFaceFirstCorner(const int iF) const {
  if(iF < 0 || iF >= _nF) return -1;
  return _faceFirstCorner[iF];
  // TODO
}

int Faces::getFaceVertex(const int iF, const int j) const {
  if(iF < 0 || iF >= _nF) return -1;
  const int sz = _faceSize[iF];
  if(j < 0 || j >= sz) return -1;
  const int fc = _faceFirstCorner[iF];
  const int iC = fc + j;
  if(iC < 0 || iC >= (int)_coordIndex.size()) return -1;
  return _coordIndex[iC];
  // TODO
}

int Faces::getCornerFace(const int iC) const {
  if(iC < 0 || iC >= (int)_coordIndex.size()) return -1;
  if(_coordIndex[iC] == -1) return -1; // separator
  return _cornerFace[iC];
  // TODO
}

int Faces::getNextCorner(const int iC) const {
  if(iC < 0 || iC >= (int)_coordIndex.size()) return -1;
  if(_coordIndex[iC] == -1) return -1; // separator
  return _nextCorner[iC];
  // TODO
}

