// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamPlayerController.h"
#include "AdamPlayerCameraManager.h"
#include "AdamCharacter.h"


AAdamPlayerController::AAdamPlayerController()
{
	PlayerCameraManagerClass = AAdamPlayerCameraManager::StaticClass();
	
}


void AAdamPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents(); // 폰과 플레이어 컨트롤러가 생성되는 시점 확인 가능

}
void AAdamPlayerController::OnPossess(APawn* aPawn) 
{
	Super::OnPossess(aPawn); // 빙의를 진행하는 시점 
	MyCharacter = Cast<AAdamCharacter>(GetCharacter());
	
}

void AAdamPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameOnly InputMode;  // UI 배제하고 게임에만 입력 전달
	SetInputMode(InputMode);

}

void AAdamPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis(TEXT("MoveFB"), this, &AAdamPlayerController::MoveFB);
	InputComponent->BindAxis(TEXT("MoveLR"), this, &AAdamPlayerController::MoveLR);

	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAdamPlayerController::Jump);
	InputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AAdamPlayerController::StopJumping);

	InputComponent->BindAxis(TEXT("LookUp"),this, &AAdamPlayerController::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &AAdamPlayerController::Turn);

	InputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AAdamPlayerController::Sprint);
	InputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AAdamPlayerController::StopSprinting);

	InputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AAdamPlayerController::Attack);

	InputComponent->BindAction(TEXT("WeaponAbility"), IE_Pressed, this, &AAdamPlayerController::UseWeaponAbility);
	InputComponent->BindAction(TEXT("WeaponAbility"), IE_Released, this, &AAdamPlayerController::StopWeaponAbility);

	// 무기전환 : 숫자키
	InputComponent->BindAction(TEXT("SwordAndShieldMode"), IE_Pressed, this, &AAdamPlayerController::SwordAndShieldMode);
	InputComponent->BindAction(TEXT("BowMode"), IE_Pressed, this, &AAdamPlayerController::BowMode);

}

void AAdamPlayerController::MoveFB(float NewAxisValue)
{
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->MoveFB(NewAxisValue);
	}

}

void AAdamPlayerController::MoveLR(float NewAxisValue)
{
	if (MyCharacter && NewAxisValue != 0.0f)
	{
		MyCharacter->MoveLR(NewAxisValue);
	}
}

void AAdamPlayerController::Jump()
{
	if (MyCharacter)
	{
		MyCharacter->Jump();
	}
}

void AAdamPlayerController::StopJumping()
{
	if (MyCharacter)
	{
		MyCharacter->StopJumping();
	}
}

void AAdamPlayerController::LookUp(float NewAxisValue)
{
	if (MyCharacter)
	{
		MyCharacter->AddControllerPitchInput(NewAxisValue);
	}
	
}

void AAdamPlayerController::Turn(float NewAxisValue)
{
	if (MyCharacter)
	{
		MyCharacter->AddControllerYawInput(NewAxisValue);
	}
}

void AAdamPlayerController::Sprint()
{
	if (MyCharacter)
	{
		MyCharacter->Sprint();
	}
}

void AAdamPlayerController::StopSprinting()
{
	if (MyCharacter)
	{
		MyCharacter->StopSprinting();
	}
}

void AAdamPlayerController::Attack()
{
	if (MyCharacter)
	{
		MyCharacter->Attack();
	}
}

void AAdamPlayerController::UseWeaponAbility()
{
	if (MyCharacter)
	{
		MyCharacter->UseWeaponAbility();
	}
}

void AAdamPlayerController::StopWeaponAbility()
{
	if (MyCharacter)
	{
		MyCharacter->StopWeaponAbility();
	}
}

void AAdamPlayerController::SwordAndShieldMode()
{
	if (MyCharacter)
	{
		MyCharacter->SwordAndShieldMode();
	}
}

void AAdamPlayerController::BowMode()
{
	if (MyCharacter)
	{
		MyCharacter->BowMode();
	}
}






