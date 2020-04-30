// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRouteComponent.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	//Get Patrol Points
	TArray<AActor*> PatrolRoutes = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRouteComponent>()->GetPatrolPoints();

	//! Checking to see if Component is added into the Actor
	if (!ensure(OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRouteComponent>()))
		EBTNodeResult::Failed;



	//Set Next Waypoint
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, PatrolRoutes[BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName)]);

	//Cycle Index
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, ((BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName) + 1) % PatrolRoutes.Num()));

	//UE_LOG(LogTemp, Warning, TEXT("Index Value = %i"), PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}
