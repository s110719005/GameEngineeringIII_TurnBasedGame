// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::MoveForward()
{
	UE_LOG(LogTemp, Warning, TEXT("MOVE FORWARD"));
	this->SetActorLocation(this->GetActorLocation() + FVector(100.0f, 0, 0));
}

void APlayerCharacter::MoveBackward()
{
	UE_LOG(LogTemp, Warning, TEXT("MOVE BACKWARD"));
	this->SetActorLocation(this->GetActorLocation() + FVector(-100.0f, 0, 0));
}

void APlayerCharacter::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("MOVE RIGHT"));
	this->SetActorLocation(this->GetActorLocation() + FVector(0, 100, 0));
}

void APlayerCharacter::MoveLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("MOVE LEFT"));
	this->SetActorLocation(this->GetActorLocation() + FVector(0, -100, 0));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//ME: thing inside"" should be set in edit/projectsettings/input Action binding
	//PlayerInputComponent->BindAction("Forward", IE_Pressed, this, &ACharacter::SetActorLocation(this->GetActorLocation() + FVector(1, 0, 0))
	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAction("MoveBackWard", IE_Pressed, this, &APlayerCharacter::MoveBackward);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APlayerCharacter::MoveLeft);

}

