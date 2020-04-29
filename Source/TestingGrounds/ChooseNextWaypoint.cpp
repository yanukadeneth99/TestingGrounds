// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UE_LOG(LogTemp, Warning, TEXT("Index Value = %i"), BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName));
	return EBTNodeResult::Succeeded;
}