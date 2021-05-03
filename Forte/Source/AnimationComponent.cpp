// file:   AnimationComponent.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <AnimationComponent.h>
#include <GameObject.h>
#include <SpriteComponent.h>
#include <AnimationSystem.h>

FAnimation::FAnimation(unsigned frame_count, float frame_rate, bool looping) : FComponent(FComponent::Type::CT_FAnimation),
                                                                               m_frame_count(frame_count), 
                                                                               m_frame_duration(1.0f / frame_rate), 
                                                                               m_curr_frame_time(m_frame_duration),
                                                                               m_playing(false), m_loop(looping), 
                                                                               m_finished(false)
{
}

void FAnimation::Start()
{
  m_playing = true;

  FSprite* sprite = GetParent()->Get(FSprite);
  if (sprite)
    sprite->SetFrame(0);
  else
  {
    trace.error.Log("Tried to play an animation on an object which has no texture.");
  }
}

void FAnimation::Update(float dt)
{
  m_finished = false;
  if (m_playing)
  {
    m_curr_frame_time -= dt;

    // End of current frame time, move to next frame
    if (m_curr_frame_time <= 0)
    {
      AdvanceFrame();
    }
  }

}

FAnimation* FAnimation::Clone()
{
  FAnimation* new_anim = AnimationSystem::Instance()->CreateComponent();
  // no allocated data, so shallow copy works fine
  if (new_anim)
  {
    *new_anim = *this;
  }
  return new_anim;
}

void FAnimation::AdvanceFrame()
{
  FSprite* sprite = m_parent->Get(FSprite);

  if (!sprite)
  {
    throw std::exception("Trying to advance the frame on an animation with no sprite attached.");
  }

  int index = sprite->GetFrame() + 1;

  // End of animation
  if ((unsigned)index >= m_frame_count)
  {
    // Set back to beginning of animation
    if (m_loop)
    {
      index = 0;
    }
    // Otherwise, done playing animation
    else
    {
      index = m_frame_count - 1;
      m_playing = false;

    }
    m_finished = true;

  }

  // Potentially not done playing animation
  if (m_playing)
  {
    sprite->SetFrame(index);
    m_curr_frame_time += m_frame_duration;
  }
  else
  {
    m_curr_frame_time = 0;
  }
}





