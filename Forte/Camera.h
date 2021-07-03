// file:   Camera.h
// author: Alfaroh Corney III
// date:   7/2/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef CAMERA_H
#define CAMERA_H

#include <forte.h>

class FCamera
{
public:
  static FCamera* Instance();

  // Details:
  //  Set the position of the camera.
  //
  // Inputs:
  // -pos / x, y
  //  The position of the camera in world space.
  // 
  // Output:
  //  Sets the zoom. If an invalid zoom is given (less than or equal to 0), the zoom will be set to 1.0.
  void SetPosition(const RVec2& pos);
  void SetPosition(float x, float y);

  // Details:
  //  Get the current position of the camera.
  // 
  // Output:
  //  The camera's position in world space.
  const RVec2& GetPosition() const { return m_pos; }

  // Details:
  //  Set a multiplier on the camera's zoom. 1.0 is default zoom (320x180 pixels). 
  //  Numbers greater than 1 zoom in, numbers less than 1 zoom out.
  //
  // Inputs:
  // -zoom 
  //   The multiplier on the zoom camera. 1.0 = 320x180, 0.5 = 160x90, 2.0 = 640x360, etc.
  //         
  // Output:
  //  Sets the zoom. If an invalid zoom is given (less than or equal to 0), the zoom will be set to 1.0.
  void SetZoom(float zoom);

  // Details:
  //  Get the current zoom of the camera.
  // 
  // Output:
  //  The camera's zoom value.
  float GetZoom() const { return m_zoom; }

private:
  // Singleton pattern constructor.
  FCamera() : m_pos(0, 0), m_zoom(1.0f) {}
  static FCamera* s_instance;

  // Position in world space.
  RVec2 m_pos;
  // Zoom value.
  float m_zoom;

};


#endif
