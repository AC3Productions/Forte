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
#include <map>
#include <json.hpp>
using JSON = nlohmann::json;

class GameObject;
class GameObjectFactory;

class GameObjectSystem : public FSystem
{
  public:
    static GameObjectSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    ~GameObjectSystem();

    // Creates an empty GameObject and gives it a name.
    GameObject* CreateGameObject(const std::string& name);

    // Details:
    //  Creates a GameObject based on the given template.
    //
    // Inputs:
    // -filename 
    //   The name of the Template file. Do NOT include the path OR file extension.
    //   Example: "Assets/myobj.json" should be passed in as "myobj".
    //
    // Output:
    //   If that template exists, returns a copy of it. Otherwise,
    //   returns nullptr.
    GameObject* CreateFromTemplate(const std::string& template_name);

    GameObject* FindGameObject(const std::string& name);
    GameObject* FindGameObject(int id);

    // Note: despite the name, this function does not
    // destroy all game objects--only non-persistent ones.
    // Those only get destroyed when the GameObjectSystem's 
    // destructor is called.
    void DestroyAllObjects();


  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    GameObjectSystem();
    static GameObjectSystem* m_instance;

    void AddToActiveObjects(GameObject* obj);

    // Takes the given JSON data and applies it to the given object.
    void DeserializeGameObject(GameObject* obj, const JSON& data);

    // Every game object has an internal id
    std::map<int, GameObject*> m_objects;
    int id_counter = 0;

    std::map<std::string, GameObject*> m_templates;
};

#endif
