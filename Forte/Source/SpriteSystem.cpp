// file:   SpriteSystem.cpp
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <SpriteSystem.h>
#include <GameObject.h>
#include <SpriteComponent.h>

SpriteSystem* SpriteSystem::m_instance = nullptr;

SpriteSystem* SpriteSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new SpriteSystem;
  }

  return m_instance;
}

SpriteSystem::SpriteSystem() : FSystem("Sprite System")
{
}

void SpriteSystem::Init()
{
}

 FSprite* SpriteSystem::CreateComponent()
 {
   FSprite* new_comp = new FSprite;
   m_components.push_back(new_comp);
   return new_comp;
 }
 
 void SpriteSystem::DestroyComponent(FSprite*& sprite)
 {
   // Find the object and destroy it
   for (auto it : m_components)
   {
     if (it == sprite)
     {
       delete it;
       it = nullptr;
       sprite = nullptr;
     }
   }
 }

void SpriteSystem::Update(float dt)
{
  UNREF_PARAM(dt);
}

void SpriteSystem::Render()
{
  // Render all sprites
  for (auto it : m_components)
  {
    if (it)
    {
      GameObject* obj = it->GetParent();
      if (obj && obj->IsEnabled())
      {
        it->Render();
      }
    }
  }

}

SpriteSystem::~SpriteSystem()
{
  for (auto it : m_components)
  {
    delete it;
  }
}
