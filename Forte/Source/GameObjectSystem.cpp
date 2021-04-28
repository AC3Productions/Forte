// file:   GameObjectSystem.cpp
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//   Description of the purpose of the file goes here.
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

GameObjectSystem::GameObjectSystem() : FSystem("Game Object System")
{
}

void GameObjectSystem::Init()
{
}

void GameObjectSystem::Update(float dt)
{
}

GameObjectSystem::~GameObjectSystem()
{

}
