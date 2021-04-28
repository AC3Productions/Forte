// file:   System.h
// author: Alfaroh Corney III
// date:   1/31/2021
// 
// info:
//  All derived system classes (and the Engine) will include this file.
#ifndef SYSTEM_H
#define SYSTEM_H

#include <forte.h>

class FSystem
{
  public:
    // Being able to copy/move a system would almost certainly cause lots of problems
    FSystem(const FSystem &) = delete;
    FSystem(const FSystem &&) = delete;
    FSystem& operator=(const FSystem &) = delete;
    FSystem& operator=(const FSystem &&) = delete;

    FSystem(const char *name) : m_name(name) {}

    // Destructor must be implemented in all derived classes
    virtual ~FSystem() = default;

    virtual void Init() {}
    virtual void Update(float dt) { UNREF_PARAM(dt); }
    virtual void Render() {}

    const std::string& GetName() const { return m_name; }

  private:
    std::string m_name;

};

#endif
