/**
 * @file muonMaterial.hh
 * @brief 构建材料
 * @author loyxin
 * @version 1.0
 * @date 2017-09-10
 */
#ifndef MUONMATERIAL_HH 
#define MUONMATERIAL_HH 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
/**
 * @brief 构建材料
 */
class muonMaterial{
public:
    /**
     * @brief 默认 construction 函数并初始化 fNistMan
     */
    muonMaterial();
    ~muonMaterial();
    static muonMaterial* GetInstance();
    /**
     * @brief 根据名字找到 nist 下的材料
     */
    G4Material* GetMaterial(const G4String);
    /**
     * @brief 得到 detector 的材料
     * @return detector 的材料
     */
    G4Material* Getfdetector(){return fdetector;}
    /**
     * @brief 得到 PMT 的材料
     * @return PMT 的材料
     */
    G4Material* GetfPMT(){return fPMT;}
    /**
     * @brief 得到 reflect 的材料
     * @return  reflect 的材料
     */
    G4Material* Getfreflect(){return freflect;}
    /**
     * @brief 得到 world 的材料-空气
     * @return world 的材料
     */
    G4Material* GetfAir(){return fAir;}
    
    G4Material* GetfPMMA(){return fPMMA;}
private:  
    // 构建材料
    /**
     * @brief 构建材料
     * @details 初始化 fdetector fPMT freflect fAir
     */
    void CreateMaterials();

private:

    static muonMaterial* fInstance;

    G4NistManager*     fNistMan;

    G4Material*        fdetector;
    G4Material*        fPMT;
    G4Material*        freflect;
    G4Material*        fAir;
    G4Material*        fPMMA;
};


#endif