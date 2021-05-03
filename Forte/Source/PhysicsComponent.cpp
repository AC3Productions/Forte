// file:   PhysicsComponent.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <PhysicsComponent.h>
#include <PhysicsSystem.h>
#include <GameObject.h>
#include <TransformComponent.h>

// Brief explanation of function. If this function is not explained in the header file,
// it should have a full description block.

void FPhysics::Update(float dt)
{
  // Use physics to update Transform
  FTransform* transform = m_parent->Get(FTransform);

  if (!transform)
  {
    throw std::exception("Trying to call physics Update on an object with no Transform.");
  }

  RVec2 pos = transform->GetPosition();

  m_velocity += m_acceleration * dt;
  pos += m_velocity * dt;

  transform->SetPosition(pos);
}

FPhysics* FPhysics::Clone()
{

  FPhysics* new_phy = PhysicsSystem::Instance()->CreateComponent();
  // no allocated data, so shallow copy works fine
  if (new_phy)
  {
    *new_phy = *this;
  }
  return new_phy;

}
