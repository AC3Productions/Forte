// file:   PhysicsSystem.cpp
// author: Alfaroh Corney III
// date:   4/26/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <forte.h>
#include <PhysicsSystem.h>
#include <TransformComponent.h>

PhysicsSystem* PhysicsSystem::m_instance = nullptr;

PhysicsSystem* PhysicsSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new PhysicsSystem;
  }

  return m_instance;
}


PhysicsSystem::PhysicsSystem() : FSystem("Physics System")
{
}

void PhysicsSystem::Init()
{
}

FPhysics* PhysicsSystem::CreateComponent()
{
  FPhysics* new_comp = new FPhysics;
  m_components.push_back(new_comp);
  return new_comp;
}

void PhysicsSystem::DestroyComponent(FPhysics*& physics)
{
  // Find the object and destroy it
  for (auto it : m_components)
  {
    if (it == physics)
    {
      delete it;
      it = nullptr;
      physics = nullptr;
    }
  }
}

void PhysicsSystem::Update(float dt)
{
  // Update all the physics components
  for (auto it : m_components)
  {
    if (it)
    {
      it->Update(dt);
    }
  }
}

PhysicsSystem::~PhysicsSystem()
{
  // Delete all the components
  for (auto it : m_components)
  {
    delete it;
  }
}

