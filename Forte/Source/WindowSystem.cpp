// file:   WindowSystem.cpp
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//   Description of the purpose of the file goes here.
#pragma once
#include <WindowSystem.h>
#include <GLFW/glfw3.h>

#include <json.hpp>
using JSON = nlohmann::json;

WindowSystem* WindowSystem::m_instance = nullptr;

WindowSystem* WindowSystem::Instance()
{
  if (!m_instance)
  {
    m_instance = new WindowSystem;
  }

  return m_instance;
}

WindowSystem::WindowSystem() : FSystem("Window System"), m_window_width(0), m_window_height(0), m_window_mode(WindowMode::Windowed)
{
}

void WindowSystem::Init()
{
  // Try to load settings file
  if (!LoadSettingsFile())
  {
    // If it wasn't there, use default settings
    DefaultSettings();
  }
  
  SetTargetFPS(60);
}

bool WindowSystem::LoadSettingsFile()
{
  // Look for settings' json file
  std::string filename = std::string("settings.json");
  std::ifstream file(filename);
  if (file.is_open())
  {
    // Get the JSON data
    JSON settings_json;
    file >> settings_json;

    // Resolution
    m_window_width = settings_json["window"]["resolution"][0];
    m_window_height = settings_json["window"]["resolution"][1];
    m_window.SetSize(m_window_width, m_window_height);
    CenterWindow();

    // Window Mode
    std::string window_mode = settings_json["window"]["window mode"];
    SetWindowMode(window_mode);
    

    return true;
  }
  // File not loaded
  return false;
}

void WindowSystem::DefaultSettings()
{
  m_window_width = 960;
  m_window_height = 540;

  m_window.SetSize(m_window_width, m_window_height);
  
  m_window_mode = WindowMode::Windowed;

  CenterWindow();

}

void WindowSystem::Update(float dt)
{
}

WindowSystem::~WindowSystem()
{
}


void WindowSystem::CenterWindow()
{
  // Calculate position that puts window in the center of the screen
  int screen_width = GetMonitorWidth(0);
  int screen_height = GetMonitorHeight(0);
  // This centers the window even if screen_width < window_width (same for height).
  int m_posx = (screen_width - m_window_width) / 2;
  int m_posy = (screen_height - m_window_height) / 2;
  m_window.SetPosition(m_posx, m_posy);
}

void WindowSystem::SetWindowMode(const std::string& mode)
{
  if (mode == "Windowed")
  {
    m_window_mode = WindowMode::Windowed;
    if (IsWindowFullscreen())
    {
      ToggleFullscreen();
    }
    // Make sure window has top bar
    m_window.ClearState(FLAG_WINDOW_UNDECORATED);
    m_window.SetSize(m_window_width, m_window_height);
  }
  else if (mode == "Borderless")
  {
    m_window_mode = WindowMode::Borderless;
    // disable fullscreen
    if (IsWindowFullscreen())
    {
      ToggleFullscreen();
    }
    // Take bar off the top of the window
    m_window.SetState(FLAG_WINDOW_UNDECORATED);
    // Scale window to monitor dimensions
    m_window.SetSize(GetMonitorWidth(0), GetMonitorHeight(0));
  }
  // Fullscreen is Windowed borderless under the hood?
  else if (mode == "Fullscreen")
  {
    m_window_mode = WindowMode::Fullscreen;
    if (!IsWindowFullscreen())
    {
      ToggleFullscreen();
    }
    m_window_width = GetMonitorWidth(0);
    m_window_height = GetMonitorHeight(0);
    m_window.SetSize(m_window_width, m_window_height);
  }
}

void WindowSystem::SetWindowMode(WindowMode mode)
{
  //switch (mode)
  //{
  //}
}