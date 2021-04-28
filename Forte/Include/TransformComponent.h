// file:   TransformComponent.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <forte.h>
#include <component.h>
#include <GameObject.h>


/*********************************************************/
// Transform Class
// 
// The transform contains all data related to location in
// world-space.
// This includes:
//  -Position in World-Space
//  -Rotation
//  -Scale
// 
/*********************************************************/
class FTransform : public FComponent
{
  public:
  // Details:
  //  Important info that is not made immediately clear from the function name and parameters.
  //
  // Inputs:
  // -pos 
  //   Starting position in world-space.
  // -rot
  //   Starting orientation in world-space.
  // -scale
  //   Starting scale in world-space.
  //         
  // Output:
  //   Useful information about the return value, and/or whatever else the function did.
  FTransform(RVec2 pos = RVec2(), float rot = 0, 
             RVec2 scale = RVec2()) : FComponent(FComponent::Type::CT_FTransform),
                                      m_pos(pos), m_rot(rot), m_scale(scale)
  {
  }

  // Details:
  //  Sets the World-space coordinates of the transform.
  void SetPosition(const RVec2& pos);
  void SetPosition(float x, float y);

  // Details:
  //  Returns location of the transform in world space.
  const RVec2& GetPosition() const { return m_pos; }

  // Details:
  //  Sets the rotation value of the transform, in radians.
  void SetRotation(float rad);

  // Details:
  //  Returns the transform's rotation value, in radians.
  float GetRotation() const { return m_rot; }

  // Details:
  //  Sets the scale value of the transform X and Y can be scaled independently.
  void SetScale(const RVec2& scale);
  void SetScale(float x, float y);

  // Details:
  //  Returns the transform's scale.
  const RVec2& GetScale() const { return m_scale; }

  private:
    RVec2 m_pos;
    float m_rot; // Stored in radians
    RVec2 m_scale;
};






#endif
