// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FF_CHARTS_API SSlatePolygon : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SSlatePolygon)
		{}
		SLATE_ARGUMENT(FSlateBrush*, Brush)
		SLATE_ARGUMENT(TArray<FVector2D>, Locations)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	void SetBrush(FSlateBrush* InBrush);

	void SetLocations(TArray<FVector2D> In_Locations);


protected:

	FInvalidatableBrushAttribute Brush;

	TArray<FVector2D> Locations;

};