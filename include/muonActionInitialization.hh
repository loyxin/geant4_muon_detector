/**
 * @file muonActionInitialization.hh
 * @brief 总体 action 类的注册
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef MUONACTIONINITIALIZATION_HH
#define MUONACTIONINITIALIZATION_HH

#include <G4VUserActionInitialization.hh>
/**
 * @brief action 类的注册
 */
class muonActionInitialization : public G4VUserActionInitialization
{
  public:
    // 
    /**
     * @brief 默认 construction 函数
     * @details [long description]
     */
    muonActionInitialization();
    virtual ~muonActionInitialization();


    /**
     * @brief 多线程 build 暂时没有用
     */
    virtual void BuildForMaster() const override;
    /**
     * @brief 单线程 build
     * @details 初始化 muonPrimaryGeneratorAction, runAction,eventAction,SteppingAction
     */

    virtual void Build() const override;
};

#endif
