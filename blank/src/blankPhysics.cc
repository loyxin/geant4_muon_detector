
#include "blankPhysics.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

blankPhysics::blankPhysics() : G4VUserPhysicsList()
{

    SetCuts();
}
blankPhysics::~blankPhysics(){

}
#include "G4ShortLivedConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
void blankPhysics::ConstructParticle()
{
    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();

    // gamma
    G4Gamma::GammaDefinition();

    //OpticalPhotons
    G4OpticalPhoton::OpticalPhotonDefinition();

    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();

    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();

    //  mesons
    G4MesonConstructor mConstructor;
    mConstructor.ConstructParticle();

    //  baryons
    G4BaryonConstructor bConstructor;
    bConstructor.ConstructParticle();

    //  ions
    G4IonConstructor iConstructor;
    iConstructor.ConstructParticle();

    G4ShortLivedConstructor slConstructor;
    slConstructor.ConstructParticle();

}

void blankPhysics::ConstructProcess()
{

    AddTransportation();

    ConstructEM();

    ConstructOp();

}

// Electromagnetic Processes ////////////////////////////////////////////////
// all charged particles

// gamma
#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4ComptonScattering.hh"
#include "G4LivermoreComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4LivermoreGammaConversionModel.hh"

#include "G4RayleighScattering.hh"
#include "G4LivermoreRayleighModel.hh"


// e-
#include "G4eMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4LivermoreIonisationModel.hh"

#include "G4eBremsstrahlung.hh"
#include "G4LivermoreBremsstrahlungModel.hh"


// e+
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"


// alpha and GenericIon and deuterons, triton, He3:

//muon:
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCapture.hh"

//OTHERS:
#include "G4hIonisation.hh"
#include "G4hMultipleScattering.hh"
#include "G4hBremsstrahlung.hh"
#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"

//em process options to allow msc step-limitation to be switched off
#include "G4EmParameters.hh"
#include "G4VAtomDeexcitation.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4LossTableManager.hh"

