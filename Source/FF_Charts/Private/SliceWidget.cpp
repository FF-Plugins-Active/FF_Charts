// Fill out your copyright notice in the Description page of Project Settings.

#include "SliceWidget.h"

#define LOCTEXT_NAMESPACE "UMG"

void USliceWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	MySlice->SetBrush(&Brush);
	MySlice->SetAngle(Angle);
	MySlice->SetArcSize(ArcSize);
}

void USliceWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	MySlice.Reset();
}

void USliceWidget::SetAngle(double InAngle)
{
	const double Temp_Angle = FMath::Clamp(InAngle, 0, 360);
	
	Angle = Temp_Angle;
	
	if (MySlice)
	{
		MySlice->SetAngle(Temp_Angle);
	}
}

void USliceWidget::SetArcSize(double InArcSize)
{
	const double Temp_ArcSize = FMath::Clamp(InArcSize, 0, 360);
	
	ArcSize = Temp_ArcSize;
	
	if (MySlice)
	{
		MySlice->SetArcSize(Temp_ArcSize);
	}
}

#if WITH_EDITOR
const FText USliceWidget::GetPaletteCategory()
{
	return LOCTEXT("CustomPaletteCategory", "My custom category!");
}
#endif

TSharedRef<SWidget> USliceWidget::RebuildWidget()
{
	MySlice = SNew(SSlateSlice)
		.Brush(&Brush)
		.Angle(FMath::Clamp(Angle, 0, 360))
		.ArcSize(FMath::Clamp(ArcSize, 0, 360))
		.SecondaryColor(SecondaryColor);
	
	return MySlice.ToSharedRef();
}