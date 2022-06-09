// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "EngineMinimal.h"
#include "PalaceWorld.h"
#include "GameFramework/Character.h"
#include "AdamCharacter.generated.h"




UCLASS()
class PROJECTRPG_API AAdamCharacter : public ACharacter
{
	GENERATED_BODY()

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
	UPROPERTY(VisibleAnywhere, Category = Stat)
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


	// �����¿� �̵�
	void MoveFB(float NewAxisValue);
	void MoveLR(float NewAxisValue);
	void Attack(); // �⺻����. ���߿� ���� ���� �ٸ���
	// shiftŰ-�޸���
	void Sprint(); 
	void StopSprinting();
	void UseWeaponAbility(); // ���� Ư�����. ���� ���� �ٸ���
	void StopWeaponAbility();
	// ����Ű : ���� ��ȯ
	void SwordAndShieldMode();
	void BowMode();

	// getter
	//FORCEINLINE bool GetIsDead() { return bIsDead; };

private:
	//void LoadStaticMeshInConstructor(UStaticMeshComponent* SMComponent,FName SocketName, FName ComponentName, UStaticMesh* mesh);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// Į�� ���� ��ȯ 
	void SwordTookOutCheck();
	// Ȱ�� ���� ��ȯ
	void BowTookOutCheck();
	// Į ���� �޺�
	void AttackStartComboState();
	void AttackEndComboState();
	// Į ���� Ž��
	void AttackCheck();
	
	// Ȱ �⺻���� ��������Ʈ
	void BowAttackPickArrowCheck();
	void BowAttackShootArrowCheck();
	

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // ���� ���� Ÿ��
	EWeaponType CurWeaponType;

	// ���� ���� ���������� ����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

	// Į ���� �޺� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bCanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
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

	

	
};