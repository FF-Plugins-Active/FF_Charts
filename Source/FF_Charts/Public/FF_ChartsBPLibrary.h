// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

// Custom Includes
#include "FF_Charts_Enums.h"

#include "FF_ChartsBPLibrary.generated.h"

UCLASS()
class UFF_ChartsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Int32 To Graphics", ToolTip = "Unit Value gives scale as a float between 0 and 1.", Keywords = "int32, graphics, pie"), Category = "FF_Charts")
	static FF_CHARTS_API void Int32ToGraphics(EGraphicsType GraphicsType, int32 TargetInteger, int32 FullInteger, double& Scale, double& UnitValue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Detect Pie", ToolTip = "", Keywords = "graphics, pie"), Category = "FF_Charts")
	static FF_CHARTS_API bool DetectPie(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, double ArcSize, double ArcAngle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Detect Pie Recursive", ToolTip = "", Keywords = "graphics, pie, recursive"), Category = "FF_Charts")
	static FF_CHARTS_API bool DetectPieRecursive(int32& Out_Index, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TMap<double, double> Pies);

};