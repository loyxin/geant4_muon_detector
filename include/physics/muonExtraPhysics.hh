

#ifndef muonExtraPhysics_h
#define muonExtraPhysics_h 1

#include "globals.hh"

#include "G4VPhysicsConstructor.hh"

class muonExtraPhysics : public G4VPhysicsConstructor
{
  public:

    muonExtraPhysics();
    virtual ~muonExtraPhysics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

};

#endif
