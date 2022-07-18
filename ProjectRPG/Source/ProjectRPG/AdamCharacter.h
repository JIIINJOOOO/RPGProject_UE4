// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "EngineMinimal.h"
#include "PalaceWorld.h"
#include "GameFramework/Character.h"
#include "AdamCharacter.generated.h"




UCLASS()
class PROJECTRPG_API AAdamCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's properties
	AAdamCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override; // 부모 AActor에 데미지 관련 로직이 구현되어 있어 super키워드로 부모 클래스 로직 먼저 실행

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// 캐릭터 스탯
	UPROPERTY(Replicated,VisibleAnywhere, Category = Stat)
	class UAdamCharacterStatComponent* CharacterStat;

	// 등 뒤 무기 스태틱메쉬들
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Bow;
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Quiver; // 화살통
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Scabbard; // 칼집
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Sword; // 칼집에 넣은 칼
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Shield; // 칼집에 넣은 칼
	
	// 사용하는 무기 액터
	UPROPERTY(VisibleAnywhere, Category = Weapon_Use)
	class AAdamWeaponSword* Weapon_Sword;
	UPROPERTY(VisibleAnywhere, Category = Weapon_Use)
	class AAdamWeaponShield* Weapon_Shield;
	UPROPERTY(VisibleAnywhere, Category = Weapon_Use)
	class AAdamWeaponBow* Weapon_Bow;

	// 화살 오브젝트 풀
	class AAdamObjectPool* ArrowPool;
	// 화살 액터
	class AAdamArrow* Bow_Arrow;
	
	/*UPROPERTY(EditDefaultsOnly, Category = Arrow)
	TSubclassOf<class AAdamArrow> ArrowClass;*/ // 스폰할때 쓸 화살 클래스

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	//////////////////////////////////////////////
	// Input Handlers
	// 상하좌우 이동S
	void MoveFB(float NewAxisValue);
	void MoveLR(float NewAxisValue);

	void OnAttack(); // 기본공격. 나중에 무기 따라 다르게
	// shift키-달리기
	/** 플레이어가 sprint action을 눌렀다 */
	void OnStartSprinting();	
	/** 플레이어가 sprint action 키 뗐다 */
	void OnStopSprinting(); 
	/** 플레이어가 무기별 능력 키 뗐다 */
	void OnUseWeaponAbility(); // 무기 특수기능. 무기 따라 다르게
	/** 플레이어가 무기별 능력 키 뗐다 */
	void OnStopWeaponAbility();
	/*void UseWeaponAbility(); 
	void StopWeaponAbility();*/
	// 숫자키 : 무기 전환
	void OnSwordAndShieldMode();
	void OnBowMode();

	// getter
	//FORCEINLINE bool GetIsDead() { return bIsDead; };
private:
	//////////////////////////////////////////////
	// server replication functions
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetSprinting(bool bNewSprinting);
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetUsingShield(bool bNewUsingShield);
	UFUNCTION(reliable, server, WithValidation)
	void ServerSetAimingArrow(bool bNewAimingArrow);
	UFUNCTION(reliable, server, WithValidation)
	void ServerSwitchWeaponMode(EWeaponType NewWeapon);
	UFUNCTION(reliable, server, WithValidation)
	void ServerDoBasicAttack();
private:
	//void LoadStaticMeshInConstructor(UStaticMeshComponent* SMComponent,FName SocketName, FName ComponentName, UStaticMesh* mesh);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnAttackNextAttackCheck();

	// 칼로 무기 전환 
	void SwordTookOutCheck();
	// 활로 무기 전환
	void BowTookOutCheck();
	// 칼 공격 콤보
	void AttackStartComboState();
	void AttackEndComboState();
	// 칼 공격 탐지
	UFUNCTION(server,reliable)
	void HitActorApplyDamage(const FHitResult& HitResult);
	void AttackCheck();
	
	// 활 기본공격 델리게이트
	void BowAttackPickArrowCheck();
	void BowAttackShootArrowCheck();
	// 활 공격 화살 데이터(데미지,컨트롤러) set
	UFUNCTION(server, reliable)
	void SetArrowDamageData();

	// HPIsZero일때 Delegate
	void HPIsZero();

	// [server+ local] sprint상태를 바꾼다
	void SetSprinting(bool bNewSprinting);
	// [server+ local] shield 사용 상태를 바꾼다
	void SetUsingShield(bool bNewUsingShield);
	// [server+ local] aiming arrow 사용 상태를 바꾼다
	void SetAimingArrow(bool bNewAimingArrow);
	/** CurWeaponType 업데이트 */
	UFUNCTION(NetMulticast,reliable, WithValidation)
	void SetCurrentWeaponMode(EWeaponType NewWeapon);
	// 기본 공격 로직 함수
	UFUNCTION(NetMulticast, reliable, WithValidation)
	void DoBasicAttack();
	/*UFUNCTION()
	void OnRep_CurrentComboMtgUpdate(int32 NewCurrentCombo);*/

	/** 현재 무기 리플리케이션 handler */
	/*UFUNCTION()
	void OnRep_CurrentWeaponModeUpdate(EWeaponType NewWeapon);*/

	UFUNCTION(NetMulticast, reliable, WithValidation)
	void SetAttackMtgByCurrentCombo(int32 NewCurrentCombo);
private:
	UPROPERTY(Replicated/*ReplicatedUsing = OnRep_CurrentWeaponModeUpdate*/,VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // 현재 무기 타입
	EWeaponType CurWeaponType;

	// 무기 공통 공격중인지 변수
	UPROPERTY(Replicated,VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

	// 칼 공격 콤보 변수들
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bCanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsComboInputOn;
	UPROPERTY(/*Replicated,*//*ReplicatedUsing = OnRep_CurrentComboMtgUpdate, */VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	// 칼 공격 충돌처리: 캡슐 디버그 드로잉
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;

	UPROPERTY()
	class UAdamAnimInstance* AdamAnim;
	
	/*UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsDead;*/
	/** Identifies if pawn is in its dying state */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, Meta = (AllowPrivateAccess = true))
	uint32 bIsDying : 1;

	// 네트워크 리플리케이션 위한 변수들
	/** 현재 Sprint 중 인지 아닌지 상태*/
	UPROPERTY(Transient, Replicated)
	uint8 bIsSprinting : 1;
	/** 현재 무기별 능력 사용중 인지 아닌지 상태*/
	UPROPERTY(Transient, Replicated)
	uint8 bIsUsingShield : 1;
	UPROPERTY(Transient, Replicated)
	uint8 bIsAimingArrow : 1;
public:
	//////////////////////////////////////////////
	// getter
	/**sprint 중인지 상태 get*/
	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsSprinting() const;
	bool IsUsingShield() const;
	bool IsAimingArrow() const;

	float GetSprintingSpeedModifier() const;

	
};
