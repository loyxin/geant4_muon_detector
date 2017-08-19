
#ifndef BLANK_BLANCPHYSICS_HH
#define BLANK_BLANCPHYSICS_HH 1

#include "G4VUserPhysicsList.hh"

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class blankPhysics: public G4VUserPhysicsList
{
public:
    blankPhysics();
    ~blankPhysics();
    virtual void ConstructParticle();

    virtual void ConstructProcess();

    void ConstructEM();

    void ConstructOp();

};

#endif //BLANK_BLANCPHYSICS_HH
