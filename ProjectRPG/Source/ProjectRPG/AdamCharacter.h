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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override; // �θ� AActor�� ������ ���� ������ �����Ǿ� �־� superŰ����� �θ� Ŭ���� ���� ���� ����

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// ĳ���� ����
	UPROPERTY(Replicated,VisibleAnywhere, Category = Stat)
	class UAdamCharacterStatComponent* CharacterStat;

	// �� �� ���� ����ƽ�޽���
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Bow;
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Quiver; // ȭ����
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Scabbard; // Į��
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Sword; // Į���� ���� Į
	UPROPERTY(VisibleAnywhere, Category = Weapon_Back)
	UStaticMeshComponent* Shield; // Į���� ���� Į
	
	// ����ϴ� ���� ����
	UPROPERTY(VisibleAnywhere, Category = Weapon_Use)
	class AAdamWeaponSword* Weapon_Sword;
	UPROPERTY(VisibleAnywhere, Category = Weapon_Use)
	class AAdamWeaponShield* Weapon_Shield;
	UPROPERTY(VisibleAnywhere, Category = Weapon_Use)
	class AAdamWeaponBow* Weapon_Bow;

	// ȭ�� ������Ʈ Ǯ
	class AAdamObjectPool* ArrowPool;
	// ȭ�� ����
	class AAdamArrow* Bow_Arrow;
	
	/*UPROPERTY(EditDefaultsOnly, Category = Arrow)
	TSubclassOf<class AAdamArrow> ArrowClass;*/ // �����Ҷ� �� ȭ�� Ŭ����

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	//////////////////////////////////////////////
	// Input Handlers
	// �����¿� �̵�S
	void MoveFB(float NewAxisValue);
	void MoveLR(float NewAxisValue);

	void OnAttack(); // �⺻����. ���߿� ���� ���� �ٸ���
	// shiftŰ-�޸���
	/** �÷��̾ sprint action�� ������ */
	void OnStartSprinting();	
	/** �÷��̾ sprint action Ű �ô� */
	void OnStopSprinting(); 
	/** �÷��̾ ���⺰ �ɷ� Ű �ô� */
	void OnUseWeaponAbility(); // ���� Ư�����. ���� ���� �ٸ���
	/** �÷��̾ ���⺰ �ɷ� Ű �ô� */
	void OnStopWeaponAbility();
	/*void UseWeaponAbility(); 
	void StopWeaponAbility();*/
	// ����Ű : ���� ��ȯ
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

	// Į�� ���� ��ȯ 
	void SwordTookOutCheck();
	// Ȱ�� ���� ��ȯ
	void BowTookOutCheck();
	// Į ���� �޺�
	void AttackStartComboState();
	void AttackEndComboState();
	// Į ���� Ž��
	UFUNCTION(server,reliable)
	void HitActorApplyDamage(const FHitResult& HitResult);
	void AttackCheck();
	
	// Ȱ �⺻���� ��������Ʈ
	void BowAttackPickArrowCheck();
	void BowAttackShootArrowCheck();
	// Ȱ ���� ȭ�� ������(������,��Ʈ�ѷ�) set
	UFUNCTION(server, reliable)
	void SetArrowDamageData();

	// HPIsZero�϶� Delegate
	void HPIsZero();

	// [server+ local] sprint���¸� �ٲ۴�
	void SetSprinting(bool bNewSprinting);
	// [server+ local] shield ��� ���¸� �ٲ۴�
	void SetUsingShield(bool bNewUsingShield);
	// [server+ local] aiming arrow ��� ���¸� �ٲ۴�
	void SetAimingArrow(bool bNewAimingArrow);
	/** CurWeaponType ������Ʈ */
	UFUNCTION(NetMulticast,reliable, WithValidation)
	void SetCurrentWeaponMode(EWeaponType NewWeapon);
	// �⺻ ���� ���� �Լ�
	UFUNCTION(NetMulticast, reliable, WithValidation)
	void DoBasicAttack();
	/*UFUNCTION()
	void OnRep_CurrentComboMtgUpdate(int32 NewCurrentCombo);*/

	/** ���� ���� ���ø����̼� handler */
	/*UFUNCTION()
	void OnRep_CurrentWeaponModeUpdate(EWeaponType NewWeapon);*/

	UFUNCTION(NetMulticast, reliable, WithValidation)
	void SetAttackMtgByCurrentCombo(int32 NewCurrentCombo);
private:
	UPROPERTY(Replicated/*ReplicatedUsing = OnRep_CurrentWeaponModeUpdate*/,VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // ���� ���� Ÿ��
	EWeaponType CurWeaponType;

	// ���� ���� ���������� ����
	UPROPERTY(Replicated,VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

	// Į ���� �޺� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bCanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsComboInputOn;
	UPROPERTY(/*Replicated,*//*ReplicatedUsing = OnRep_CurrentComboMtgUpdate, */VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	// Į ���� �浹ó��: ĸ�� ����� �����
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

	// ��Ʈ��ũ ���ø����̼� ���� ������
	/** ���� Sprint �� ���� �ƴ��� ����*/
	UPROPERTY(Transient, Replicated)
	uint8 bIsSprinting : 1;
	/** ���� ���⺰ �ɷ� ����� ���� �ƴ��� ����*/
	UPROPERTY(Transient, Replicated)
	uint8 bIsUsingShield : 1;
	UPROPERTY(Transient, Replicated)
	uint8 bIsAimingArrow : 1;
public:
	//////////////////////////////////////////////
	// getter
	/**sprint ������ ���� get*/
	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsSprinting() const;
	bool IsUsingShield() const;
	bool IsAimingArrow() const;

	float GetSprintingSpeedModifier() const;

	
};
