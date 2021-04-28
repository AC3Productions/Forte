// file:   GameObject.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  Anything that uses/manages Game Objects should include this. Long-term, that'll
//  probably just be the Game Object Factory and Game Object Management System.
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <forte.h>
#include <PhysicsComponent.h>
#include <TransformComponent.h>
#include <SpriteComponent.h>
#include <AnimationComponent.h>

#define Get(type) GetComponent<type>(FComponent::Type::CT_##type)

class GameObject
{
  public:
    GameObject(const std::string& name);
    void Update(float dt);
    void Render();

    template <typename T>
    T* GetComponent(FComponent::Type type)
    {
      return static_cast<T*>(m_components[static_cast<int>(type)]);
    }

    void Add(FComponent* component);

  private:
    std::string m_name;
    FComponent* m_components[(int)FComponent::Type::CT_FCount];

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
