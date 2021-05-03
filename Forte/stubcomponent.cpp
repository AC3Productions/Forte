// file:   stubcomponent.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <stubcomponent.h>
#include <StubSystem.h>

FStub::FStub() : FComponent(FComponent::Type::CT_FInvalid)
{

}

void FStub::Update(float dt)
{

}

void FStub::Render()
{

}

// This method NEEDS to be updated if your class 
// has dynamic memory allocation.
FStub* FStub::Clone()
{

  FStub* new_stub = StubSystem::Instance()->CreateComponent();
  // no allocated data, so shallow copy works fine
  if (new_stub)
  {
    *new_stub = *this;
  }
  return new_stub;

}
