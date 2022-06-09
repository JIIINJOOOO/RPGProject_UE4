// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	// 관련 키 이름이 절대 변하지 않는다는 가정 하에 static const 사용
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset; 
};
