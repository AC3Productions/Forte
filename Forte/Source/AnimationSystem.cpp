// file:   AnimationSystem.cpp
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <AnimationSystem.h>

AnimationSystem* AnimationSystem::m_instance = nullptr;

AnimationSystem* AnimationSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new AnimationSystem;
  } 

  return m_instance;
}

AnimationSystem::AnimationSystem() : FSystem("Animation System")
{
}

void AnimationSystem::Init()
{
}

 FAnimation* AnimationSystem::CreateComponent()
 {
   FAnimation* new_comp = new FAnimation;
   m_components.push_back(new_comp);
   return new_comp;
 }
 
 void AnimationSystem::DestroyComponent(FAnimation*& Animation)
 {
   // Find the object and destroy it
   for (auto it : m_components)
   {
     if (it == Animation)
     {
       delete it;
       it = nullptr;
       Animation = nullptr;
     }
   }
 }

void AnimationSystem::Update(float dt)
{
  for (auto it : m_components)
  {
    if (it)
      it->Update(dt);
  }
}


AnimationSystem::~AnimationSystem()
{

}
