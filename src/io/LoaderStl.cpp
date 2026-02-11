//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:42:17 taubin>
//------------------------------------------------------------------------
//
// LoaderStl.cpp
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

#include <stdio.h>
#include "TokenizerFile.hpp"
#include "LoaderStl.hpp"
#include "StrException.hpp"

#include "wrl/Shape.hpp"
#include "wrl/Appearance.hpp"
#include "wrl/Material.hpp"
#include "wrl/IndexedFaceSet.hpp"

// reference
// https://en.wikipedia.org/wiki/STL_(file_format)

const char* LoaderStl::_ext = "stl";

bool LoaderStl::parseFacet(TokenizerFile& tkn,
                           std::vector<float>& normal,
                           std::vector<float>& coord,
                           std::vector<int>& coordIndex) {

    // read next token (facet / endsolid / EOF)
    if(!tkn.get()) return false;  // EOF
    std::string tok = (std::string)tkn;

    // normal termination
    if(tok == "endsolid") {
        // optional name after endsolid: ignore
        return false;
    }

    if(tok != "facet") {
        throw new StrException(("expected 'facet' or 'endsolid', got '" + tok + "'").c_str());
    }

    // facet normal nx ny nz
    if(!(tkn.expecting("normal") && tkn.get()))
        throw new StrException("expected 'normal' after 'facet'");

    if(!tkn.get()) throw new StrException("expected nx");
    float nx = std::stof((std::string)tkn);
    if(!tkn.get()) throw new StrException("expected ny");
    float ny = std::stof((std::string)tkn);
    if(!tkn.get()) throw new StrException("expected nz");
    float nz = std::stof((std::string)tkn);

    // outer loop
    if(!(tkn.expecting("outer") && tkn.get()))
        throw new StrException("expected 'outer'");
    if(!(tkn.expecting("loop") && tkn.get()))
        throw new StrException("expected 'loop'");

    // 3 vertices
    int base = (int)(coord.size() / 3);
    for(int k=0; k<3; k++) {
        if(!(tkn.expecting("vertex") && tkn.get()))
            throw new StrException("expected 'vertex'");

        if(!tkn.get()) throw new StrException("expected vx");
        float x = std::stof((std::string)tkn);
        if(!tkn.get()) throw new StrException("expected vy");
        float y = std::stof((std::string)tkn);
        if(!tkn.get()) throw new StrException("expected vz");
        float z = std::stof((std::string)tkn);

        coord.push_back(x);
        coord.push_back(y);
        coord.push_back(z);

        coordIndex.push_back(base + k);
    }
    coordIndex.push_back(-1);

    // endloop endfacet
    if(!(tkn.expecting("endloop") && tkn.get()))
        throw new StrException("expected 'endloop'");
    if(!(tkn.expecting("endfacet") && tkn.get()))
        throw new StrException("expected 'endfacet'");

    // per-face normal
    normal.push_back(nx);
    normal.push_back(ny);
    normal.push_back(nz);

    return true;
}

bool LoaderStl::load(const char* filename, SceneGraph& wrl) {
  bool success = false;

  // clear the scene graph
  wrl.clear();
  wrl.setUrl("");

  FILE* fp = (FILE*)0;
  try {

    // open the file
    if(filename==(char*)0) throw new StrException("filename==null");
    fp = fopen(filename,"r");
    if(fp==(FILE*)0) throw new StrException("fp==(FILE*)0");

    // use the io/Tokenizer class to parse the input ascii file

    TokenizerFile tkn(fp);
    // first token should be "solid"
    if(tkn.expecting("solid") && tkn.get()) {

        if(!tkn.get()) throw new StrException("Unexpected EOF after solid");
        std::string nextTok = (std::string)tkn;

        bool firstFaceAlreadyRead = false;

        if(nextTok == "facet") {
            firstFaceAlreadyRead = true;
        } else if (nextTok == "endsolid") {
        } else {
        }

      // TODO ...

      // create the scene graph structure :
      // 1) the SceneGraph should have a single Shape node a child
      // 2) the Shape node should have an Appearance node in its appearance field
      // 3) the Appearance node should have a Material node in its material field
      // 4) the Shape node should have an IndexedFaceSet node in its geometry node
      Shape* shape = new Shape();
      Appearance* app = new Appearance();
      Material* mat = new Material();
      IndexedFaceSet* ifs = new IndexedFaceSet();

      // wire them
      app->setMaterial(mat);
      shape->setAppearance(app);
      shape->setGeometry(ifs);

      wrl.addChild(shape);
      wrl.setUrl(filename);

      // from the IndexedFaceSet
      // 5) get references to the coordIndex, coord, and normal arrays
      // 6) set the normalPerVertex variable to false (i.e., normals per face)
      std::vector<int>&   coordIndex = ifs->getCoordIndex();
      std::vector<float>& coord      = ifs->getCoord();
      std::vector<float>& normal     = ifs->getNormal();
      ifs->setNormalPerVertex(false);  

      // the file should contain a list of triangles in the following format
      while(true) {
        bool ok = parseFacet(tkn, normal, coord, coordIndex);
        if(!ok) break; // endsolid/EOF
      }


      // facet normal ni nj nk
      //   outer loop
      //     vertex v1x v1y v1z
      //     vertex v2x v2y v2z
      //     vertex v3x v3y v3z
      //   endloop
      // endfacet
      int nF = (int)normal.size() / 3;
      if(nF <= 0) throw new StrException("no faces loaded from stl");

      success = true;
    }

      // - run an infinite loop to parse all the faces
      // - write a private method to parse each face within the loop
      // - the method should return true if successful, and false if not
      // - if your method returns tru
      //     update the normal, coord, and coordIndex variables
      // - if your method returns false
      //     throw an StrException explaining why the method failed

    

    // close the file (this statement may not be reached)
    fclose(fp);
    
  } catch(StrException* e) { 
    
    if(fp!=(FILE*)0) fclose(fp);
    fprintf(stderr,"ERROR | %s\n",e->what());
    delete e;

  }

  return success;
}

