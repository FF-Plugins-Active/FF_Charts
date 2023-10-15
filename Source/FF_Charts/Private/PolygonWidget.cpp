// Fill out your copyright notice in the Description page of Project Settings.

#include "PolygonWidget.h"

#define LOCTEXT_NAMESPACE "UMG"

void UPolygonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	MyPolygon->SetBrush(&Brush);
	MyPolygon->SetLocations(Locations);
}

void UPolygonWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	MyPolygon.Reset();
}

void UPolygonWidget::SetLocations(TArray<FVector2D> In_Locations)
{
	Locations = In_Locations;
	if (MyPolygon)
	{
		MyPolygon->SetLocations(Locations);
	}
}

#if WITH_EDITOR
const FText UPolygonWidget::GetPaletteCategory()
{
	return LOCTEXT("CustomPaletteCategory", "My custom category!");
}
#endif

TSharedRef<SWidget> UPolygonWidget::RebuildWidget()
{
	MyPolygon = SNew(SSlatePolygon)
		.Brush(&Brush)
		.Locations(Locations);

	return MyPolygon.ToSharedRef();
}