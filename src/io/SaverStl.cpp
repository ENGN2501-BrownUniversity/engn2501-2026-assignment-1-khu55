//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:42:17 taubin>
//------------------------------------------------------------------------
//
// SaverStl.cpp
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

#include "SaverStl.hpp"

#include "wrl/Shape.hpp"
#include "wrl/Appearance.hpp"
#include "wrl/Material.hpp"
#include "wrl/IndexedFaceSet.hpp"

#include "core/Faces.hpp"

const char* SaverStl::_ext = "stl";
// helper: remove directory + extension
static std::string baseNoExt(const char* filename) {
  std::string s = (filename ? filename : "mesh");
  size_t p = s.find_last_of("/\\");
  if(p != std::string::npos) s = s.substr(p + 1);
  size_t d = s.find_last_of('.');
  if(d != std::string::npos) s = s.substr(0, d);
  if(s.empty()) s = "mesh";
  return s;
}

//////////////////////////////////////////////////////////////////////
bool SaverStl::save(const char* filename, SceneGraph& wrl) const {
    fprintf(stderr, ">>> SaverStl from: %s\n", __FILE__);

  if(filename == nullptr) return false;

  // 1) the SceneGraph should have a single child
  if(wrl.getNumberOfChildren() != 1) return false;

  // 2) the child should be a Shape node
  if (wrl.getNumberOfChildren() < 1) {
      fprintf(stderr, "Error: SceneGraph is empty!\n");
      return false;
  }

  fprintf(stderr, ">>> Attempting to count children...\n");
  int count = wrl.getNumberOfChildren();
  fprintf(stderr, ">>> Count success: %d\n", count); // 看看这里能不能印出来

  Node* child = wrl.getChild(0);
  Shape* shape = dynamic_cast<Shape*>(child);
  if(shape == nullptr) return false;

  // 3) the geometry of the Shape node should be an IndexedFaceSet node
  Node* geom = shape->getGeometry();
  IndexedFaceSet* ifs = dynamic_cast<IndexedFaceSet*>(geom);
  if(ifs == nullptr) return false;

  // construct Faces from IndexedFaceSet
  std::vector<float>& coord = ifs->getCoord();        // flat xyzxyz...
  std::vector<int>&   coordIndex = ifs->getCoordIndex();

  if(coord.size() % 3 != 0) return false;
  const int nV = (int)(coord.size() / 3);

  Faces faces(nV, coordIndex);

  // 4) triangle mesh
  for(int iF = 0; iF < faces.getNumberOfFaces(); iF++) {
    if(faces.getFaceSize(iF) != 3) return false;
  }

  // 5) normals per face
  bool& normalPerVertex = ifs->getNormalPerVertex();
  if(normalPerVertex) return false;

  std::vector<float>& normal = ifs->getNormal();      // flat nxnynz...
  if(normal.size() % 3 != 0) return false;
  if((int)(normal.size() / 3) != faces.getNumberOfFaces()) return false;

  // all conditions satisfied -> write file
  FILE* fp = fopen(filename, "w");
  if(fp == nullptr) return false;

  // name: (ifs->getName() not shown in header) => use filename w/o path/ext
  std::string solidName = baseNoExt(filename);
  fprintf(fp, "solid %s\n", solidName.c_str());

  for(int iF = 0; iF < faces.getNumberOfFaces(); iF++) {

    float nx = normal[3*iF + 0];
    float ny = normal[3*iF + 1];
    float nz = normal[3*iF + 2];

    fprintf(fp, "  facet normal %g %g %g\n", nx, ny, nz);
    fprintf(fp, "    outer loop\n");

    for(int j = 0; j < 3; j++) {
      int iV = faces.getFaceVertex(iF, j);
      if(iV < 0 || iV >= nV) { fclose(fp); return false; }

      float x = coord[3*iV + 0];
      float y = coord[3*iV + 1];
      float z = coord[3*iV + 2];

      fprintf(fp, "      vertex %g %g %g\n", x, y, z);
    }

    fprintf(fp, "    endloop\n");
    fprintf(fp, "  endfacet\n");
  }

  fprintf(fp, "endsolid %s\n", solidName.c_str());
  fclose(fp);
  return true;
}

