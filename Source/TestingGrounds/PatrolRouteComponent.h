// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"

/** 
 * A Component that can be added into actors that makes the actor have waypoint navigation
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Points")
		TArray<AActor*> PatrolPoints;

public:
	TArray<AActor*> GetPatrolPoints() const;
		
};
