// file:   TextureSource.cpp
// author: Alfaroh Corney III
// date:   2/25/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <TextureSource.h>

TextureSource::TextureSource(const char* image, unsigned rows, unsigned cols) : texture(image), num_rows(rows), num_cols(cols)
{
  float x = (float)texture.GetWidth() / num_cols;
  float y = (float)texture.GetHeight() / num_rows;
  m_window.SetSize(x, y);
  m_window.SetPosition(0, 0);
}

void TextureSource::UpdateWindow(int index)
{

  int x = index % num_cols;
  int y = index / num_cols;

  m_window.SetPosition(x * m_window.GetWidth(), y * m_window.GetHeight());

}
