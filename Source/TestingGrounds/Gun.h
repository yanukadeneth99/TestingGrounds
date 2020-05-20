// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TESTINGGROUNDS_API AGun : public AActor {

	GENERATED_BODY()

		/** Gun mesh: 1st person view (seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

protected:

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;


public:
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ATestingGroundsProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** First Person AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FPFireMontage;

	/** Third Person AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* TPFireMontage;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = Fire)
		void FireProjectile();


	/** First Person Animation Instance to play when gun fires */
	UPROPERTY(VisibleAnywhere, Category = Animation)
		UAnimInstance* FPAnimInstance;

	/** Third Person Animation Instance to play when gun fires */
	UPROPERTY(VisibleAnywhere, Category = Animation)
		UAnimInstance* TPAnimInstance;

};
