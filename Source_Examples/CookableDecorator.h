// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grabbable.h"
#include "CookableDecorator.generated.h"

UCLASS(Blueprintable, BlueprintType)
class [REDACTED]_API ACookableDecorator : public AGrabbable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACookableDecorator();

	// Overloaded constructor that encapsulates the decoration logic
	ACookableDecorator(AGrabbable baseObject);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetUpMaterialInstance(FName OptionalName) override;

	virtual void Cook() override;
};
