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

GameObjectSystem* GameObjectSystem::m_instance = nullptr;

GameObjectSystem* GameObjectSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new GameObjectSystem;
  }

  return m_instance;
}

// Destroys all objects except the 
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
  // Remove objects marked as destroyed
}

GameObjectSystem::~GameObjectSystem()
{
  // Destroy ALL the objects, including persistent ones
  for (auto it : m_objects)
  {
    delete it.second;
  }
}

// TEMP BEHAVIOR - Creates an empty (but usable) game object with given name and returns it
// Once GameObjectFactory is implemented, this function will get an object from there instead
GameObject* GameObjectSystem::CreateGameObject(const std::string& name)
{
  
  GameObject* new_obj = new GameObject(name);
  if (new_obj)
  {
    m_objects[id_counter] = new_obj;
    ++id_counter;
  }

  return new_obj;
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
    trace.error << msg;
    return nullptr;
  }
}
