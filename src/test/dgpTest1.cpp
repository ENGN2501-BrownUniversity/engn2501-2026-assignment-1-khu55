//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:42:17 taubin>
//------------------------------------------------------------------------
//
// dgpTest.cpp
//
// Software developed for the course
// Digital Geometry Processing
// Copyright (c) 2025, Gabriel Taubin
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

#include <string>
#include <iostream>

using namespace std;

#include <wrl/SceneGraph.hpp>
#include <io/AppLoader.hpp>
#include <io/AppSaver.hpp>
#include <io/LoaderStl.hpp>
#include <io/LoaderWrl.hpp>
#include <io/SaverWrl.hpp>
#include <io/SaverStl.hpp>

class Data {
public:
  bool   _debug;
  string _inFile;
  string _outFile;
public:
  Data():
    _debug(false),
    _inFile(""),
    _outFile("")
  { }
};

const char* tv(bool value)        { return (value)?"true":"false";                 }

void options(Data& D) {
  cerr << "   -d|-debug               [" << tv(D._debug)          << "]" << endl;
}

void usage(Data& D) {
  cerr << "USAGE: dgpTest1 [options] inFile outFile" << endl;
  cerr << "   -h|-help" << endl;
  options(D);
  cerr << endl;
  exit(0);
}

void error(const char *msg) {
  cerr << "ERROR: dgpTest1 | " << ((msg)?msg:"") << endl;
  exit(0);
}

//////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {

  Data D;

  // process command line arguments ////////////////////////////////////
  if(argc==1) usage(D);
  for(int i=1;i<argc;i++) {
    if(string(argv[i])=="-h" || string(argv[i])=="-help") {
      usage(D);
    } else if(string(argv[i])=="-d" || string(argv[i])=="-debug") {
      D._debug = !D._debug;
    } else if(string(argv[i])[0]=='-') {
      error("unknown option");
    } else if(D._inFile=="") {
      D._inFile = string(argv[i]);
    } else if(D._outFile=="") {
      D._outFile = string(argv[i]);
    }
  }

  // basic error handling //////////////////////////////////////////////
  if(D._inFile =="") error("no inFile");
  if(D._outFile=="") error("no outFile");

  if(D._debug) {
    cerr << "dgpTest {" << endl;
    cerr << endl;
    options(D);
    cerr << endl;
    cerr << "  inFile  = " << D._inFile << endl;
    cerr << "  outFile = " << D._outFile << endl;
    cerr << endl;
    cerr << "}" << endl;
    cerr << endl;
    fflush(stderr);
  }

  // start /////////////////////////////////////////////////////////////
  bool success = false;

  // create loader and saver factories /////////////////////////////////
  AppLoader loaderFactory;
  AppSaver  saverFactory;

  // register input file loaders
  LoaderWrl* wrlLoader = new LoaderWrl();
  loaderFactory.registerLoader(wrlLoader);
  LoaderStl* stlLoader = new LoaderStl();
  loaderFactory.registerLoader(stlLoader);

  // register output file savers  
  SaverWrl* wrlSaver = new SaverWrl();
  saverFactory.registerSaver(wrlSaver);
  SaverStl* stlSaver = new SaverStl();
  saverFactory.registerSaver(stlSaver);

  // read input file and create SceneGraph /////////////////////////////

  if(D._debug) {
    cerr << "  loading input file {" << endl;
    cerr << "    fileName       = \"" << D._inFile << "\"" << endl;
  }

  SceneGraph wrl; // create empty scene graph
  success = loaderFactory.load(D._inFile.c_str(),wrl);

  if(D._debug) {
    cerr << "    success        = " << tv(success)          << endl;
    cerr << "  }" << endl;
    cerr << endl;
  }

  if(success==false) return -1;

  // process ///////////////////////////////////////////////////////////
  
  // if(D._debug) cerr << "  processing {" << endl;
  // if(D._debug) cerr << "    nothing to do in this assignment" << endl;
  // if(D._debug) cerr << "  }" << endl;  

  // write output file /////////////////////////////////////////////////
  
  if(D._debug) {
    cerr << "  saving output file {" << endl;
    cerr << "    fileName       = \"" << D._outFile << "\"" << endl;
  }

  success = saverFactory.save(D._outFile.c_str(),wrl);

  if(D._debug) {
    cerr << "    success        = " << tv(success)          << endl;
    cerr << "  }" << endl;
    cerr << endl;
  }

  // done //////////////////////////////////////////////////////////////

  if(D._debug) {
    cerr << "}" << endl;
    fflush(stderr);
  }

  return 0;
}
