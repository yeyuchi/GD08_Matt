// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "MyPawnSensingComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AI, HideCategories = (Activation, "Components|Activation", Collision), meta = (BlueprintSpawnableComponent))
class MYAPRG_API UMyPawnSensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "AI|Components|PawnSensing")
	virtual bool HasLineOfSightTo(const AActor* Other) const;

};
