#include <G4tgrVolumeMgr.hh>
#include <G4tgrFileReader.hh>
#include <G4tgbVolumeMgr.hh>

#include "TextDetectorBuilder.hh"
const G4tgrVolume * TextDetectorBuilder::ReadDetector()
{
   G4tgrFileReader* fileReader = G4tgrFileReader::GetInstance();
   fileReader->SetLineProcessor(fLineProcessor);
   fileReader->ReadFiles();
   G4tgrVolumeMgr* mgr = G4tgrVolumeMgr::GetInstance();
   const G4tgrVolume* world = mgr->GetTopVolume();
   return world;
}
//______________________________________________________________________________
//
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>
G4VPhysicalVolume* TextDetectorBuilder::ConstructDetector(
      const G4tgrVolume* topVol)
{
   G4VPhysicalVolume *world = G4tgbDetectorBuilder::ConstructDetector(topVol);

   G4tgbVolumeMgr* tgbVolmgr = G4tgbVolumeMgr::GetInstance();
   BorderSurface* border = fLineProcessor->Border;
   while (border) {
      G4String physV1 = border->v1.substr(0,border->v1.find(":"));
      G4String physV2 = border->v2.substr(0,border->v2.find(":"));
      int copyNo1 = atoi(border->v1.substr(border->v1.find(":")+1).data());
      int copyNo2 = atoi(border->v2.substr(border->v2.find(":")+1).data());
      G4LogicalVolume *m1=tgbVolmgr->FindG4PhysVol(physV1)->GetMotherLogical();
      G4LogicalVolume *m2=tgbVolmgr->FindG4PhysVol(physV2)->GetMotherLogical();
      // search for phyiscs volumes on the sides of the border
      G4VPhysicalVolume *v1=0, *v2=0;
      for (int i=0; i<m1->GetNoDaughters(); i++) {
         v1 = m1->GetDaughter(i);
         if (v1->GetCopyNo()==copyNo1) break;
      }
      if(physV2=="world")
      v2 = tgbVolmgr->FindG4PhysVol(physV2);
      else{
            for (int i=0; i<m2->GetNoDaughters(); i++) {
                  v2 = m2->GetDaughter(i);
                  if (v2->GetCopyNo()==copyNo2) break;
      }
      }
      
      if (v1 && v2) {
         new G4LogicalBorderSurface(border->name,v1,v2,border->optic);
         // for my project
         new G4LogicalSkinSurface(border->name,m1,border->optic);
         G4cout<<"Border surface "<<border->name<<" in between "
            <<physV1<<":"<<copyNo1<<" and "<<physV2<<":"<<copyNo2
            <<" added"<<G4endl;
      }
      border=border->next;
   }
   return world;
}

