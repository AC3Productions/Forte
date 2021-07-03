// file:   stub.cpp
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//   Implementation of the Engine class
#include <Engine.h>

#include <PhysicsSystem.h>
#include <TransformSystem.h>
#include <SpriteSystem.h>
#include <AnimationSystem.h>
#include <GameObjectSystem.h>
#include <TextureAtlas.h>
#include <WindowSystem.h>

#include <fstream>
#include <json.hpp>
using JSON = nlohmann::json;

#pragma region temp
GameObject* obj = nullptr;
#pragma endregion

Engine::Engine() : m_is_running(true), trace_log(nullptr)
{
}

void Engine::Init()
{

  trace_log = TraceLogger::Instance();
  trace.info.Log("Trace Log Initialized.");

  /* Initialize systems (order-dependent) */
  m_systems.push_back(WindowSystem::Instance());

  m_systems.push_back(AnimationSystem::Instance());
  m_systems.push_back(PhysicsSystem::Instance());

  /* Initialize systems (order-independent) */
  m_systems.push_back(TransformSystem::Instance());
  m_systems.push_back(SpriteSystem::Instance());
  m_systems.push_back(GameObjectSystem::Instance());
  m_systems.push_back(TextureAtlas::Instance());

  for (auto it : m_systems)
  {
    if (it)
      it->Init();
  }

#pragma region temp
  // This is more or less how an object will be generated.
  // Will be in level-loading
  obj = GameObjectSystem::Instance()->CreateFromTemplate("test_obj");

  GameObjectSystem::Instance()->CreateFromTemplate("test_ball0");
  GameObjectSystem::Instance()->CreateFromTemplate("test_ball1");
  GameObjectSystem::Instance()->CreateFromTemplate("test_ball2");
  GameObjectSystem::Instance()->CreateFromTemplate("test_ball3");
  // This will get called in behaviors/scripting.
  obj->Get(FAnimation)->Start();
#pragma endregion

  trace.info.Log("Engine Fully Initialized.");
}


void Engine::Update()
{
  trace.verbose.Log("Engine: Update");

  if (WindowSystem::Instance()->ShouldClose())
  {
    m_is_running = false;
    return;
  }

#pragma region temp
  
  /* Temporary code, would be in scripts/behaviors later */
  
  // Move player with arrow keys
  RVec2 vel;
  float speed = 100.0f;
  
  if (IsKeyDown(KEY_RIGHT)) 
    vel.x += 1;
  if (IsKeyDown(KEY_LEFT)) 
    vel.x -= 1;
  if (IsKeyDown(KEY_UP)) 
    vel.y += 1;
  if (IsKeyDown(KEY_DOWN)) 
    vel.y -= 1;

  vel = vel.Normalize() * speed;
  obj->Get(FPhysics)->SetVelocity(vel);

  // Update camera position
  FCamera* camera = SpriteSystem::Instance()->GetCamera();
  camera->SetPosition(obj->Get(FTransform)->GetPosition());

#pragma endregion
  
  float dt = WindowSystem::Instance()->GetDT();

  // Update all the systems, in order
  for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
  {
    (*it)->Update(dt);
  }
}

void Engine::Render()
{
  BeginDrawing();
  ClearBackground(DARKBLUE);

  // Render all systems
  for (auto it : m_systems)
  {
    it->Render();
  }

  #pragma region temp

  /* FPS Counter (for debugging) */
  // Small rectangle around text (white, transparent)
  DrawRectangle(0, 0, 85, 25, Color{ 255, 255, 255, 150 });
  // FPS counter and label
  std::string fps("FPS: ");
  fps += std::to_string(GetFPS());
  DrawText(fps.c_str(), 5, 5, 20, BLACK);
  
  /* Position (debug) */
  // Small rectangle around text (white, transparent)
  DrawRectangle(0, 25, 325, 25, Color{ 255, 255, 255, 150 });
  // Data
  const RVec2& pos = obj->Get(FTransform)->GetPosition();
  std::string pos_str("Position: ");
  pos_str += std::to_string(pos.x) + std::string(", ") + std::to_string(pos.y);
  DrawText(pos_str.c_str(), 5, 30, 20, BLACK);

  #pragma endregion

  EndDrawing();
}

void Engine::ShutDown()
{
  trace.info.Log("Shutting down engine...");

  // Shut down in reverse order
  for (auto it = m_systems.rbegin(); it != m_systems.rend(); ++it)
  {
    delete *it;
  }

}



