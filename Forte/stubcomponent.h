// file:   stubcomponent.h
// author: Alfaroh Corney III
// date:   00/00/0000
// 
// info:
//  Info about what kinds of places this file should be included.
#ifndef STUBCOMPONENT_H
#define STUBCOMPONENT_H

#include <forte.h>
#include <Component.h>

class FStub : public FComponent
{
public:
  FStub();

  void Update(float dt) override;
  void Render() override;
  FStub* Clone() override;

  private:

};

#endif
