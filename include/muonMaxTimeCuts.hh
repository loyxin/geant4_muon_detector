// 继承muonSpecialCuts

#ifndef MUONMAXTIMECUTS_HH
#define MUONMAXTIMECUTS_HH
#include "G4ios.hh"
#include "globals.hh"
#include "muonSpecialCuts.hh"


class muonMaxTimeCuts : public muonSpecialCuts
{
  public:

     muonMaxTimeCuts(const G4String& processName ="muonMaxTimeCuts" );

     virtual ~muonMaxTimeCuts();

     // PostStep GPIL
     virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
                             G4double   previousStepSize,
                             G4ForceCondition* condition
                            );


  private:

  // hide assignment operator as private
      muonMaxTimeCuts(muonMaxTimeCuts&);
      muonMaxTimeCuts& operator=(const muonMaxTimeCuts& right);

};


#endif // MUONMAXTIMECUTS_HH
