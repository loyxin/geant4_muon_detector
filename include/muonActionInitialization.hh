// 作用：总体初始化相应的 action 类
// 调用 muonPrimaryGeneratorAction 类
#ifndef MUONACTIONINITIALIZATION_HH
#define MUONACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class muonActionInitialization : public G4VUserActionInitialization
{
  public:
    // 默认 construction 函数
    muonActionInitialization();
    virtual ~muonActionInitialization();

    // 多线程 build
    virtual void BuildForMaster() const override;
    // 单线程 build
    // 效果:初始化 muonPrimaryGeneratorAction
    // 作用：见.hh文件
    virtual void Build() const override;
};

#endif
