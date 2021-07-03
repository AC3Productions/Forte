// file:   SpriteComponent.h
// author: Alfaroh Corney III
// date:   2/25/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef SPRITE_H
#define SPRITE_H

#include <forte.h>
#include <component.h>
#include <TextureSource.h>

class FSprite : public FComponent
{
  public:

    FSprite();  
    
    void SetAlpha(float alpha) { m_alpha = alpha; }
    float GetAlpha() const { return m_alpha; }

    void SetFrame(int frame);
    int GetFrame() { return m_frame; }

    void SetTextureSource(TextureSource* texture);
    TextureSource* GetTextureSource() { return m_texture; }

    void SetUI(bool is_ui) { m_is_ui = is_ui; }
    bool IsUI() { return m_is_ui; }

    FSprite* Clone();

    void Render();

  private:
    float m_alpha;
    int m_frame;
    TextureSource* m_texture;

    bool m_is_ui;

};




#endif
