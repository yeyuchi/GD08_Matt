// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_ThirdPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent :: SocketName);
	FollowCamera->bUsePawnControlRotation = false;



	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;  
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540, 0);  
	GetCharacterMovement()->JumpZVelocity = 650; 
	GetCharacterMovement()->AirControl = 0.2f;

}

void ATP_ThirdPersonCharacter::MoveForward(float Value)  //前后移动的方法
{
	if (Controller && Value != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();  //拿到控制器的旋转
		const FRotator YawRotation(0.f, Rotation.Yaw, 0);  //作为左右旋转的值

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);  //构造旋转矩阵，从矩阵中获取x轴的向量
		AddMovementInput(Direction, Value);
	}
}


void ATP_ThirdPersonCharacter::MoveRight(float Value)  //左右移动的方法
{
	if (Controller && Value != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}


void ATP_ThirdPersonCharacter::TurnAtRate(float Value)  
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void ATP_ThirdPersonCharacter::TurnLookupRate(float Value)  
{
	AddControllerPitchInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATP_ThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATP_ThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATP_ThirdPersonCharacter::MoveRight);

	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("Lookup", this, &ATP_ThirdPersonCharacter::TurnLookupRate);
	PlayerInputComponent->BindAxis("Turn", this, &ATP_ThirdPersonCharacter::TurnAtRate);

}

