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

#pragma region temp
static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 900;

GameObject* obj = nullptr;
TextureSource* texture = nullptr;

#pragma endregion

Engine::Engine() : m_is_running(true) ,trace_log(nullptr), m_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Forte", true)
{
}

void Engine::Init()
{

  trace_log = TraceLogger::Instance();
  trace.info << "Trace Log Initialized.";

  m_window.Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Forte");
  SetTargetFPS(60);

  /* Initialize systems (order-dependent) */
  m_systems.push_back(AnimationSystem::Instance());
  m_systems.push_back(PhysicsSystem::Instance());

  /* Initialize systems (order-independent) */
  m_systems.push_back(TransformSystem::Instance());
  m_systems.push_back(SpriteSystem::Instance());
  m_systems.push_back(GameObjectSystem::Instance());


#pragma region temp

  // This is more or less how an object will be generated.
  // The next step is to load them from files.

  obj = GameObjectSystem::Instance()->CreateGameObject("test object");
  
  FPhysics* physics = PhysicsSystem::Instance()->CreateComponent();
  obj->Add(physics);

  FTransform* transform = TransformSystem::Instance()->CreateComponent();
  transform->SetPosition(RVec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
  transform->SetRotation(0.0f);
  transform->SetScale(RVec2(3, 3));
  obj->Add(transform); 

  FSprite* sprite = SpriteSystem::Instance()->CreateComponent();
  texture = new TextureSource("Assets/gem_spin.png", 3, 5);
  sprite->SetTextureSource(texture);
  obj->Add(sprite);
  
  FAnimation* animation = AnimationSystem::Instance()->CreateComponent();
  animation->SetFrameCount(12);
  animation->SetFrameRate(12.0f);
  animation->SetLooping(true);

  obj->Add(animation);

  // This will either happen by default or get called in a behavior script.
  animation->Start(); 
  
#pragma endregion

  trace.info << "Engine Fully Initialized.";
}


void Engine::Update()
{
  trace.verbose << "Engine: Update";

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
  trace.info << "Shutting down engine...";

  for (auto it : m_systems)
  {
    delete it;
  }

  delete texture;
}



