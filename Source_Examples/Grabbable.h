// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "../Plugins/GameplayTagUtilities/Source/GameplayTagUtilities/Public/GameplayTagsComponent.h"
#include "ProceduralMeshComponent.h"
#include "Grabbable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectiveDelegate, AGrabbable*, grabbable);

UENUM(BlueprintType)
enum class EGrabbableMeshComponentType : uint8
{
	Static = 0  UMETA(DisplayName = "Static"),
	Skeletal = 1  UMETA(DisplayName = "Skeletal"),
	Procedural = 2  UMETA(DisplayName = "Procedural")
};

UCLASS(Blueprintable, BlueprintType)
class [REDACTED]_API AGrabbable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabbable();

	// Overloaded constructor that handles creation of different mesh component types as the root
	AGrabbable(EGrabbableMeshComponentType meshType);

	// Instanced version will be a static, skeletal, or procedural mesh (usually static)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UMeshComponent* ParentMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UGameplayTagsComponent* GameplayTags;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Objective Logic")
	FObjectiveDelegate OnGrabStarted;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Objective Logic")
	FObjectiveDelegate OnGrabEnded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Properties")
	bool IsGrabbed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Properties")
	bool NoLongerGrabbable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Properties")
	bool ShouldRevertToAttentionHighlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Properties")
	bool IsOutsideValidZone;

	UPROPERTY(VisibleAnywhere, Category = "BasicProperties")
	bool wasAdded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Properties")
	FVector PreviousPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Properties")
	FRotator PreviousRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Properties")
	FTransform InitialTransform;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Basic Properties")
	UStaticMesh* InitialMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Grab();

	UFUNCTION(BlueprintCallable)
	virtual void Release(FVector inputVelocity, FVector inputAngularVelocity);

	UFUNCTION(BlueprintCallable)
	virtual void ActivateHighlight();

	UFUNCTION(BlueprintCallable)
	virtual void DeactivateHighlight();

	/** Please add a function description */
	UFUNCTION(BlueprintPure)
	virtual UMeshComponent* GetMesh();

	/** Please add a function description */
	UFUNCTION(BlueprintCallable)
	virtual void SetUpMaterialInstance(FName OptionalName);

	/** Overridden by ACookableDecorator and all of its cocnrete children */
	UFUNCTION(BlueprintCallable)
	virtual void Cook();

	/** Overridden by ASliceableDecorator and all of its concrete children */
	UFUNCTION(BlueprintCallable)
	virtual void Slice();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GrabbablePickedUp(AGrabbable* grabbable);

	UFUNCTION(BlueprintImplementableEvent)
	void GrabbableReleased(AGrabbable* grabbable);
};
