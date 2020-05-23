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

	/* Use this function to spawn multiple random amount of actors which you specify per tile that is non colliding with another actor.
	@ObjectToSpawn = The Actor Reference of the Object to be spawned in the Tile
	@MinSpawn = Minimum Spawn value to run the random range from
	@MaxSpawn = Maximum Spawn value to run the random range from
	@Radius = The Radius of the SphereTrace to check if another object exists within its spawn point, and if so, move this object to another randomly generated location.*/
	UFUNCTION(BlueprintCallable, Category = Props)
	void PlaceActors(TSubclassOf<AActor> ObjectToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 700.0f);

	/* Contains the number of AActor Objects spawned via the PlaceActor funtion */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Props)
	TArray<AActor*> SpawnedObjects; // Does this need to be accessed from public (Make a getter if so)

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// This function returns true if found a location, and false if didnt. Also returns a unique random location which doesnt collide with other actors per that Radius sent.
	bool FindEmptyLocation(FVector &OutLocation, float Radius);

	// Spawn the Actor in the specified location
	void PlaceActor(TSubclassOf<AActor> ObjectToSpawn, FVector SpawnPoint);

	// Do a sphere cast around the location and radius given to it, and returns true if it collides with another actor (Not for the ground or Trigger volumes)
	bool CanSpawnAtLocation(FVector Location, float Radius);

};
