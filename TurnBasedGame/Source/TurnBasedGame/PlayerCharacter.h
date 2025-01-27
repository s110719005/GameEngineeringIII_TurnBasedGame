// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridPool.h"
#include "PlayerCharacter.generated.h"

class Command
{
public:
	int moveX;
	int moveY;
	int snowballMoveX;
	int snowballMoveY;
	ASnowball* hiddenSnowball;
	ASnowball* movingSnowball;
	FVector movingSnowballSize;
	//scale

	Command(int x, int y, ASnowball* i_hiddenSnowball, ASnowball* i_movingSnowball, int i_snowballX, int i_snowballY, FVector i_movingSnowballSize)
	{
		moveX = x;
		moveY = y;
		hiddenSnowball = i_hiddenSnowball;
		movingSnowball = i_movingSnowball;
		snowballMoveX = i_snowballX;
		snowballMoveY = i_snowballY;
		movingSnowballSize = i_movingSnowballSize;
	}
	Command()
	{
		moveX = 0;
		moveY = 0;
		hiddenSnowball = nullptr;
		movingSnowball = nullptr;
		snowballMoveX = 0;
		snowballMoveY = 0;
	}
};


UCLASS()
class TURNBASEDGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void Undo();
	void Redo();
	void MovePlayer(int i_x, int i_y);
	bool CheckNextMove(int i_x, int i_y);

	UGridPool* gridReference;
	int gridX;
	int gridY;
	TArray<Command> currentCommands;
	TArray<Command> undoCommands;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Grid")
	AActor* gridActor;
};
