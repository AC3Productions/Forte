// file:   TextureAtlas.h
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <forte.h>
#include <System.h>
#include <map>

struct TextureSource;

class TextureAtlas : public FSystem
{
  public:
    static TextureAtlas* Instance();
    ~TextureAtlas();

    // Details:
    //  Return a pointer to a texture. If it's a texture that hasn't been loaded yet,
    //  it will try to load the texture first.
    //
    // Inputs:
    // -filename 
    //   The name of the texture's json file. Do NOT include the path OR file extension.
    //   Example: "Assets/mytexture.json" should be passed in as "mytexture".
    //
    // Output:
    //   If the texture exists, returns the texturesource. Otherwise,
    //   returns nullptr.
    TextureSource* GetTexture(const std::string& name);

  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    TextureAtlas();
    static TextureAtlas* m_instance;

    std::map<std::string, TextureSource*> m_textures;
};

#endif
