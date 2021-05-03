// file:   GameObjectSystem.cpp
// author: Alfaroh Corney III
// date:   4/28/2021
// 
// info:
//   The Game Object System manages game objects--this is where objects 
//   currently being updated in the game are created, destroyed and found. 
//   All game objects will (at least when initially created) be based off of 
//   templates from the Game Object Factory.
#pragma once
#include <GameObjectSystem.h>
#include <GameObject.h>
#include <PhysicsSystem.h>
#include <TransformSystem.h>
#include <SpriteSystem.h>
#include <AnimationSystem.h>

#pragma region temp
static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 900;

TextureSource* texture = nullptr;
#pragma endregion

GameObjectSystem* GameObjectSystem::m_instance = nullptr;

GameObjectSystem* GameObjectSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new GameObjectSystem;
  }

  return m_instance;
}

// Destroys all objects that are not persistent.
void GameObjectSystem::DestroyAllObjects()
{
  // Can't use the clean
  for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
  {
    if (!(*it).second->IsPersistent())
    {
      delete (*it).second;
      m_objects.erase(it);
    }
  }
}

GameObjectSystem::GameObjectSystem() : FSystem("Game Object System")
{
}

void GameObjectSystem::Init()
{
}

void GameObjectSystem::Update(float dt)
{
  UNREF_PARAM(dt);
  // TODO: Remove objects which are marked as destroyed
}

GameObjectSystem::~GameObjectSystem()
{
  // Destroy ALL the objects, including persistent ones
  for (auto it : m_objects)
  {
    delete it.second;
  }
  // Destroy all templates as well
  for (auto it : m_templates)
  {
    delete it.second;
  }

#pragma region temp
  delete texture;
#pragma endregion
}

// Creates an empty (but usable) game object with given name and returns it.
GameObject* GameObjectSystem::CreateGameObject(const std::string& name)
{
  GameObject* new_obj = new GameObject(name);
  return new_obj;
}

// Creates an object based on the given template name. Templates are stored in JSON files,
// so if we haven't already used that template so far, we check and see if there's a JSON 
// file with that template.
GameObject* GameObjectSystem::CreateFromTemplate(const std::string& template_name)
{
  // Look for the template first
  auto temp = m_templates.find(template_name);
  if (temp != m_templates.end())
  {
    // Clone that game object and return it
    GameObject* new_obj = temp->second->Clone();
    AddToActiveObjects(new_obj);
    return new_obj;
  }
  // If it's not loaded yet, look for the file
  else
  {
    // Try to open the JSON file
    std::string filename = std::string("Assets/") + template_name + std::string(".json");
    std::ifstream file(filename);

    if (file.is_open())
    {
      // Create the new template, add it to the list of templates, and clone it
      GameObject* new_template = new GameObject(template_name);
      if (new_template)
      {
        // fill JSON class with data from the file
        JSON data;
        file >> data;
        // Send it to deserializer and add it to the template list
        DeserializeGameObject(new_template, data);
        m_templates[template_name] = new_template;
        new_template->SetEnabled(false); // Templates should not be updated or rendered

        // Clone that game object and return it
        GameObject* new_obj = new_template->Clone();
        AddToActiveObjects(new_obj);
        return new_obj;
      }
    } // File could not open
  }
  // Template not already found and file not opened. Something has gone wrong.
  std::string msg("Unable to find template object for \"");
  msg += template_name + ".json\".";
  trace.error.Log(msg);
  return nullptr;
}

void GameObjectSystem::DeserializeGameObject(GameObject* obj, const JSON& data)
{
  /* Deserialize each component, if possible */

  if (data.contains("physics"))
  {
    if (data.at("physics"))
    {
      FPhysics* physics = PhysicsSystem::Instance()->CreateComponent();
      obj->Add(physics);
    }
  }

  if (data.contains("transform"))
  {
    FTransform* transform = TransformSystem::Instance()->CreateComponent();
    transform->SetPosition(RVec2(SCREEN_WIDTH * (float)data["transform"]["position"][0], SCREEN_HEIGHT * (float)data["transform"]["position"][1]));
    transform->SetRotation(data["transform"]["rotation"]);
    transform->SetScale(RVec2(data["transform"]["scale"][0], data["transform"]["scale"][1]));
    obj->Add(transform);
  }
  /* STILL HARDCODED--REQUIRES TEXTURE ATLAS DESERIALIZATION */
  if (data.contains("sprite"))
  {
    FSprite* sprite = SpriteSystem::Instance()->CreateComponent();
    texture = new TextureSource("Assets/gem_spin.png", 3, 5);
    sprite->SetTextureSource(texture);
    obj->Add(sprite);
  }

  if (data.contains("animation"))
  {
    FAnimation* animation = AnimationSystem::Instance()->CreateComponent();

    animation->SetFrameCount(data["animation"]["framecount"]);
    animation->SetFrameRate(data["animation"]["framerate"]);
    animation->SetLooping(data["animation"]["looping"]);
    obj->Add(animation);
  }
}

GameObject* GameObjectSystem::FindGameObject(const std::string& name)
{
  for (auto it : m_objects)
  {
    if (it.second->GetName() == name)
      return it.second;
  }
  
  return nullptr;

}

GameObject* GameObjectSystem::FindGameObject(int id)
{
  try
  {
    return m_objects.at(id);
  }
  catch (std::out_of_range)
  {
    std::string msg("Could not find a game object with id ");
    msg += std::to_string(id);
    trace.error.Log(msg);
    return nullptr;
  }
}

void GameObjectSystem::AddToActiveObjects(GameObject* obj)
{
  if (obj)
  {
    m_objects[id_counter] = obj;
    ++id_counter;
  }
}
