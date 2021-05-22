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

#include <fstream>
#include <json.hpp>
using JSON = nlohmann::json;

#pragma region temp
static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 900;

GameObject* obj = nullptr;

#pragma endregion

Engine::Engine() : m_is_running(true) ,trace_log(nullptr), m_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Forte", true)
{
}

void Engine::Init()
{

  trace_log = TraceLogger::Instance();
  trace.info.Log("Trace Log Initialized.");

  m_window.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Forte");
  SetTargetFPS(60);

  /* Initialize systems (order-dependent) */
  m_systems.push_back(AnimationSystem::Instance());
  m_systems.push_back(PhysicsSystem::Instance());

  /* Initialize systems (order-independent) */
  m_systems.push_back(TransformSystem::Instance());
  m_systems.push_back(SpriteSystem::Instance());
  m_systems.push_back(GameObjectSystem::Instance());
  m_systems.push_back(TextureAtlas::Instance());


#pragma region temp
  // This is more or less how an object will be generated.
  obj = GameObjectSystem::Instance()->CreateFromTemplate("test_obj");
  // This will get called in behaviors/scripting.
  obj->Get(FAnimation)->Start();
#pragma endregion

  trace.info.Log("Engine Fully Initialized.");
}


void Engine::Update()
{
  trace.verbose.Log("Engine: Update");

  if (m_window.ShouldClose())
  {
    m_is_running = false;
    return;
  }

#pragma region temp
  RVec2 vel;
  float speed = 500.0f;

  // Update all systems
  if (IsKeyDown(KEY_RIGHT)) 
    vel.x += 1;
  if (IsKeyDown(KEY_LEFT)) 
    vel.x -= 1;
  if (IsKeyDown(KEY_UP)) 
    vel.y -= 1;
  if (IsKeyDown(KEY_DOWN)) 
    vel.y += 1;

  vel = vel.Normalize() * speed;
  obj->Get(FPhysics)->SetVelocity(vel);
#pragma endregion
  
  float dt = m_window.GetFrameTime();

  // Update all the systems, in order
  for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
  {
    (*it)->Update(dt);
  }
}

void Engine::Render()
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

  // Render all systems
  for (auto it : m_systems)
  {
    it->Render();
  }

  /* FPS Counter (for debugging) */
  // Small rectangle around text (white, transparent)
  DrawRectangle(0, 0, 85, 25, Color{ 255, 255, 255, 150 });
  // FPS counter and label
  std::string fps("FPS: ");
  fps += std::to_string(GetFPS());
  DrawText(fps.c_str(), 5, 5, 20, BLACK);
  
  EndDrawing();
}

void Engine::ShutDown()
{
  trace.info.Log("Shutting down engine...");

  for (auto it : m_systems)
  {
    delete it;
  }

}



