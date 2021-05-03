// file:   TransformSystem.h
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//  Only places that need to create a transform component, or need access to ALL transform components,
//  should include this file.
#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

#include <forte.h>
#include <System.h>

class FTransform;

class TransformSystem : public FSystem
{
  public:
    static TransformSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    ~TransformSystem();

    // Optional: If this system manages a component,
    // then it should be responsible for creating and
    // destroying them. Not all systems do this.
    FTransform* CreateComponent();
    void DestroyComponent(FTransform*& transformtub);

  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    TransformSystem();
    static TransformSystem* m_instance;

    // // If managing components, store a vector of components
    std::vector<FTransform*> m_components;
};

#endif
