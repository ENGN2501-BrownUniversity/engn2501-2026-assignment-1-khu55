//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2026-01-26 17:46:03 taubin>
//------------------------------------------------------------------------
//
// Node.hpp
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

#ifndef _Node_h_
#define _Node_h_

#include <string>

using namespace std;

class Color {
public:
  float r,g,b;
public:
  Color(float R=0.0f, float G=0.0f, float B=0.0f);
  // Color& operator=(Color& src);
};

class Vec2f {
public:
  float x,y;
public:
  Vec2f(const float X=0.0f, const float Y=0.0f);
  float& operator[] (const int i);
  // Vec2f& operator=  (const Vec2f& src);
  Vec2f& operator+= (const Vec2f& rhs);
  Vec2f& operator-= (const Vec2f& rhs);
  float  norm() const;
  void   normalize();
};

class Vec3f {
public:
  float x,y,z;
public:
  Vec3f(float X=0.0f, float Y=0.0f, float Z=0.0f);
  float& operator[] (const int i);
  // Vec3f& operator=  (const Vec3f& rhs);
  Vec3f& operator+= (const Vec3f& rhs);
  Vec3f& operator-= (const Vec3f& rhs);
  float  norm() const;
  void   normalize();
};

class Vec4f {
public:
  float x,y,z,w;
public:
  Vec4f(float X=0.0f, float Y=0.0f, float Z=0.0f, float W=0.0f);
  float& operator[] (const int i);
  // Vec4f& operator=  (const Vec4f& rhs);
  Vec4f& operator+= (const Vec4f& rhs);
  Vec4f& operator-= (const Vec4f& rhs);
  float  norm() const;
  void   normalize();
};

class Node {

protected:

  string      _name;
  const Node* _parent;
  bool        _show;

public:
  
  Node();
  virtual ~Node();

  const string&   getName() const;
  void            setName(const string& name);
  bool            nameEquals(const string& name);
  const Node*     getParent() const;
  void            setParent(const Node* node);
  bool            getShow() const;
  void            setShow(const bool value);
  int             getDepth() const; 

  virtual bool    isAppearance() const;
  virtual bool    isGroup() const;
  virtual bool    isImageTexture() const;
  virtual bool    isIndexedFaceSet() const;
  virtual bool    isIndexedLineSet() const;
  virtual bool    isMaterial() const;
  virtual bool    isPixelTexture() const;
  virtual bool    isSceneGraph() const;
  virtual bool    isShape() const;
  virtual bool    isTransform() const;
  virtual string  getType() const;

  typedef bool    (*Property)(Node& node);
  typedef void    (*Operator)(Node& node);

  virtual void    printInfo(string indent);
};

typedef Node *pNode;

#endif /* _Node_h_ */
