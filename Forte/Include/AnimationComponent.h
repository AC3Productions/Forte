// file:   AnimationComponent.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  Anything that needs to initialize, or start playing an animation, should include this file.
#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <forte.h>
#include <component.h>
#include <json.hpp>
class FAnimation : public FComponent
{
  public:
    FAnimation(unsigned frame_count = 1, float frame_rate = 1.0f, bool looping = true);
    // Start an animation
    void Start();
     
    void Update(float dt);

    /* Setters and Getters for Initializing an animation */
    void SetFrameCount(unsigned count) { m_frame_count = count; }
    void SetFrameRate(float fps) { m_frame_duration = 1.0f / fps; }
    void SetLooping(bool looping) { m_loop = looping; }

    FAnimation* Clone() override;

  private:
    /* 
       NOTE TO SELF - IF PRIVATE MEMBERS GET UPDATED, THE FOLLOWING MEMBER
       FUNCTIONS MUST BE UPDATED AS WELL:
         -Constructor
         -Clone
         -Destructor, if memory allocation is involved
    */

    unsigned m_frame_count;
    // Amount of time to display each frame for.
    // Should be serialized as a frame rate (fps)
    float m_frame_duration;
    bool m_loop;     // Whether animation should loop indefinitely

    /* All these variables are internal-use only */
    float m_curr_frame_time;
    bool m_playing;  // Currently playing
    bool m_finished; // Whether the animation has reached the end of the sequence

    void AdvanceFrame();

};

#endif
