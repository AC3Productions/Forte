// file:   StubSystem.cpp
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <StubSystem.h>

StubSystem* StubSystem::m_instance = nullptr;

StubSystem* StubSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new StubSystem;
  }

  return m_instance;
}

StubSystem::StubSystem() : FSystem("")
{
}

void StubSystem::Init()
{
}

// FStub* StubSystem::CreateComponent()
// {
//   FStub* new_comp = new FStub;
//   m_components.push_back(new_comp);
//   return new_comp;
// }
// 
// void StubSystem::DestroyComponent(FStub*& Stub)
// {
//   // Find the object and destroy it
//   for (auto it : m_components)
//   {
//     if (it == Stub)
//     {
//       delete it;
//       it = nullptr;
//       Stub = nullptr;
//     }
//   }
// }

void StubSystem::Update(float dt)
{
}

StubSystem::~StubSystem()
{
  //for (auto it : m_components)
  //{
  //  delete it;
  //}
}
