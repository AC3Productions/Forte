// file:   TransformComponent.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <TransformComponent.h>
#include <TransformSystem.h>

// Brief explanation of function. If this function is not explained in the header file,
// it should have a full description block.

FTransform* FTransform::Clone()
{

  FTransform* new_transform = TransformSystem::Instance()->CreateComponent();
  // no allocated data, so shallow copy works fine
  if (new_transform)
  {
    *new_transform = *this;
  }
  return new_transform;

}

void FTransform::SetPosition(const RVec2& pos)
{
  m_pos = pos;
}

void FTransform::SetPosition(float x, float y)
{
  m_pos.x = x;
  m_pos.y = y;
}

void FTransform::SetRotation(float rad)
{
  m_rot = rad;
}

void FTransform::SetScale(const RVec2& scale)
{
  m_scale = scale;
}

void FTransform::SetScale(float x, float y)
{
  m_scale.x = x;
  m_scale.y = y;
}
