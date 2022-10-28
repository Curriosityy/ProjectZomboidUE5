// Fill out your copyright notice in the Description page of Project Settings.


#include "LineOfSightSystem\LineOfSightComponent.h"

#include "macros.h"
#include "Engine\Canvas.h"
#include "Engine\CanvasRenderTarget2D.h"
#include "Kismet\KismetMaterialLibrary.h"
#include "Kismet\KismetMathLibrary.h"
#include "Kismet\KismetRenderingLibrary.h"
#include "Materials\MaterialParameterCollection.h"
#include "Materials\MaterialParameterCollectionInstance.h"

// Sets default values for this component's properties
ULineOfSightComponent::ULineOfSightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SightLineDistance = 1000;
	SightAngle = 45;
	RaysCount = 90;
	ShouldTick = true;
	// ...
}

FCanvasUVTri ULineOfSightComponent::GenerateTriangle()
{
	return FCanvasUVTri();
}

void ULineOfSightComponent::GenerateEndPointsList(TArray<FVector>* Array, float RotationStepAngle,
                                                  FVector RotateFromVector)
{
	FVector impactPoint, endRotation, endPosition, position;
	position = GetOwner()->GetActorTransform().GetLocation();
	FHitResult result;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(GetOwner());

	for (int i = 0; i < RaysCount; i++)
	{
		endRotation = RotateFromVector.RotateAngleAxis(RotationStepAngle * i, GetOwner()->GetActorUpVector());
		endPosition = position + endRotation * SightLineDistance;
		if (GetWorld()->LineTraceSingleByChannel(result, position, endPosition,
		                                         ECC_GameTraceChannel4, Params))
		{
			impactPoint = result.ImpactPoint;
		}
		else
		{
			impactPoint = endPosition;
		}
		Array->Add(impactPoint + endRotation * 10);
	}
}

void ULineOfSightComponent::GenerateTrianglesArray(TArray<FCanvasUVTri>* Array, const FVector2D& CenterOfTriangles,
                                                   TArray<FVector>* Vectors)
{
	FCanvasUVTri baseTri;
	FVector2D actorPosition = static_cast<FVector2D>(GetOwner()->GetTransform().GetLocation());
	baseTri.V0_Pos = CenterOfTriangles;
	baseTri.V0_Color = FColor::White;
	baseTri.V1_Color = FColor::White;
	baseTri.V2_Color = FColor::White;

	for (int i = 0; i < Vectors->Num() - 1; i++)
	{
		baseTri.V1_Pos = CenterOfTriangles + (static_cast<FVector2D>((*Vectors)[i]) - actorPosition);
		baseTri.V2_Pos = CenterOfTriangles + (static_cast<FVector2D>((*Vectors)[i + 1]) - actorPosition);
		Array->Add(FCanvasUVTri(baseTri));
	}
}

void ULineOfSightComponent::DrawLineOfSight(UCanvas* Canvas, int32 Width, int32 Height)
{
	TArray<FCanvasUVTri> triangles;
	TArray<FVector> endPoints;

	FVector leftEnd = GetOwner()->GetActorForwardVector().RotateAngleAxis(
		-(SightAngle / 2), GetOwner()->GetActorUpVector());

	GenerateEndPointsList(&endPoints, SightAngle / RaysCount, leftEnd);
	GenerateTrianglesArray(&triangles, FVector2D(Width / 2, Height / 2), &endPoints);
	Canvas->K2_DrawTriangle(nullptr, triangles);
}


// Called when the game starts
void ULineOfSightComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ShouldTick)
	{
		FoSRenderTarget->OnCanvasRenderTargetUpdate.AddDynamic(this, &ULineOfSightComponent::DrawLineOfSight);
	}

	FoSCollectionInstance = GetWorld()->GetParameterCollectionInstance(FoSCollection);
}


// Called every frame
void ULineOfSightComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldTick)
	{
		FoSRenderTarget->UpdateResource();
		FoSCollectionInstance->SetVectorParameterValue(
			TEXT("PlayerPosition"), FLinearColor(GetOwner()->GetActorTransform().GetLocation()));
	}
}
