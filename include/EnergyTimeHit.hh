#ifndef ENERGYTIMEHIT_HH
#define ENERGYTIMEHIT_HH

#include <G4VHit.hh>
#include <G4THitsMap.hh>
#include <G4ThreeVector.hh>

/**
  * Custom hit class used in task 4d.
  *
  * It holds infomation about energy deposits and position/time when
  * traversing a layer.
  */
class EnergyTimeHit : public G4VHit
{
public:
    // Memory allocation and de-allocation
    inline void* operator new(size_t);
    inline void  operator delete(void*);
    
    void SetDeltaEnergy(G4double deltaE) { fDeltaEnergy = deltaE; }
    void SetTime(G4double time) { fTime = time; }
    void SetPosition(G4ThreeVector pos) { fPosition = pos; }

    G4double GetDeltaEnergy() const { return fDeltaEnergy; }
    G4double GetTime() const { return fTime; }
    G4ThreeVector GetPosition() const { return fPosition; }

private:
    G4double fDeltaEnergy;
    G4double fTime;
    G4ThreeVector fPosition;
};

using EnergyTimeHitsCollection = G4THitsCollection<EnergyTimeHit>;

extern G4ThreadLocal G4Allocator<EnergyTimeHit> *hitAllocator;

inline void* EnergyTimeHit::operator new(size_t)
{
  if (!hitAllocator)
  {
      hitAllocator = new G4Allocator<EnergyTimeHit>;
  }
  return hitAllocator->MallocSingle();
}

inline void EnergyTimeHit::operator delete(void *aHit)
{
    if (!hitAllocator)
    {
        hitAllocator = new G4Allocator<EnergyTimeHit>;
    }
    hitAllocator->FreeSingle((EnergyTimeHit*) aHit);
}

#endif
