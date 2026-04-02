// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabbable.h"
#include "GameplayTagContainer.h"
#include "GameplayTags.h"
#include "..\Public\Grabbable.h"

// Sets default values
AGrabbable::AGrabbable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ParentMesh"));
	SetRootComponent(ParentMesh);
}

// Overloaded constructor for situations where we want to specify what type of mesh component should be created as the root
AGrabbable::AGrabbable(EGrabbableMeshComponentType meshType)
{
	switch (meshType)
	{
	    case EGrabbableMeshComponentType::Skeletal: ParentMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ParentMesh")); break;
		case EGrabbableMeshComponentType::Procedural: ParentMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ParentMesh")); break;
		default: ParentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ParentMesh")); break;
	}
}

// Called when the game starts or when spawned
void AGrabbable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGrabbable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrabbable::Grab()
{
	this->ParentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECollisionResponse::ECR_Ignore); // ECC_GameTraceChannel5 is the Hand channel

	FGameplayTag tag = FGameplayTag::RequestGameplayTag(FName("Grabbable.Held"));
	this->GameplayTags->AddTag(tag, wasAdded);

	this->IsGrabbed = true;
	this->ParentMesh->SetSimulatePhysics(false);
	this->ParentMesh->SetRenderCustomDepth(false);

	OnGrabStarted.Broadcast(this); // should show up in BPs as an event dispatcher, but need to confirm this
}

void AGrabbable::Release(FVector inputVelocity, FVector inputAngularVelocity)
{
	this->IsGrabbed = false;

	// GameplayTags->RemoveTag -- again, need to figure out how this works and then populate this function signature with Grabbable.Held

	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (this->IsOutsideValidZone)
	{
		// cast ParentMesh to UStaticMeshComponent, update its StaticMesh property with InitialMesh

		this->ParentMesh->SetSimulatePhysics(false);
		this->ParentMesh->SetWorldLocationAndRotation(InitialTransform.GetTranslation(), InitialTransform.GetRotation(), false, nullptr, ETeleportType::None);
	}

	else
	{
		this->ParentMesh->SetSimulatePhysics(true);
		this->ParentMesh->SetPhysicsLinearVelocity(inputVelocity, false, NAME_None);
		this->ParentMesh->SetPhysicsAngularVelocityInRadians(inputAngularVelocity, false, NAME_None);
	}
	
	this->ParentMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECollisionResponse::ECR_Block); // ECC_GameTraceChannel5 is the Hand channel
	this->OnGrabEnded.Broadcast(this); // should show up in BPs as an event dispatcher, but need to confirm this
}

void AGrabbable::ActivateHighlight()
{
	this->ParentMesh->SetRenderCustomDepth(true);

	if (this->ParentMesh->CustomDepthStencilValue == 2) // attention channel (cyan)
		this->ShouldRevertToAttentionHighlight = true;

	else this->ShouldRevertToAttentionHighlight = false;

	this->ParentMesh->SetCustomDepthStencilValue(1); // grab channel (purple)
}

void AGrabbable::DeactivateHighlight()
{
	if (ShouldRevertToAttentionHighlight)
		this->ParentMesh->SetCustomDepthStencilValue(2);

	else this->ParentMesh->SetCustomDepthStencilValue(0);
}

UMeshComponent* AGrabbable::GetMesh()
{
	return this->ParentMesh;
}

void AGrabbable::SetUpMaterialInstance(FName OptionalName)
{

}

void AGrabbable::Cook()
{

}

void AGrabbable::Slice()
{

}