// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Custom Includes.
#include "SlateSlice.h"

// UE Includes.
#include "Components/Widget.h"
#include "Components/Button.h"
#include "SliceWidget.generated.h"

UCLASS()
class FF_CHARTS_API USliceWidget : public UWidget
{
	GENERATED_BODY()

public:

	virtual void SynchronizeProperties() override;
	
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (ClampMin = "0", ClampMax = "360"))
	double Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (ClampMin = "0", ClampMax = "360"))
	double ArcSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	FColor SecondaryColor = FColor::White;
	
	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetAngle(double InAngle);

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetArcSize(double InArcSize);

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	TSharedPtr<SSlateSlice> MySlice;
	
};