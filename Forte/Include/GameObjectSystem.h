// file:   GameObjectSystem.h
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef GAMEOBJECTSYSTEM_H
#define GAMEOBJECTSYSTEM_H

#include <forte.h>
#include <System.h>
#include <GameObject.h>

class GameObjectSystem : public FSystem
{
  public:
    static GameObjectSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    ~GameObjectSystem();

    GameObject* CreateGameObject(const std::string& name);

    GameObject* FindGameObject(const std::string& name);
    GameObject* FindGameObject(int id);

    // Note: despite the name, this function does not
    // destroy persistent game objects. That will only
    // happen if the GameObjectSystem is destroyed 
    // ie. the destructor is called.
    void DestroyAllObjects();


  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    GameObjectSystem();
    static GameObjectSystem* m_instance;

    // Every game object has an internal id
    std::map<int, GameObject*> m_objects;
    int id_counter = 0;
};

#endif
