// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/World.h"


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

/* Place an Actor in a Randomly generated location within the boundaries of the tile */
void ATile::PlaceActor(TSubclassOf<AActor> ObjectToSpawn, int MinSpawn, int MaxSpawn) {

	// Write the Ranges of the Box (Static because you don't need to change the ranges)
	FVector MinBounds(-2000.0f, 2000.0f, 100.f);
	FVector MaxBounds(2000.0f, -2000.0f, 100.f);

	// Make a Box based on the Min and Max
	FBox Bounds(MinBounds, MaxBounds);

	// Loop to make the object produce multiple times
	int LoopRange = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < LoopRange; i++) {

		// Calculate the Random FVector point in between the given ranges
		FVector CalculatedBox(FMath::RandPointInBox(Bounds));

		// Spawn the Actor
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn);

		// Specify the objects Transform
		SpawnedActor->SetActorRelativeLocation(CalculatedBox);

		// Attach the Actor into the Tile Blueprint while keeping its relative location and physics properties
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

		// Add the object into the array
		SpawnedObjects.Add(SpawnedActor);

	}
}