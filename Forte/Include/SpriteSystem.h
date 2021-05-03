// file:   SpriteSystem.h
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef SPRITESYSTEM_H
#define SPRITESYSTEM_H

#include <forte.h>
#include <System.h>

class FSprite;

class SpriteSystem : public FSystem
{
  public:
    static SpriteSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    void Render() override;
    ~SpriteSystem();

    // Optional: If this system manages a component,
    // then it should be responsible for creating and
    // destroying them. Not all systems do this.
    FSprite* CreateComponent();
    void DestroyComponent(FSprite*& sprite);

  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    SpriteSystem();
    static SpriteSystem* m_instance;

    // If managing components, store a vector of components
    std::vector<FSprite*> m_components;
};

#endif
