// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TP_ThirdPersonCharacter.generated.h"

UCLASS()
class MYAPRG_API ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


public:
	// Sets default values for this character's properties
	ATP_ThirdPersonCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera);
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera);
	float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float forward_value);
	void MoveRight(float right_value);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
		void OnDamaged(float Damage, const FHitResult& HitInfo, class ATP_ThirdPersonCharacter* InstigatedCharacter, AActor* DamageCauser);

public:
	UFUNCTION(BlueprintCallable, Category = "Character")
		virtual void HandleDamage(float Damage, const FHitResult& HitInfo, class ATP_ThirdPersonCharacter* InstigatedCharacter, AActor* DamageCauser)
	{
		OnDamaged(Damage, HitInfo, InstigatedCharacter, DamageCauser);
	}
};
