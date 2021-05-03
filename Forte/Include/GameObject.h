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
    // Details:
    //  Constructs a game object with the given name. components must be added using Add().
    //
    // Input:
    // -name 
    //   The name of the object.
    GameObject(const std::string& name);
    ~GameObject();

    template <typename T>
    T* GetComponent(FComponent::Type type)
    {
      return static_cast<T*>(m_components[static_cast<int>(type)]);
    }

    void Add(FComponent* component);

    GameObject* Clone();

    bool IsPersistent() { return m_persistent; }

    void SetEnabled(bool enabled) { m_enabled = enabled; }
    bool IsEnabled() { return m_enabled; }
    
    const std::string& GetName() { return m_name; }    

  private:
    std::string m_name;
    FComponent* m_components[(int)FComponent::Type::CT_FCount];
    bool m_persistent; // persistent game objects are not destroyed between game states
    bool m_enabled;

};




#endif
