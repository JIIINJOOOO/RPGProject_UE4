// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomBaseLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"


void ACustomBaseLevelScriptActor::BeginPlay()
{
	UGameplayStatics::OpenLevel(this,"127.0.0.1",true);
}
