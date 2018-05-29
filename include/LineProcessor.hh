#include <G4OpticalSurface.hh>
/**
 * A link list of G4LogicalBorderSurface.
 * It is used to save information provided by the :surf tag in the text
 * geometry description, for constructing a G4LogicalBorderSurface later.
 */
struct BorderSurface
{
   G4String name; ///< name of the surface
   G4String v1;   ///< name of volume 1
   G4String v2;   ///< name of volume 2
   G4OpticalSurface* optic; ///< point to G4OpticalSurface object
   BorderSurface* next; ///< link to next border surface
}; 
//______________________________________________________________________________
//
#include <G4tgrLineProcessor.hh>
#include <G4MaterialPropertiesTable.hh>
/**
 * Extension to default text geometry file line processor.
 */
class LineProcessor: public G4tgrLineProcessor
{
   public:
      LineProcessor(): G4tgrLineProcessor(), Border(0) {};
      ~LineProcessor();
      /**
       * Overwrite G4tgrLineProcessor::ProcessLine to add new tags.
       * Two new tags are added: ":PROP" and ":SURF".
       */
      G4bool ProcessLine(const std::vector<G4String, std::allocator<G4String> > &words);

      BorderSurface* Border; ///< pointer to a BorderSurface object

   private:
      G4MaterialPropertiesTable* CreateMaterialPropertiesTable(
            const std::vector<G4String> &words, size_t idxOfWords);
};
