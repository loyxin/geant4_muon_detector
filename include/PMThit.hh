#ifndef PMTHIT_HH
#define PMTHIT_HH 1

#include <G4VHit.hh>
#include <G4THitsMap.hh>
#include <G4ThreeVector.hh>

// 设置 Hit 容器
class PMThit : public G4VHit
{
public:
    // Memory allocation and de-allocation
    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void SetDeltaEnergy(G4double deltaE) { fDeltaEnergy = deltaE; }
    void SetTime(G4double time) { fTime = time; }
    void SetPosition(G4ThreeVector pos) { fPosition = pos; }
    void SetName(G4String name){fname=name;}
    
    G4double GetDeltaEnergy() const { return fDeltaEnergy; }
    G4double GetTime() const { return fTime; }
    G4ThreeVector GetPosition() const { return fPosition; }
    G4String GetName()const{return fname;}
private:
    G4double fDeltaEnergy;
    G4double fTime;
    G4ThreeVector fPosition;
    G4String fname;
};

using pmtHitsCollection = G4THitsCollection<PMThit>;

extern G4ThreadLocal G4Allocator<PMThit> *pmthitAllocat;

inline void* PMThit::operator new(size_t)
{
  if (!pmthitAllocat)
  {
      pmthitAllocat = new G4Allocator<PMThit>;
  }
  return pmthitAllocat->MallocSingle();
}

inline void PMThit::operator delete(void *aHit)
{
    if (!pmthitAllocat)
    {
        pmthitAllocat = new G4Allocator<PMThit>;
    }
    pmthitAllocat->FreeSingle((PMThit*) aHit);
}

#endif