// file:   GameStateSystem.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  This should be included wherever something needs to change the game state
//  (so the engine, and behaviors).
#ifndef GAMESTATESYSTEM_H
#define GAMESTATESYSTEM_H

#include <forte.h>

class GameStateSystem
{
  public:
    void Init();
    void Update(float dt);
    void Shutdown();

  private:


};

#endif
