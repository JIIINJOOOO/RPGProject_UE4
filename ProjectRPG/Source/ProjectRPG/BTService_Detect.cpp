// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "MonsterAIController.h"
#include "AdamCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "DrawDebugHelpers.h"


UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;
	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 700.0f;

	if (nullptr == World)
		return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::TargetKey, nullptr);
			AAdamCharacter* AdamCharacter = Cast<AAdamCharacter>(OverlapResult.GetActor());
			if (AdamCharacter && AdamCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::TargetKey, AdamCharacter);
				//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
			}
		}
	}
	else
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::TargetKey, nullptr);
	
	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
