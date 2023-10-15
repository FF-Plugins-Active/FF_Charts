// Fill out your copyright notice in the Description page of Project Settings.

#include "SlatePolygon.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlatePolygon::Construct(const FArguments& InArgs)
{
	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
	Locations = InArgs._Locations;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SSlatePolygon::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	return LayerId;
}

void SSlatePolygon::SetBrush(FSlateBrush* InBrush)
{
	Brush.SetImage(*this, InBrush);
}

void SSlatePolygon::SetLocations(TArray<FVector2D> In_Locations)
{
	Locations = In_Locations;
}