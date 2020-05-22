// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor {

	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Place an Actor in a Randomly generated location within the boundaries of the tile
	UFUNCTION(BlueprintCallable, Category = Props)
	void PlaceActor(TSubclassOf<AActor> ObjectToSpawn, int MinSpawn, int MaxSpawn);

	/* Contains the number of AActor Objects spawned via the PlaceActor funtion */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Props)
	TArray<AActor*> SpawnedObjects; // Does this need to be accessed from public (Make a getter if so)

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Do a sphere cast around the actor that is spawned
	bool CastSphere(FVector Location, float Radius);

};
