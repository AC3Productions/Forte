// file:   StubSystem.h
// author: Alfaroh Corney III
// date:   00/00/0000
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef STUBSYSTEM_H
#define STUBSYSTEM_H

#include <forte.h>
#include <System.h>

class FStub;

class StubSystem : public FSystem
{
  public:
    static StubSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    ~StubSystem();

    // Optional: If this system manages a component,
    // then it should be responsible for creating and
    // destroying them. Not all systems do this.
    FStub* CreateComponent();
    void DestroyComponent(FStub*& stub);

  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    StubSystem();
    static StubSystem* m_instance;

    // // If managing components, store a vector of components
    std::vector<FStub*> m_components;
};

#endif
