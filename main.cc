/**
 * @file main.cc
 * @author loyxin
 * @brief  main file 可视化，三个强制类的新建
 * @details 
 * 可视化，如果遇到 -i 参数，都会弹出可视化界面
 * 直接调用程序默认弹出可视化界面
 * 如果有宏文件，则不弹出可视化界面，并执行宏文件命令
 * 新建三个强制类，并交给 runManager 管理
 * @version 1.0
 * @date 2017-09-10
 */

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4ScoringManager.hh>
#include <G4String.hh>
#include <G4VUserPhysicsList.hh>

#ifdef G4VIS_USE
    #include <G4VisExecutive.hh>
#endif

#ifdef G4UI_USE
    #include <G4UIExecutive.hh>
#endif

#include <Randomize.hh>
#include <vector>

#include "Analysis.hh"
#include "muonDetectorConstruction.hh"
#include "muonActionInitialization.hh"
#include "muonPhysicsList.hh"
#include "Physics.hh"

using namespace std;

int main(int argc,char** argv)
{

  vector<G4String> macros;
  bool interactive = false;


  if  (argc == 1)
    {
    // 可视化交互 default
      interactive = true;
    }
  else
    {
    for (int i = 1; i < argc; i++)
      {
        G4String arg = argv[i];
        // 启用 参数 -i 可视化交互
        if (arg == "-i" || arg == "--interactive")
        {
          interactive = true;
          continue;
        }
        else
        {
          // macro 存储宏文件名字
          macros.push_back(arg);
        }
      }
    }


  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager();
  runManager->SetVerboseLevel(1);

  // Set mandatory initialization classes
  // Detector construction
  runManager->SetUserInitialization(new muonDetectorConstruction() );

  // Physics list
   G4String physName = "QGSP_BERT_HP";
  // G4VModularPhysicsList* physicsList = new QBBC;
  G4VUserPhysicsList* muonPhy = new muonPhysicsList(physName);
  // G4VUserPhysicsList* muonPhy = new Physics();

  runManager->SetUserInitialization(muonPhy);
  muonPhy->SetVerboseLevel(1);

  //Action initialization
  runManager->SetUserInitialization(new muonActionInitialization());
  #ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive("quiet");
    visManager->SetVerboseLevel(0);
    visManager->Initialize();
  #endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  #ifdef G4UI_USE
    G4UIExecutive* ui;
    if (interactive)
      {
        ui = new G4UIExecutive(argc, argv);
      }
  #endif

  // batch mode
  for (auto macro : macros)
    {
      G4String command = "/control/execute ";
      UImanager->ApplyCommand(command + macro);
    }

    // 默认可视化设置
  #ifdef G4UI_USE
    if (interactive)
      {
        UImanager->ApplyCommand("/control/execute macro/init_vis.mac");
        ui->SessionStart();
        delete ui;
      }
  #endif

  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->CloseFile();

  delete visManager;
  delete runManager;

  std::cout << "Application successfully ended.\nBye :-)" << std::endl;
  return 0;
}
