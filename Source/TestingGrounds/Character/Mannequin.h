// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter {
	GENERATED_BODY()

		/* First Person Camera */
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Camera)
		class UCameraComponent* FPCamera;

	/* First Person Mesh (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FPMesh;

public:

	/* Calls the fire function inside the Gun child object */
	UFUNCTION(BlueprintCallable, Category = Firing)
		void PullTrigger();

	/* Sets the gun blueprint */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TSubclassOf<class AGun> GunBlueprint;


	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called to attached the gun to the Third Person mesh on Death
	virtual void UnPossessed() override;

private:

	// Instance of the gun
	class AGun* GunRef;

	// Function to spawn the gun, attach it and hook up anim instance
	void SetupGun();

public:

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return FPMesh; }

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FPCamera; }

};
