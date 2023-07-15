// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnSensingComponent.h"
bool UMyPawnSensingComponent::HasLineOfSightTo(const AActor* Other) const
{
	return Super::HasLineOfSightTo(Other);
}