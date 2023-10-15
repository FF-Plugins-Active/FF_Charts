// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FF_CHARTS_API SSlateSlice : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SSlateSlice)
		{}
		SLATE_ARGUMENT(FSlateBrush*, Brush)
		SLATE_ARGUMENT(double, Angle)
		SLATE_ARGUMENT(double, ArcSize)
		SLATE_ARGUMENT(FColor, SecondaryColor)
	SLATE_END_ARGS()

	TSharedPtr<FHittestGrid> HittestGrid;

	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	void SetBrush(FSlateBrush* InBrush);

public:
	
	void SetAngle(double InAngle);
	
	void SetArcSize(double InArcSize);

	void SetSecondaryColor(FColor InSecondaryColor);

protected:

	FInvalidatableBrushAttribute Brush;
	
	FColor SecondaryColor = FColor::White;

	double Angle;
	
	double ArcSize;

};