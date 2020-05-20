// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"


AMannequin::AMannequin() {

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a First Person CameraComponent
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FPCamera->bUsePawnControlRotation = true;

	// Create a First Person Mesh Component
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	FPMesh->SetupAttachment(FPCamera);
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	FPMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	FPMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}


void AMannequin::BeginPlay() {
	Super::BeginPlay();

	SetupGun();
}

// Called to attached the gun to the Third Person mesh on Death
void AMannequin::UnPossessed() {
	Super::UnPossessed();

	if (!(GunRef == nullptr))
		GunRef->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

// Called every frame
void AMannequin::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
}

void AMannequin::PullTrigger() {
	if (GunRef == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Gun not Set in Blueprint - Mannequin.cpp,68"));
		return;
	}

	// if not, fire
	GunRef->FireProjectile();
}

void AMannequin::SetupGun() {

	// Spawn the Gun 
	GunRef = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	if (GunRef == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Gun Setup Error, Check Blueprint - Mannequin.cpp,82"));
		return;
	}

	// Attach the spawned gun into the mesh
	if (IsPlayerControlled()) {
		GunRef->AttachToComponent(FPMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else {
		GunRef->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}

	//Setup Animation Instances
	GunRef->FPAnimInstance = FPMesh->GetAnimInstance();
	GunRef->TPAnimInstance = GetMesh()->GetAnimInstance();

}