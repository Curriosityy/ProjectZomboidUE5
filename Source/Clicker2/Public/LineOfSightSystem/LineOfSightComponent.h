// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components\ActorComponent.h"
#include "LineOfSightComponent.generated.h"


class UCanvasRenderTarget2D;
class UMaterialParameterCollection;
class UCanvas;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CLICKER2_API ULineOfSightComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int RaysCount;

	UPROPERTY(EditDefaultsOnly)
	float SightAngle;

	UPROPERTY(EditDefaultsOnly)
	float SightLineDistance;

	UPROPERTY(EditDefaultsOnly)
	float OutOfSightDistance;

	UPROPERTY(EditDefaultsOnly)
	int RaysCountOutOfSightAngle;


	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCanvasRenderTarget2D> FoSRenderTarget;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialParameterCollection> FoSCollection;

	UPROPERTY(NonTransactional, Transient)
	TObjectPtr<UMaterialParameterCollectionInstance> FoSCollectionInstance;

	UPROPERTY(EditAnywhere)
	bool ShouldTick;

public:
	// Sets default values for this component's properties
	ULineOfSightComponent();

protected:
	FCanvasUVTri GenerateTriangle();

	void GenerateEndPointsList(TArray<FVector>* Array, float RotationStepAngle, FVector RotateFromVector, int Ticks,
	                           float RayDistance);

	void GenerateTrianglesArray(TArray<FCanvasUVTri>* Array, const FVector2D& CenterOfTriangles, TArray<FVector>* Vectors, bool looped);

	UFUNCTION()
	void DrawLineOfSight(UCanvas* Canvas, int32 Width, int32 Height);

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
