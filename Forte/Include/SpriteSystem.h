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
#include <Camera.h>

#define TRUE_WIDTH 320
#define TRUE_HEIGHT 180

class FSprite;


class SpriteSystem : public FSystem
{
  public:
    static SpriteSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    void Render() override;
    ~SpriteSystem();

    float GetWindowScale() { return m_world_to_window; }

    // Creates a sprite component and adds it to the managed list of sprites.
    FSprite* CreateComponent();
    
    // Removes a sprite component from the active list.
    void DestroyComponent(FSprite*& sprite);

    // Get the camera, to modify its position and zoom.
    FCamera* GetCamera() { return m_camera->Instance(); }

  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    SpriteSystem();
    static SpriteSystem* m_instance;

    // If managing components, store a vector of components
    std::vector<FSprite*> m_components;

    // World to window resolution scale
    // The world's screen dimensions are TRUE_WIDTH x TRUE_HEIGHT
    float m_world_to_window = 1.0f;

    // The camera data (position, zoom).
    FCamera* m_camera;

};

#endif
