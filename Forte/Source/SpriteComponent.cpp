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

FSprite::FSprite() : FComponent(FComponent::Type::CT_FSprite), m_alpha(1.0f), m_frame(0), m_texture(nullptr)
{
}

FSprite* FSprite::Clone()
{
  FSprite* new_sprite = SpriteSystem::Instance()->CreateComponent();
  // no allocated data, so shallow copy works fine
  // Note: Shallow copy of m_texture is fine, since it is/will be
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

  if (m_texture)
  {
    RVec2 image_scale = m_texture->m_window.GetSize();

    raylib::Rectangle dest(pos, image_scale * scale);
    m_texture->texture.Draw(m_texture->m_window, dest, RVec2(0, 0), rot);
  }
  else
  {
    // For now, default drawing behavior is a blue square
    pos.DrawRectangle(m_parent->Get(FTransform)->GetScale(), BLUE);
  }

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