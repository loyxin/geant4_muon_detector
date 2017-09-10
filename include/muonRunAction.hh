/**
 * @file muonRunAction.hh
 * @brief 设置 run action 打开文件，并设置文件的参数 
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef MUONRUNACTION_HH
#define MUONRUNACTION_HH

#include <G4UserRunAction.hh>
#include <G4Run.hh>
#include <G4ParticleDefinition.hh>


class G4Run;
/**
  * @brief 打开文件，并设置文件的参数 
  */
class muonRunAction : public G4UserRunAction
{
  public:
  	/**
  	 * @brief 打开 muon_nt_detector.csv muon_nt_pmt.csv 文件，并设置文件的参数 
  	 * @details muon_nt_pmt id = 1 muon_nt_detector id = 2
  	 */
    muonRunAction();
    /**
     * @brief 写入数据，关闭文件
     */
    virtual ~muonRunAction();
    /**
     * @brief 打印已运行多少个 event
     */
    virtual void EndOfRunAction(const G4Run* run);

};

#endif
