// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttackInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class LETHAL_DED_API UAttackInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
	
};

class IAttackInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void AttackUpdate(float _DeltaTime);
	virtual void AttackStart();
	virtual void AttackEnd();
};
