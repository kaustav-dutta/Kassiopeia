//
// Created by trost on 14.03.16.
//

#ifndef KASPER_KSGENENERGYRYDBERG_H
#define KASPER_KSGENENERGYRYDBERG_H

#include "KSGenCreator.h"
#include "KField.h"

namespace Kassiopeia
{
class KSGenEnergyRydberg:
    public KSComponentTemplate< KSGenEnergyRydberg, KSGenCreator >
{
public:
    KSGenEnergyRydberg();
    KSGenEnergyRydberg( const KSGenEnergyRydberg& aCopy );
    KSGenEnergyRydberg* Clone() const override;
    ~KSGenEnergyRydberg() override;

    //******
    //action
    //******

public:
    void Dice( KSParticleQueue* aPrimaries ) override;

private:
    ;K_SET_GET( double, DepositedEnergy );
    ;K_SET_GET( double, IonizationEnergy );

    //**********
    //initialize
    //**********

public:
    void InitializeComponent() override;
    void DeinitializeComponent() override;
};

}

#endif //KASPER_KSGENENERGYRYDBERG_H
