// file:   PhysicsComponent.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <forte.h>
#include <Component.h>

class FPhysics : public FComponent
{
  public:
    FPhysics() : FComponent(FComponent::Type::CT_FPhysics), 
                 m_velocity(0,0), 
                 m_acceleration(0,0) {}

    void Update(float dt);
    
    const RVec2& GetVelocity() const { return m_velocity; }
    void SetVelocity(const RVec2& vel) { m_velocity = vel; }

    const RVec2& GetAcceleration() const { return m_velocity; }
    void SetAcceleration(const RVec2& vel) { m_velocity = vel; }

    FPhysics* Clone() override;

  private:
    RVec2 m_velocity;
    RVec2 m_acceleration;

};

#endif
