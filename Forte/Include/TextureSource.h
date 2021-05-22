// file:   TextureSource.h
// author: Alfaroh Corney III
// date:   2/25/2021
// 
// info:
//  Any file where a texture needs to get loaded/set up.
//  Should be mostly Sprite-related files.
#ifndef TEXTURESOURCE_H
#define TEXTURESOURCE_H

#include <forte.h>


// Plain-old-data struct about Texture data.
struct TextureSource
{

  raylib::Texture texture;
  unsigned num_rows;
  unsigned num_cols;

  raylib::Rectangle m_window; // Rectangle info for displaying part of the texture

  TextureSource(const char* image, unsigned rows = 1, unsigned cols = 1);

  void UpdateWindow(int index);

  ~TextureSource() {}
};



#endif
