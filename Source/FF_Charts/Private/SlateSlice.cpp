// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateSlice.h"
#include "SlateOptMacros.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Input/HittestGrid.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlateSlice::Construct(const FArguments& InArgs)
{
	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
	Angle = FMath::Clamp(InArgs._Angle, 0, 360);
	ArcSize = FMath::Clamp(InArgs._ArcSize, 0, 360);
	SecondaryColor = InArgs._SecondaryColor;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SSlateSlice::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	const FVector2D CursorPos = MouseEvent.GetScreenSpacePosition();
	const FVector2D Size = MyGeometry.GetAbsoluteSize();
	const FVector2D Center = MyGeometry.GetAbsolutePosition() + 0.5 * Size;
	const double Radius = FMath::Min(Size.X, Size.Y) * 0.5f;
	const double CursorDistance = UKismetMathLibrary::Distance2D(CursorPos, Center);

	if (CursorDistance > Radius)
	{
		return FReply::Unhandled();
	}

	const FVector2D Fixed_CursorPos = FVector2D(CursorPos.X, MyGeometry.GetRenderBoundingRect().GetBottomLeft2f().Y - CursorPos.Y);
	const FVector2D Fixed_Center = FVector2D(Center.X, MyGeometry.GetRenderBoundingRect().GetBottomLeft2f().Y - Center.Y);
	const double Yaw = -1 * UKismetMathLibrary::FindLookAtRotation(FVector(Fixed_Center.X, Fixed_Center.Y, double(0)), FVector(Fixed_CursorPos.X, Fixed_CursorPos.Y, double(0))).Yaw;
	double Angle_Cursor = Yaw >= 0 ? Angle_Cursor = Yaw : Angle_Cursor = 360 + Yaw;
	
	const double Angle_Space = 360 - ArcSize;
	const double Difference = Angle - Angle_Space;

	double Range_Min = 0;
	double Range_Max = 0;
	if (Difference < 0)
	{
		Range_Min = Angle;
		Range_Max = 360 + Difference;

		if (FMath::IsWithin(Angle_Cursor, Range_Min, Range_Max))
		{
			const FWidgetStyle TintStyle;
			GEngine->AddOnScreenDebugMessage(-1, 10, Brush.Get()->GetTint(TintStyle).ToFColor(false), FString::SanitizeFloat(Angle_Cursor));
			return FReply::Handled();
		}

		else
		{
			return FReply::Unhandled();
		}
	}

	else
	{
		Range_Min = Difference;
		Range_Max = Angle;

		if (!FMath::IsWithin(Angle_Cursor, Range_Min, Range_Max))
		{
			const FWidgetStyle TintStyle;
			GEngine->AddOnScreenDebugMessage(-1, 10, Brush.Get()->GetTint(TintStyle).ToFColor(false), FString::SanitizeFloat(Angle_Cursor));
			return FReply::Handled();
		}

		else
		{
			return FReply::Unhandled();
		}
	}
}

int32 SSlateSlice::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	auto CalculateUV = [](const FVector2D& Point, const FVector2D& Center, double Radius) -> FVector2D
		{
			// Normalize direction
			FVector2D Direction = (Point - Center) / Radius;
			
			float U = 0.5f + Direction.X * 0.5f;
			float V = 0.5f + Direction.Y * 0.5f;
			
			return FVector2D(U, V);
		};

	const FVector2D Pos = AllottedGeometry.GetAbsolutePosition();
	const FVector2D Size = AllottedGeometry.GetAbsoluteSize();
	const FVector2D Center = Pos + 0.5 * Size;
	const double Radius = FMath::Min(Size.X, Size.Y) * 0.5f;

	const FSlateBrush* SlateBrush = Brush.GetImage().Get();
	FLinearColor LinearColor = InWidgetStyle.GetColorAndOpacityTint() * SlateBrush->GetTint(InWidgetStyle);
	FColor FinalColorAndOpacity = LinearColor.ToFColor(true);

	const int32 NumSegments = FMath::RoundToInt(ArcSize / 2.0f);
	TArray<FSlateVertex> Vertices;
	Vertices.Reserve(NumSegments + 3);

	// Add center vertex
	Vertices.AddZeroed();
	FSlateVertex& CenterVertex = Vertices.Last();
	CenterVertex.Position = (FVector2f)(Center);
	CenterVertex.Color = FinalColorAndOpacity;
	CenterVertex.SecondaryColor = SecondaryColor;
	CenterVertex.TexCoords[0] = CalculateUV(Center, Center, Radius).X;
	CenterVertex.TexCoords[1] = CalculateUV(Center, Center, Radius).Y;

	// Add edge vertices
	for (int i = 0; i < NumSegments + 2; ++i)
	{
		const double CurrentAngle = FMath::DegreesToRadians(ArcSize * i / NumSegments + Angle);
		const FVector2D EdgeDirection(FMath::Cos(CurrentAngle), FMath::Sin(CurrentAngle));
		const FVector2D OuterEdge(Radius * EdgeDirection);
		const FVector2D EndPoint = (FVector2D)(Center + OuterEdge);

		Vertices.AddZeroed();
		FSlateVertex& OuterVert = Vertices.Last();
		OuterVert.Position = (FVector2f)(EndPoint);
		OuterVert.Color = FinalColorAndOpacity;
		OuterVert.SecondaryColor = SecondaryColor;
		OuterVert.TexCoords[0] = CalculateUV(EndPoint, Center, Radius).X;
		OuterVert.TexCoords[1] = CalculateUV(EndPoint, Center, Radius).Y;
	}

	TArray<SlateIndex> Indices;
	for (int i = 0; i <= NumSegments; ++i)
	{
		Indices.Add(0);
		Indices.Add(i);
		Indices.Add(i + 1);
	}

	const FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(*SlateBrush);
	FSlateDrawElement::MakeCustomVerts(OutDrawElements, LayerId, Handle, Vertices, Indices, nullptr, 0, 0, ESlateDrawEffect::PreMultipliedAlpha);
	FHittestGrid& PreviousGrid = Args.GetHittestGrid();

	return LayerId;
}

void SSlateSlice::SetBrush(FSlateBrush* InBrush)
{
	Brush.SetImage(*this, InBrush);
}

void SSlateSlice::SetAngle(double InAngle)
{
	Angle = FMath::Clamp(InAngle, 0, 360);
}

void SSlateSlice::SetArcSize(double InArcSize)
{
	ArcSize = FMath::Clamp(InArcSize, 0, 360);
}

void SSlateSlice::SetSecondaryColor(FColor InSecondaryColor)
{
	SecondaryColor = InSecondaryColor;
}