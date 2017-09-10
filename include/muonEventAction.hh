/**
 * @file muonEventAction.hh
 * @brief 设置Event action 保存信息输出到 Ntuple
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef MUONEVENTACTION_HH
#define MUONEVENTACTION_HH

#include <G4UserEventAction.hh>
#include <globals.hh>

class muonRunAction;
/**
 * @brief 保存信息输出到 Ntuple
 */
class muonEventAction : public G4UserEventAction
{
	public:
		/**
		 * @brief 默认 construction 函数
		 */
		muonEventAction();
		virtual ~muonEventAction();
		/**
		 * @brief 保存信息到 Ntuple 中
		 * @details 保存 pmt hitcollection 和 muon detector hitcollection
		 * @param anEvent [description]
		 */
    	virtual void EndOfEventAction(const G4Event* anEvent) override;
	private:

		G4int muondetectorEnId { -1 };
    	G4int PMT_Id{-1};
};

#endif
