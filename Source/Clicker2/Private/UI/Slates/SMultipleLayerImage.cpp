// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI\Slates\SMultipleLayerImage.h"
#include "Rendering\DrawElements.h"
#if WITH_ACCESSIBILITY
#include "Widgets\Accessibility\SlateCoreAccessibleWidgets.h"
#endif


SLATE_IMPLEMENT_WIDGET(SMultipleLayerImage)

void SMultipleLayerImage::PrivateRegisterAttributes(FSlateAttributeInitializer& AttributeInitializer)
{
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION_WITH_NAME(AttributeInitializer, "Image", ImageAttribute,
	                                                EInvalidateWidgetReason::Layout);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION_WITH_NAME(AttributeInitializer, "ColorAndOpacity", ColorAndOpacityAttribute,
	                                                EInvalidateWidgetReason::Paint);
	SLATE_ADD_MEMBER_ATTRIBUTE_DEFINITION_WITH_NAME(AttributeInitializer, "DesiredSizeOverride",
	                                                DesiredSizeOverrideAttribute, EInvalidateWidgetReason::Layout);
}

SMultipleLayerImage::SMultipleLayerImage()
	: ImageAttribute(*this)
	  , ColorAndOpacityAttribute(*this)
	  , DesiredSizeOverrideAttribute(*this)
{
	SetCanTick(false);
	bCanSupportFocus = false;
}

void SMultipleLayerImage::Construct(const FArguments& InArgs)
{
	ImageAttribute.Assign(*this, InArgs._Image);
	ColorAndOpacityAttribute.Assign(*this, InArgs._ColorAndOpacity);
	bFlipForRightToLeftFlowDirection = InArgs._FlipForRightToLeftFlowDirection;
	Asset = InArgs._Asset;

	DesiredSizeOverrideAttribute.Assign(*this, InArgs._DesiredSizeOverride);

	SetOnMouseButtonDown(InArgs._OnMouseButtonDown);
}

int32 SMultipleLayerImage::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                   const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
                                   int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const UMultipleLayerImageAsset* asset = GetDefault<UMultipleLayerImageAsset>(Asset);


	for (const FSlateBrush& layer : asset->Layers)
	{
		const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);
		const ESlateDrawEffect DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		const FLinearColor FinalColorAndOpacity(
			InWidgetStyle.GetColorAndOpacityTint() * ColorAndOpacityAttribute.Get().GetColor(InWidgetStyle) * layer.
			GetTint(InWidgetStyle));

		if (bFlipForRightToLeftFlowDirection && GSlateFlowDirection == EFlowDirection::RightToLeft)
		{
			const FGeometry FlippedGeometry = AllottedGeometry.MakeChild(FSlateRenderTransform(FScale2D(-1, 1)));
			FSlateDrawElement::MakeBox(OutDrawElements, LayerId, FlippedGeometry.ToPaintGeometry(), &layer, DrawEffects,
			                           FinalColorAndOpacity);
		}
		else
		{
			FSlateDrawElement::MakeBox(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), &layer,
			                           DrawEffects, FinalColorAndOpacity);
		}
	}

	return LayerId;
}

FVector2D SMultipleLayerImage::ComputeDesiredSize(float) const
{
	const FSlateBrush* ImageBrush = ImageAttribute.Get();
	if (ImageBrush != nullptr)
	{
		const TOptional<FVector2D>& CurrentSizeOverride = DesiredSizeOverrideAttribute.Get();

		return CurrentSizeOverride.IsSet() ? CurrentSizeOverride.GetValue() : ImageBrush->ImageSize;
	}
	return FVector2D::ZeroVector;
}

void SMultipleLayerImage::SetColorAndOpacity(TAttribute<FSlateColor> InColorAndOpacity)
{
	ColorAndOpacityAttribute.Assign(*this, MoveTemp(InColorAndOpacity));
}

void SMultipleLayerImage::SetColorAndOpacity(FLinearColor InColorAndOpacity)
{
	ColorAndOpacityAttribute.Set(*this, InColorAndOpacity);
}

void SMultipleLayerImage::SetImage(TAttribute<const FSlateBrush*> InImage)
{
	ImageAttribute.Assign(*this, MoveTemp(InImage));
}

void SMultipleLayerImage::SetDesiredSizeOverride(TAttribute<TOptional<FVector2D>> InDesiredSizeOverride)
{
	DesiredSizeOverrideAttribute.Assign(*this, MoveTemp(InDesiredSizeOverride));
}

#if WITH_ACCESSIBILITY
TSharedRef<FSlateAccessibleWidget> SMultipleLayerImage::CreateAccessibleWidget()
{
	return MakeShareable<FSlateAccessibleWidget>(new FSlateAccessibleImage(SharedThis(this)));
}
#endif
