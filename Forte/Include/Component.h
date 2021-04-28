// file:   stub.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  All derived classes will inherit this header and use the class.
//  The GameObject class will use it as well.
#ifndef COMPONENT_H
#define COMPONENT_H

#include <forte.h>

class GameObject;

// Base Component Class
class FComponent
{
  public:
    //  A live list of all the possible components an object can have.
    enum class Type
    {
      CT_FTransform,
      CT_FPhysics,
      CT_FSprite,
      CT_FAnimation,

      CT_FCount,
      CT_FInvalid = -1
    };

    // Details:
    //  Should pretty much just get called by derived class' constructors.
    //
    // Inputs:
    // -type 
    //   The type of the component
    FComponent(Type type) : m_type(type), m_parent(nullptr) {}
    
    Type GetType() { return m_type; }

    GameObject* GetParent() { return m_parent; }
    void SetParent(GameObject* parent) { m_parent = parent; }

  protected:
    Type m_type;
    GameObject* m_parent;
};



#endif
