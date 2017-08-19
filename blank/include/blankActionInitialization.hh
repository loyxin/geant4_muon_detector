

#ifndef blankActionInitialization_h
#define blankActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class blankActionInitialization : public G4VUserActionInitialization
{
  public:
    blankActionInitialization();
    virtual ~blankActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};



#endif

    