void blankPhysics::ConstructEM() {

    //set a finer grid of the physic tables in order to improve precision
    //former LowEnergy models have 200 bins up to 100 GeV
    G4EmParameters* param = G4EmParameters::Instance();
    param->SetMaxEnergy(100*GeV);
    param->SetNumberOfBinsPerDecade(20);
    param->SetMscStepLimitType(fMinimal);
    param->SetFluo(true);
    param->SetPixe(true);
    param->SetAuger(true);
    G4LossTableManager* man = G4LossTableManager::Instance();
    G4VAtomDeexcitation* ad = man->AtomDeexcitation();
    if(!ad) {
        man->SetAtomDeexcitation(new G4UAtomicDeexcitation());
    }

    auto particleIterator=GetParticleIterator();
    particleIterator->reset();
    while( (*particleIterator)() ){
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        G4String particleType = particle->GetParticleType();
        G4double charge = particle->GetPDGCharge();

        if (particleName == "gamma")
        {
            //gamma
            G4RayleighScattering* theRayleigh = new G4RayleighScattering();
            pmanager->AddDiscreteProcess(theRayleigh);

            G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
            thePhotoElectricEffect->SetEmModel(new G4LivermorePhotoElectricModel());
            pmanager->AddDiscreteProcess(thePhotoElectricEffect);

            G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
            theComptonScattering->SetEmModel(new G4LivermoreComptonModel());
            pmanager->AddDiscreteProcess(theComptonScattering);

            G4GammaConversion* theGammaConversion = new G4GammaConversion();
            theGammaConversion->SetEmModel(new G4LivermoreGammaConversionModel());
            pmanager->AddDiscreteProcess(theGammaConversion);

        }
        else if (particleName == "e-")
        {
            //electron
            // process ordering: AddProcess(name, at rest, along step, post step)
            // Multiple scattering
            G4eMultipleScattering* msc = new G4eMultipleScattering();
            msc->SetStepLimitType(fUseDistanceToBoundary);
            pmanager->AddProcess(msc,-1, 1, -1);

            // Ionisation
            G4eIonisation* eIonisation = new G4eIonisation();
            eIonisation->SetEmModel(new G4LivermoreIonisationModel());
            eIonisation->SetStepFunction(0.2, 100*um); //improved precision in tracking
            pmanager->AddProcess(eIonisation,-1, 2, 2);

            // Bremsstrahlung
            G4eBremsstrahlung* eBremsstrahlung = new G4eBremsstrahlung();
            eBremsstrahlung->SetEmModel(new G4LivermoreBremsstrahlungModel());
            pmanager->AddProcess(eBremsstrahlung, -1,-3, 3);
        }
        else if (particleName == "e+")
        {
            //positron
            G4eMultipleScattering* msc = new G4eMultipleScattering();
            msc->SetStepLimitType(fUseDistanceToBoundary);
            pmanager->AddProcess(msc,-1, 1, 1);

            // Ionisation
            G4eIonisation* eIonisation = new G4eIonisation();
            eIonisation->SetStepFunction(0.2, 100*um); //
            pmanager->AddProcess(eIonisation,                 -1, 2, 2);

            //Bremsstrahlung (use default, no low-energy available)
            pmanager->AddProcess(new G4eBremsstrahlung(), -1,-1, 3);

            //Annihilation
            pmanager->AddProcess(new G4eplusAnnihilation(),0,-1, 4);
        }
        else if( particleName == "mu+" ||
                 particleName == "mu-"    )
        {
            //muon
            pmanager->AddProcess(new G4eMultipleScattering,           -1, 1, 1);
            pmanager->AddProcess(new G4MuIonisation(),          -1, 2, 2);
            pmanager->AddProcess(new G4MuBremsstrahlung(),      -1,-1, 3);
            pmanager->AddProcess(new G4MuPairProduction(),      -1,-1, 4);
            if( particleName == "mu-" )
                pmanager->AddProcess(new G4MuonMinusCapture(), 0,-1,-1);
        }
        else if (particleName == "proton" ||
                 particleName == "pi+" ||
                 particleName == "pi-")
        {
            //multiple scattering
            pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);

            //ionisation
            G4hIonisation* hIonisation = new G4hIonisation();
            hIonisation->SetStepFunction(0.2, 50*um);
            pmanager->AddProcess(hIonisation,                     -1, 2, 2);

            //bremmstrahlung
            pmanager->AddProcess(new G4hBremsstrahlung,     -1,-3, 3);
        }
        else if(particleName == "alpha"      ||
                particleName == "deuteron"   ||
                particleName == "triton"     ||
                particleName == "He3")
        {
            //multiple scattering
            pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);

            //ionisation
            G4ionIonisation* ionIoni = new G4ionIonisation();
            ionIoni->SetStepFunction(0.1, 20*um);
            pmanager->AddProcess(ionIoni,                   -1, 2, 2);
        }
        else if (particleName == "GenericIon")
        {
            // OBJECT may be dynamically created as either a GenericIon or nucleus
            // G4Nucleus exists and therefore has particle type nucleus
            // genericIon:

            //multiple scattering
            pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);

            //ionisation
            G4ionIonisation* ionIoni = new G4ionIonisation();
            ionIoni->SetEmModel(new G4IonParametrisedLossModel());
            ionIoni->SetStepFunction(0.1, 20*um);
            pmanager->AddProcess(ionIoni,                   -1, 2, 2);
        }

        else if ((!particle->IsShortLived()) &&
                 (charge != 0.0) &&
                 (particle->GetParticleName() != "chargedgeantino"))
        {
            //all others charged particles except geantino
            G4hMultipleScattering* aMultipleScattering = new G4hMultipleScattering();
            G4hIonisation* ahadronIon = new G4hIonisation();

            //multiple scattering
            pmanager->AddProcess(aMultipleScattering,-1,1,1);

            //ionisation
            pmanager->AddProcess(ahadronIon,       -1,2,2);
        }

    }
}


