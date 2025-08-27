// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Interface/AttackInterface.h"

UAttackInterface::UAttackInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void IAttackInterface::AttackUpdate( float _DeltaTime)
{
}

void IAttackInterface::AttackStart()
{
}

void IAttackInterface::AttackEnd()
{
}
