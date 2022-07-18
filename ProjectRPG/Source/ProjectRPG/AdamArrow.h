// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "GameFramework/Actor.h"
#include "AdamArrow.generated.h"

UCLASS()
class PROJECTRPG_API AAdamArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdamArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 프로젝타일 속도를 발사 방향으로 초기화 시키는 함수
	void ShootInDirection(const FVector& ShootDirection);
public:
	FORCEINLINE void SetObjectPool(class AAdamObjectPool* InObjectPool) { m_ObjectPool = InObjectPool; } // 자신을 관리하는 오브젝트 풀의 레퍼런스 초기화 위한 함수
	FORCEINLINE bool getIsActive() { return m_bIsActive; } // 해당 오브젝트의 활성화 여부 반환 함수
	void ReturnSelf(); // 자신을 관리하는 오브젝트 풀에 스스로를 반환하고 비활성화 하는 함수
	void SetActive(bool bIsActive); // 자신을 활성/비활성화 하는 함수
	void OnActivated(const FVector& ShootDir); // 활성화 되었을 때 함수

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(server,reliable)
	void HitActorApplyDamage(const FHitResult& HitResult);

	UFUNCTION(NetMulticast,reliable)
	void setArrowDataByPlayer(float dmg, AController* EventInstigator);
	FORCEINLINE float getDamageByPlayerLevel() { return DmgByPlayerLv; }

public:	
	// 화살 메쉬
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Bow_ArrowMesh;
protected:
	// 충돌 박스
	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	class UBoxComponent* ArrowColBox;
	
	// 프로젝타일 컴포넌트
	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* Movement; 
private:
	// 오브젝트 풀링 위한 변수들
	bool m_bIsActive; // 해당 오브젝트의 활성화 여부
	class AAdamObjectPool* m_ObjectPool; // 해당 오브젝트 관리하는 오브젝트 풀의 레퍼런스
	FTimerHandle ArrowTimerHandle; // 충돌 후 오브젝트 풀에 반환 위한 타이머 핸들
	float returnInterval; // 객체가 충돌하고 오브젝트 풀에 반환될때 까지 시간

	// 화살을 쏜 플레이어의 컨트롤러
	AController* ShooterController;

	UPROPERTY(replicated)
	/*static */float DmgByPlayerLv;
};