// Optical Processes ////////////////////////////////////////////////////////
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"

#include "G4OpBoundaryProcess.hh"

void blankPhysics::ConstructOp()
{
    // default scintillation process
    G4Scintillation* theScintProcessDef = new G4Scintillation("Scintillation");
    // theScintProcessDef->DumpPhysicsTable();
    theScintProcessDef->SetTrackSecondariesFirst(true);
    theScintProcessDef->SetScintillationYieldFactor(1.0); //
    theScintProcessDef->SetScintillationExcitationRatio(0.0); //
    int OpVerbLevel =0;
    theScintProcessDef->SetVerboseLevel(OpVerbLevel);

    // scintillation process for alpha:
    G4Scintillation* theScintProcessAlpha = new G4Scintillation("Scintillation");
    // theScintProcessNuc->DumpPhysicsTable();
    theScintProcessAlpha->SetTrackSecondariesFirst(true);
    theScintProcessAlpha->SetScintillationYieldFactor(1.1);
    theScintProcessAlpha->SetScintillationExcitationRatio(1.0);
    theScintProcessAlpha->SetVerboseLevel(OpVerbLevel);

    // scintillation process for heavy nuclei
    G4Scintillation* theScintProcessNuc = new G4Scintillation("Scintillation");
    // theScintProcessNuc->DumpPhysicsTable();
    theScintProcessNuc->SetTrackSecondariesFirst(true);
    theScintProcessNuc->SetScintillationYieldFactor(0.2);
    theScintProcessNuc->SetScintillationExcitationRatio(1.0);
    theScintProcessNuc->SetVerboseLevel(OpVerbLevel);

    // optical processes
    G4OpAbsorption* theAbsorptionProcess = new G4OpAbsorption();
    //  G4OpRayleigh* theRayleighScatteringProcess = new G4OpRayleigh();
    G4OpBoundaryProcess* theBoundaryProcess = new G4OpBoundaryProcess();
    //  theAbsorptionProcess->DumpPhysicsTable();
    //  theRayleighScatteringProcess->DumpPhysicsTable();
    theAbsorptionProcess->SetVerboseLevel(OpVerbLevel);
    // theRayleighScatteringProcess->SetVerboseLevel(OpVerbLevel);
    theBoundaryProcess->SetVerboseLevel(OpVerbLevel);

    auto particleIterator=GetParticleIterator();
    particleIterator->reset();
    while( (*particleIterator)() )
    {
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        if (theScintProcessDef->IsApplicable(*particle)) {
            //      if(particle->GetPDGMass() > 5.0*GeV)
            if(particle->GetParticleName() == "GenericIon") {
                pmanager->AddProcess(theScintProcessNuc); // AtRestDiscrete
                pmanager->SetProcessOrderingToLast(theScintProcessNuc,idxAtRest);
                pmanager->SetProcessOrderingToLast(theScintProcessNuc,idxPostStep);
            }
            else if(particle->GetParticleName() == "alpha") {
                pmanager->AddProcess(theScintProcessAlpha);
                pmanager->SetProcessOrderingToLast(theScintProcessAlpha,idxAtRest);
                pmanager->SetProcessOrderingToLast(theScintProcessAlpha,idxPostStep);
            }
            else {
                pmanager->AddProcess(theScintProcessDef);
                pmanager->SetProcessOrderingToLast(theScintProcessDef,idxAtRest);
                pmanager->SetProcessOrderingToLast(theScintProcessDef,idxPostStep);
            }
        }

        if (particleName == "opticalphoton") {
            pmanager->AddDiscreteProcess(theAbsorptionProcess);
            //	pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
            pmanager->AddDiscreteProcess(theBoundaryProcess);
        }
    }
}