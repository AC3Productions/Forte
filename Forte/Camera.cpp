// file:   Camera.cpp
// author: Alfaroh Corney III
// date:   7/2/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <Camera.h>

FCamera* FCamera::s_instance = nullptr;

FCamera* FCamera::Instance()
{
  if (!s_instance)
  {
    s_instance = new FCamera;
  }
  return s_instance;
}

// Set camera position with vector
void FCamera::SetPosition(const RVec2& pos)
{
  m_pos = pos;
}

// Set camera position with floats
void FCamera::SetPosition(float x, float y)
{
  m_pos.x = x;
  m_pos.y = y;
}

// Set camera zoom
void FCamera::SetZoom(float zoom)
{
  if (zoom >= 0.0f)
  {
    m_zoom = 1.0f;
  }
  else
  {
    m_zoom = zoom;
  }
}
