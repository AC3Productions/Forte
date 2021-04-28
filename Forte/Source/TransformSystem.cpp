// file:   TransformSystem.cpp
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <TransformSystem.h>

TransformSystem* TransformSystem::m_instance = nullptr;

TransformSystem* TransformSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new TransformSystem;
  }

  return m_instance;
}

TransformSystem::TransformSystem() : FSystem("Transform System")
{
}

void TransformSystem::Init()
{
}

FTransform* TransformSystem::CreateComponent()
{
  FTransform* new_comp = new FTransform;
  m_components.push_back(new_comp);
  return new_comp;
}

void TransformSystem::DestroyComponent(FTransform*& transform)
{
  // Find the object and destroy it
  for (auto it : m_components)
  {
    if (it == transform)
    {
      delete it;
      // No dangling pointers
      it = nullptr;
      transform = nullptr;
    }
  }
}

void TransformSystem::Update(float dt)
{
  UNREF_PARAM(dt);
}

TransformSystem::~TransformSystem()
{
  // Delete all transforms
  for (auto it : m_components)
  {
    delete it;
  }
}
