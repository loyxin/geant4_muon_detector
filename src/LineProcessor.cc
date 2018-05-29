#include "LineProcessor.hh"
LineProcessor::~LineProcessor()
{
   while (Border) { // the G4OpticalSurface should be taken care by Geant4
      BorderSurface *next=Border->next;
      delete Border;
      Border=next;
   }
}
//______________________________________________________________________________
//
#include <G4UIcommand.hh>
#include <G4NistManager.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4LogicalVolume.hh>
#include <G4tgbMaterialMgr.hh>

G4bool LineProcessor::ProcessLine(const std::vector<G4String, std::allocator<G4String> > &words)
{
   // process default text geometry tags
   G4bool processed = G4tgrLineProcessor::ProcessLine(words);
   G4Material* mat;
   if (processed) return true;

   // process added tags
   G4String test;
   G4String tag = words[0];
   tag.toLower();
   if (tag.substr(0,5)==":prop") {
      G4NistManager* mgr = G4NistManager::Instance();
      G4cout<<"Set optical properties of "<<words[1]<<":"<<G4endl;
      mat =  mgr->FindOrBuildMaterial(words[1]);
      if(mat!=0) {
        mat->SetMaterialPropertiesTable(CreateMaterialPropertiesTable(words,2));
      }
      else{
        G4Material* sysumate = G4tgbMaterialMgr::GetInstance()->FindOrBuildG4Material( words[1] );
        sysumate->SetMaterialPropertiesTable(CreateMaterialPropertiesTable(words,2));
          }
      return true;
   } else if (tag.substr(0,5)==":surf") {
      BorderSurface *bdr = new BorderSurface;
      bdr->next=Border;
      Border=bdr;
      bdr->name=words[1];
      bdr->v1=words[2];
      bdr->v2=words[3];
      bdr->optic = new G4OpticalSurface(words[1]);
      size_t i=4; 
      // loop over optical surface setup lines
      while (i<words.size()) {
         G4String setting = words[i], value = words[i+1];
         setting.toLower(); value.toLower();
         if (setting=="property") {
            i++;
            break;
         } else if(setting=="type") {
            if (value=="dielectric_metal")
               bdr->optic->SetType(dielectric_metal);
            else if(value=="dielectric_dielectric")
               bdr->optic->SetType(dielectric_dielectric);
            else if(value=="firsov") bdr->optic->SetType(firsov);
            else if(value=="x_ray") bdr->optic->SetType(x_ray);
            else G4cout<<"Unknown surface type "<<value<<", ignored!"<<G4endl;
         } else if(setting=="model") {
            if (value=="glisur") bdr->optic->SetModel(glisur);
            else if(value=="unified") bdr->optic->SetModel(unified);
            else G4cout<<"Unknown surface model "<<value<<", ignored!"<<G4endl;
         } else if(setting=="finish") {
            if(value=="polished") bdr->optic->SetFinish(polished);
            else if(value=="polishedfrontpainted")
               bdr->optic->SetFinish(polishedfrontpainted);
            else if(value=="polishedbackpainted")
               bdr->optic->SetFinish(polishedbackpainted);
            else if(value=="ground") bdr->optic->SetFinish(ground);
            else if(value=="groundfrontpainted")
               bdr->optic->SetFinish(groundfrontpainted);
            else if(value=="groundbackpainted")
               bdr->optic->SetFinish(groundbackpainted);
            else
               G4cout<<"Unknown surface finish "<<value<<", ignored!"<<G4endl;
         } else if(setting=="sigma_alpha") {
            bdr->optic->SetSigmaAlpha(G4UIcommand::ConvertToInt(value));
         } else
            G4cout<<"Unknown surface setting "<<setting<<", ignored!"<<G4endl;
         i+=2;
      }
      if (i<words.size()) { // break while loop because of "property"
         G4cout<<"Set optical properties of "<<bdr->name<<":"<<G4endl;
         bdr->optic->SetMaterialPropertiesTable(
               CreateMaterialPropertiesTable(words,i));
      }
      return true;
   } else
      return false;
}
//______________________________________________________________________________
//
#include <G4tgrUtils.hh>
#include <G4MaterialPropertiesTable.hh>
G4MaterialPropertiesTable* LineProcessor::CreateMaterialPropertiesTable(
      const std::vector<G4String> &words, size_t idxOfWords)
{
   bool photonEnergyUnDefined=true;
   int cnt=0; // number of photon energy values
   double *energies; // photon energy values
   G4MaterialPropertiesTable *table = new G4MaterialPropertiesTable();
   for (size_t i=idxOfWords; i<words.size(); i++) {
      G4String property = words[i]; property.toUpper();
      if (property=="SCINTILLATIONYIELD" || property=="RESOLUTIONSCALE"
            || property=="FASTTIMECONSTANT" || property=="SLOWTIMECONSTANT"
            || property=="YIELDRATIO" || property=="WLSTIMECONSTANT") {
         table->AddConstProperty(property, G4tgrUtils::GetDouble(words[i+1]));
         G4cout<<property<<"="<<words[i+1]<<G4endl;
         i++; // property value has been used
      } else if (property.substr(0,12)=="PHOTON_ENERG") {
         photonEnergyUnDefined=false;
         cnt = G4UIcommand::ConvertToInt(words[i+1]); // get array size
         energies = new double[cnt]; // create energy array
         for (int j=0; j<cnt; j++)
            energies[j]=G4tgrUtils::GetDouble(words[i+2+j]);
         i=i+1+cnt; // array has been used
      } else { // wavelength-dependent properties
         if (photonEnergyUnDefined) {
            G4cout<<"photon energies undefined, "
               <<"ignore all wavelength-dependent properties!"<<G4endl;
            break;
         }
         double *values = new double[cnt];
         for (int j=0; j<cnt; j++) 
            values[j]=G4tgrUtils::GetDouble(words[i+1+j]);
         G4cout<<property<<"="<<values[0]<<", "<<values[1]<<"..."<<G4endl;
         table->AddProperty(property, energies, values, cnt);
         delete[] values;
         i=i+cnt;
      }
   }
   delete[] energies;
   return table;
}
