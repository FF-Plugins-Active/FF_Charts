// Copyright Epic Games, Inc. All Rights Reserved.

#include "FF_ChartsBPLibrary.h"
#include "FF_Charts.h"

UFF_ChartsBPLibrary::UFF_ChartsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UFF_ChartsBPLibrary::Int32ToGraphics(EGraphicsType GraphicsType, int32 TargetInteger, int32 FullInteger, double& Scale, double& UnitValue)
{
    int32 FullScale = 0;

    switch (GraphicsType)
    {
        case EGraphicsType::ChartPie:
            FullScale = 360;
            break;
        
        case EGraphicsType::ChartBar:
            FullScale = 100;
            break;
    }

    Scale = (static_cast<double>(TargetInteger) * FullScale) / FullInteger;

    UnitValue = Scale / FullScale;
}