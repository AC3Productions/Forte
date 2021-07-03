// file:   WindowSystem.h
// author: Alfaroh Corney III
// date:   3/23/2021
// 
// info:
//  Files that need to adjust Window settings (like resolution) should include this (and the Engine).
//  That's not very many things.
#ifndef WINDOWSYSTEM_H
#define WINDOWSYSTEM_H

#include <forte.h>
#include <System.h>

class WindowSystem : public FSystem
{
  public:
    enum class WindowMode
    {
      Windowed = 0,
      Borderless,
      Fullscreen,
    };

    static WindowSystem* Instance();

    void Init() override;
    void Update(float dt) override;
    ~WindowSystem();

    bool ShouldClose() { return m_window.ShouldClose(); }
    float GetDT() { return m_window.GetFrameTime(); }

  private:
    // These are for the singleton pattern.
    // It ensures that you never have multiple instances
    // of the system.
    WindowSystem();
    static WindowSystem* m_instance;
    raylib::Window m_window;

    int m_window_width;
    int m_window_height;

    WindowMode m_window_mode;

    // Tries to open a settings file and configure the window, returns whether it was successful
    bool LoadSettingsFile();
    // Set default window/game settings
    void DefaultSettings();
    // Place the window in the center of the monitor (usually after resizing)
    void CenterWindow();

    void SetWindowMode(const std::string& mode);
    void SetWindowMode(WindowMode mode);

};

#endif
