// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobDevUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LETHAL_DED_API UGlobDevUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Global|Network")
	void StartServer();

	UFUNCTION(BlueprintCallable, Category = "Global|Network")
	void ConnectServer();
	
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global|Network", meta = (AllowPrivateAccess = "true"))
	FString IP = TEXT("127.0.0.1");
	
};
