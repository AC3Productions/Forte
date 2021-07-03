// file:   TextureAtlas.cpp
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <TextureAtlas.h>
#include <fstream>
#include <TextureSource.h>
#include <json.hpp>

using JSON = nlohmann::json;

TextureAtlas* TextureAtlas::m_instance = nullptr;

TextureAtlas* TextureAtlas::Instance()
{
  if (!m_instance)
  {
    m_instance = new TextureAtlas;
  }

  return m_instance;
}

TextureAtlas::TextureAtlas() : FSystem("Texture Atlas")
{
}

// Tries to find the texture if it's not already loaded.
TextureSource* TextureAtlas::GetTexture(const std::string& name)
{
  // If we already have the texture, just send it out
  auto texture = m_textures.find(name);
  if (texture != m_textures.end())
  {
    return texture->second;
  }

  // Look for texture source's json file
  std::string filename = std::string("Assets/") + name + std::string(".json");
  std::ifstream file(filename);
  if (file.is_open())
  {
    // Get the JSON data
    JSON texture_json;
    file >> texture_json;

    // Try to open the texture file
    std::string filename = std::string("Assets/") + texture_json["image"].get<std::string>();
    TextureSource* new_texture = new TextureSource(filename.c_str(), texture_json["rows"], texture_json["columns"]);
    if (new_texture)
    {
      // Add to atlas
      m_textures[name] = new_texture;

      trace.info.Log("Loaded texture: " + filename);

      // Send it out
      return new_texture;
    }
    else
    {
      trace.error.Log("Texture allocation failed. Either out of memory (unlikely), or something went wrong trying to load the texture.");
    }

  }
  else
  {
    trace.error.Log("Tried to load a texture which does not have a .json file.");
  }
  return nullptr;

}

// Unloads all textures
void TextureAtlas::FlushTextures()
{
  for (auto it : m_textures)
  {
    delete it.second;
  }

  m_textures.clear();

}

// Unloads all textures
TextureAtlas::~TextureAtlas()
{
  FlushTextures();
}
