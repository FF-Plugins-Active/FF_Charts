// Copyright Epic Games, Inc. All Rights Reserved.

#include "FF_ChartsBPLibrary.h"
#include "FF_Charts.h"

#include "Kismet/KismetMathLibrary.h"

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

bool UFF_ChartsBPLibrary::DetectPie(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, double ArcSize, double ArcAngle)
{
	const FVector2D CursorPos = MouseEvent.GetScreenSpacePosition();
	const FVector2D Size = MyGeometry.GetAbsoluteSize();
	const FVector2D Center = MyGeometry.GetAbsolutePosition() + 0.5 * Size;
	const double Radius = FMath::Min(Size.X, Size.Y) * 0.5f;
	const double CursorDistance = UKismetMathLibrary::Distance2D(CursorPos, Center);

	if (CursorDistance > Radius)
	{
		return false;
	}

	const FVector2D Fixed_CursorPos = FVector2D(CursorPos.X, MyGeometry.GetRenderBoundingRect().GetBottomLeft2f().Y - CursorPos.Y);
	const FVector2D Fixed_Center = FVector2D(Center.X, MyGeometry.GetRenderBoundingRect().GetBottomLeft2f().Y - Center.Y);
	const double Yaw = -1 * UKismetMathLibrary::FindLookAtRotation(FVector(Fixed_Center.X, Fixed_Center.Y, double(0)), FVector(Fixed_CursorPos.X, Fixed_CursorPos.Y, double(0))).Yaw;
	double Angle_Cursor = Yaw >= 0 ? Yaw : 360 + Yaw;
	const double Difference = ArcAngle - (360 - ArcSize);

	double Range_Min = 0;
	double Range_Max = 0;
	
	if (Difference < 0)
	{
		Range_Min = ArcAngle;
		Range_Max = 360 + Difference;

		if (FMath::IsWithin(Angle_Cursor, Range_Min, Range_Max))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		Range_Min = Difference;
		Range_Max = ArcAngle;

		if (!FMath::IsWithin(Angle_Cursor, Range_Min, Range_Max))
		{
			return true;
		}

		else
		{
			return false;
		}
	}
}

bool UFF_ChartsBPLibrary::DetectPieRecursive(USliceWidget*& Out_Widget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TArray<FPieStruct> Pies)
{
	bool bRetVal = false;

	for (FPieStruct EachPie : Pies)
	{
		if (UFF_ChartsBPLibrary::DetectPie(MyGeometry, MouseEvent, EachPie.ArcSize, EachPie.ArcAngle))
		{
			bRetVal = true;
			Out_Widget = EachPie.TargetWidget;
		}
	}

	return bRetVal;
}