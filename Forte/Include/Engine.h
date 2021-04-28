// file:   Engine.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  This should only be included in main, and places that want
//  to close the game (ex. behaviors).
#ifndef ENGINE_H
#define ENGINE_H

#include <forte.h>
#include <raylib.h>
#include <System.h>
#include <GameObject.h>

class Engine 
{
public:
  Engine();

  void Init();
  void Update();
  void Render();
  void ShutDown();

  bool IsRunning() { return m_is_running; }
  void EndGame() { m_is_running = false; }

private:
  /* Engine-specific veriables */
  bool m_is_running; // When set to false the engine shuts down
  TraceLogger* trace_log;

  /* Systems */
  raylib::Window m_window;

  std::vector<FSystem*> m_systems;

};

#endif
