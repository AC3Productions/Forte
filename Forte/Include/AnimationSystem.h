// file:   AnimationSystem.h
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <forte.h>
#include <System.h>
#include <AnimationComponent.h>

class AnimationSystem : public FSystem
{
  public:
    static AnimationSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    ~AnimationSystem();

    // Optional: If this system manages a component,
    // then it should be responsible for creating and
    // destroying them. Not all systems do this.
    FAnimation* CreateComponent();
    void DestroyComponent(FAnimation*& animation);

  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    AnimationSystem();
    static AnimationSystem* m_instance;

    // If managing components, store a vector of components
    std::vector<FAnimation*> m_components;
};

#endif
