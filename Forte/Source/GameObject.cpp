// file:   stub.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <GameObject.h>

GameObject::GameObject(const std::string& name) : m_name(name), m_persistent(false)
{
  for (int i = 0; i < (int)FComponent::Type::CT_FCount; ++i)
  {
    m_components[i] = nullptr;
  }
}

GameObject::~GameObject()
{
  // Remove the parent from all components (which disables them).
  // Technically, the more memory-efficient solution is to 
  // Call DestroyComponent() on each system the game object
  // has, but that's 1) ugly, 2) requires updating this function
  // when I add systems/components, and 3) is quite slow with
  // lots of objects loaded (since each DestroyComponent() call
  // checks the component lists linearly to remove them).
  // This isn't a particularly great solution either imo, will 
  // need to come back to this.
  for (auto it : m_components)
  {
    it->SetParent(nullptr);
  }

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

GameObject* GameObject::Clone()
{
  GameObject* new_clone = new GameObject(m_name);

  if (new_clone)
  {
    // Copy all the components
    for (int i = 0; i < static_cast<int>(FComponent::Type::CT_FCount); ++i)
    {
      if (m_components[i])
      {
        new_clone->Add(m_components[i]->Clone());
      }
    }
  }

  return new_clone;

}
