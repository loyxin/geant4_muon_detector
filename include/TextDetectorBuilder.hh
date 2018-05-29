/**
 * \file gears.C
 *
 * The only C++ file in this project.
 *
 * Everything is placed in one file intentionally to simplify management.
 */


#include <G4tgbDetectorBuilder.hh>
#include "LineProcessor.hh"
/**
 * Construct detector based on text geometry description.
 */
class TextDetectorBuilder : public G4tgbDetectorBuilder
{
   public :
      TextDetectorBuilder() { fLineProcessor = new LineProcessor(); }
      ~TextDetectorBuilder() { delete fLineProcessor; }
      const G4tgrVolume* ReadDetector(); ///< Read text geometry input
      /**
       * Construct detector based on text geometry description.
       */
      G4VPhysicalVolume* ConstructDetector(const G4tgrVolume* topVol);

   private :
      LineProcessor* fLineProcessor;
};
