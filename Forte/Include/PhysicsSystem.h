// file:   PhysicsSystem.h
// author: Alfaroh Corney III
// date:   4/26/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <forte.h>
#include <System.h>
#include <PhysicsComponent.h>

class PhysicsSystem : public FSystem
{
public:
  static PhysicsSystem* Instance();

  void Init() override;
  void Update(float dt) override;
  ~PhysicsSystem();

  // Optional: If this system manages a component,
  // then it should be responsible for creating and
  // destroying them. Not all systems do this.
  FPhysics* CreateComponent();
  void DestroyComponent(FPhysics*& physics);

private:
  // These are for the singleton pattern.
  // It ensures that you never have multiple instances
  // of the system.
  PhysicsSystem();
  static PhysicsSystem* m_instance;

  // // If managing components, store a vector of components
  std::vector<FPhysics*> m_components;
};

// Details:
//  Important info that is not made immediately clear from the function name and parameters.
//
// Inputs:
// -param1 
//   Description of parameter
// -param2
//   Description of parameter
//         
// Output:
//   Useful information about the return value, and/or whatever else the function did.


#endif
