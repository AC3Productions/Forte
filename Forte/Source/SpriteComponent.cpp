// file:   SpriteComponent.cpp
// author: Alfaroh Corney III
// date:   2/25/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <SpriteComponent.h>
#include <GameObject.h>
#include <SpriteSystem.h>

FSprite::FSprite() : FComponent(FComponent::Type::CT_FSprite), m_alpha(1.0f), m_frame(0), m_texture(nullptr), m_is_ui(false)
{
}

FSprite* FSprite::Clone()
{
  FSprite* new_sprite = SpriteSystem::Instance()->CreateComponent();
  // no allocated data, so shallow copy works fine
  // Note: Shallow copy of m_texture is fine, since it is
  // a pointer to a texture stored in the Texture Atlas
  // ie. the textures will always outlast the objects.
  if (new_sprite)
  {
    *new_sprite = *this;
  }
  return new_sprite;
}

void FSprite::Render()
{
  // Draw a circle at given position
  FTransform* transform = m_parent->Get(FTransform);
  RVec2 pos = transform->GetPosition();
  float rot = transform->GetRotation();
  RVec2 scale = transform->GetScale();

  // If not a UI element, convert from world space to screen space
  if (!m_is_ui)
  {
    // Offset  position and scale based on camera position
    FCamera* camera = SpriteSystem::Instance()->GetCamera();
    pos -= camera->GetPosition();

    // Convert all our stuff to screen space
    pos.x += TRUE_WIDTH / 2;
    pos.y = -pos.y + TRUE_HEIGHT / 2;
  }

  // Scale to window dimensions
  float window_scale = SpriteSystem::Instance()->GetWindowScale();
  pos *= window_scale;
  scale *= window_scale;

  if (m_texture)
  {
    RVec2 image_scale = m_texture->m_window.GetSize();

    RVec2 final_scale = image_scale * scale;
    raylib::Rectangle dest(pos, final_scale);
    m_texture->texture.Draw(m_texture->m_window, dest, final_scale * 0.5f, rot);
    
  }
  else
  {
    // For now, default drawing behavior is a blue square
    pos.DrawRectangle(m_parent->Get(FTransform)->GetScale(), BLUE);
  }

  // Debug draw: Draw origin of object
  pos.DrawCircle(1.0f * window_scale, WHITE);
  pos.DrawCircle(0.5f * window_scale, RED);

}


void FSprite::SetFrame(int frame)
{
  if (!m_texture)
  {
    trace.error.Log("Trying to set the frame of a sprite which has no texture.");
    return;
  }

  m_frame = frame;
  m_texture->UpdateWindow(frame);
}

void FSprite::SetTextureSource(TextureSource* texture)
{
  m_texture = texture;
}