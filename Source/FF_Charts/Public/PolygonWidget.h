// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Custom Includes.
#include "SlatePolygon.h"

// UE Includes.
#include "Components/Widget.h"

#include "PolygonWidget.generated.h"

UCLASS()
class FF_CHARTS_API UPolygonWidget : public UWidget
{
	GENERATED_BODY()

public:

	virtual void SynchronizeProperties() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	TArray<FVector2D> Locations;

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetLocations(TArray<FVector2D> InAngle);

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

	TSharedPtr<SSlatePolygon> MyPolygon;

};