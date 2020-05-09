// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include "TestingGroundsProjectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGun::AGun() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.200007f, 71.724091f, 11.299643f));
	FP_MuzzleLocation->SetRelativeRotation(FRotator(0.0f,0.0f, 90.0f));
}

// Called when the game starts or when spawned
void AGun::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AGun::OnFire() {
	// try and fire a projectile
	if (ProjectileClass != NULL) {

		UWorld* const World = GetWorld();
		if (World != NULL) {

			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
			const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ATestingGroundsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			UE_LOG(LogTemp, Warning, TEXT("FIRED"));
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL) {
		// Get the animation object for the arms mesh
		if (AnimInstance != NULL) {
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

