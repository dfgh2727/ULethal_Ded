// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/DevGlob/GlobDevUserWidget.h"
#include "Global/LCGlobal.h"

void UGlobDevUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UGlobDevUserWidget::StartServer()
{
	APlayerController* Controller = GetOwningLocalPlayer()->GetPlayerController(GetWorld());
	ULCGlobal::StartServer(GetWorld(), Controller);
}

void UGlobDevUserWidget::ConnectServer()
{
	APlayerController* Controller = GetOwningLocalPlayer()->GetPlayerController(GetWorld());
	ULCGlobal::ConnectServer(GetWorld(), Controller, IP);
}

