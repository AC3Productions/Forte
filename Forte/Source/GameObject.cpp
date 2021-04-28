// file:   stub.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <stub.h>
#include <GameObject.h>

GameObject::GameObject(const std::string& name) : m_name(name)
{
  for (int i = 0; i < (int)FComponent::Type::CT_FCount; ++i)
  {
    m_components[i] = nullptr;
  }
}

void GameObject::Render()
{
  //Get(FSprite)->Render();
}

void GameObject::Add(FComponent* component)
{
  int type = (int)component->GetType();

  if (component && 
      type > (int)FComponent::Type::CT_FInvalid && 
      type < (int)FComponent::Type::CT_FCount)
  {
    m_components[static_cast<int>(component->GetType())] = component;
    component->SetParent(this);
  }

}
