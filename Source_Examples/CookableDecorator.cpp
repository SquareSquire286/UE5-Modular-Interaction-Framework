// Fill out your copyright notice in the Description page of Project Settings.


#include "CookableDecorator.h"

// Sets default values
ACookableDecorator::ACookableDecorator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Sets overloaded values (precursor to executing decorator logic)
ACookableDecorator::ACookableDecorator(AGrabbable baseObject)
{

}

// Called when the game starts or when spawned
void ACookableDecorator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACookableDecorator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACookableDecorator::SetUpMaterialInstance(FName OptionalName)
{

}

void ACookableDecorator::Cook()
{

}