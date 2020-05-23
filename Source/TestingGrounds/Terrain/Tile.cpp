// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}


/* Use this function to spawn multiple random amount of actors which you specify per tile that is non colliding with another actor.
@ObjectToSpawn = The Actor Reference of the Object to be spawned in the Tile
@MinSpawn = Minimum Spawn value to run the random range from
@MaxSpawn = Maximum Spawn value to run the random range from
@Radius = The Radius of the SphereTrace to check if another object exists within its spawn point, and if so, move this object to another randomly generated location.*/
void ATile::PlaceActors(TSubclassOf<AActor> ObjectToSpawn, int MinSpawn, int MaxSpawn, float Radius) {

	// Loop to make the object produce multiple times
	int LoopRange = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < LoopRange; i++) {

		// Returns an empty spawn location (Not always)
		FVector SpawnPoint;
		bool found = FindEmptyLocation(SpawnPoint, Radius);

		// If the returned spawn location is actually empty then spawn actor
		if (found)
			PlaceActor(ObjectToSpawn, SpawnPoint);
	}
}

// Do a sphere cast around the location and radius given to it, and returns true if it collides with another actor (Not for the ground or Trigger volumes)
bool ATile::CanSpawnAtLocation(FVector Location, float Radius) {

	// SweepSingleByChannel Trace
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location); //Convert Local to World Coordinates
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation + FVector(0, 0, 1),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	// Draw a debug line to see the channel
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, 100);

	return !HasHit;
}

// This function returns true if found a location, and false if didnt. Also returns a unique random location which doesnt collide with other actors per that Radius sent.
bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius) {

	// Write the Ranges of the Box (Static because you don't need to change the ranges)
	FVector MinBounds(-2000.0f, 2000.0f, 100.f);
	FVector MaxBounds(2000.0f, -2000.0f, 100.f);

	// Make a Box based on the Min and Max
	FBox Bounds(MinBounds, MaxBounds);

	// Loop until it returns a correct location or goes over 100
	const int32 MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++) {

		// Calculate the Random FVector point within the Box
		FVector CalculatedPoint(FMath::RandPointInBox(Bounds));

		// SphereTrace and find whether that location collides with any other actor
		if (CanSpawnAtLocation(CalculatedPoint, Radius)) {
			OutLocation = CalculatedPoint;
			return true;
		}
	}

	return false;
}

// Spawn the Actor in the specified location
void ATile::PlaceActor(TSubclassOf<AActor> ObjectToSpawn, FVector SpawnPoint) {

	// Spawn the Actor
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn);

	// Specify the objects Location
	SpawnedActor->SetActorRelativeLocation(SpawnPoint);

	// Attach the Actor into the Tile Blueprint while keeping its relative location and physics properties
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	// Add the object into the array
	SpawnedObjects.Add(SpawnedActor);
}
