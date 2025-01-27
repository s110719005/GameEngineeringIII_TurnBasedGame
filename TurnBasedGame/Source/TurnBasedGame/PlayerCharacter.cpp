// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"



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
	gridX = 4;
	gridY = 2;
	this->SetActorLocation(FVector(100 * gridX, 100 * gridY, 50));
	if (gridActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SEARCHING GRID"));
		gridReference = gridActor->FindComponentByClass<UGridPool>();
		if (gridReference != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("FIND POOL, SIZE: %d"), gridReference->gridSizeX);

		}
	}
	
}

void APlayerCharacter::MoveForward()
{
	if (!CheckNextMove(1, 0)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("MOVE FORWARD"));
	undoCommands.Empty();
}

void APlayerCharacter::MoveBackward()
{
	if (!CheckNextMove(-1, 0)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("MOVE BACKWARD"));
	undoCommands.Empty();
}

void APlayerCharacter::MoveRight()
{
	if (!CheckNextMove(0, 1)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("MOVE RIGHT"));
	undoCommands.Empty();
}

void APlayerCharacter::MoveLeft()
{
	if (!CheckNextMove(0, -1)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("MOVE LEFT"));
	undoCommands.Empty();
}

void APlayerCharacter::Undo()
{
	if (currentCommands.Num() >= 1)
	{
		Command newCommand;
		Command lastCommand;
		Command lastTwoCommand;
		lastCommand = currentCommands.Last();
		int ballX = 0;
		int ballY = 0;
		if (lastCommand.movingSnowball != nullptr)
		{
			ballX = lastCommand.movingSnowball->GridX();
			ballY = lastCommand.movingSnowball->GridY();
		}
		newCommand = Command(gridX, gridY, 
							 lastCommand.hiddenSnowball, lastCommand.movingSnowball,
							 ballX, ballY,
							 lastCommand.movingSnowballSize);
		undoCommands.Add(newCommand);
		MovePlayer(lastCommand.moveX, lastCommand.moveY);
		if (lastCommand.movingSnowball != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("TRY UNDO MOVING SNOWBALL"));
			UE_LOG(LogTemp, Warning, TEXT("UNDO MOVING BALL TO: %d, %d"), lastCommand.snowballMoveX, lastCommand.snowballMoveY);
			lastCommand.movingSnowball->Move(lastCommand.snowballMoveX, lastCommand.snowballMoveY);
		}
		if (lastCommand.hiddenSnowball != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("TRY UNDO HIDDEN SNOWBALL"));
			if (lastCommand.hiddenSnowball->IsHidden())
			{
				UE_LOG(LogTemp, Warning, TEXT("REACTIVATE AT: %d, %d"), ballX, ballY);
				lastCommand.hiddenSnowball->ReActivateSnowball(ballX, ballY);
			}
			lastCommand.hiddenSnowball->SetActorHiddenInGame(!lastCommand.hiddenSnowball->IsHidden());
			if (lastCommand.movingSnowball != nullptr)
			{
				lastCommand.movingSnowball->SetActorScale3D(lastCommand.movingSnowballSize - FVector(0.3f, 0.3f, 0.3f));
			}
		}
		currentCommands.Pop();
	}
}

void APlayerCharacter::Redo()
{
	if (undoCommands.Num() >= 1)
	{
		Command newCommand;
		Command lastCommand;
		lastCommand = undoCommands.Last();
		int ballX = 0;
		int ballY = 0;
		if (lastCommand.movingSnowball != nullptr)
		{
			ballX = lastCommand.movingSnowball->GridX();
			ballY = lastCommand.movingSnowball->GridY();
		}
		
		newCommand = Command(gridX, gridY,
							 lastCommand.hiddenSnowball, lastCommand.movingSnowball,
							 ballX, ballY,
							 lastCommand.movingSnowballSize);
		UE_LOG(LogTemp, Warning, TEXT("ADD REDO MOVING BALL: %d, %d"), newCommand.snowballMoveX, newCommand.snowballMoveY);
		
		currentCommands.Add(newCommand);
		MovePlayer(lastCommand.moveX, lastCommand.moveY);
		if (lastCommand.movingSnowball != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRY REDO MOVING SNOWBALL"));
			lastCommand.movingSnowball->Move(lastCommand.snowballMoveX, lastCommand.snowballMoveY);
		}
		if (lastCommand.hiddenSnowball != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRY REDO HIDDEN SNOWBALL"));
			if (lastCommand.hiddenSnowball->IsHidden())
			{
				UE_LOG(LogTemp, Warning, TEXT("REACTIVATE AT: %d, %d"), ballX, ballY);
				lastCommand.hiddenSnowball->ReActivateSnowball(ballX, ballY);
			}
			lastCommand.hiddenSnowball->SetActorHiddenInGame(!lastCommand.hiddenSnowball->IsHidden());
			if (lastCommand.movingSnowball != nullptr)
			{
				lastCommand.movingSnowball->SetActorScale3D(lastCommand.movingSnowballSize + FVector(0.3f, 0.3f, 0.3f));
			}
		}
		undoCommands.Pop();
	}
}

void APlayerCharacter::MovePlayer(int i_x, int i_y)
{
	gridX = i_x;
	gridY = i_y;
	this->SetActorLocation(FVector(100 * i_x, 100 * i_y, 50));
}

bool APlayerCharacter::CheckNextMove(int i_x, int i_y)
{
	if (gridReference != nullptr)
	{
		int x = gridX + i_x;
		int y = gridY + i_y;
		if (x < gridReference->gridSizeY && y < gridReference->gridSizeX && x >= 0 && y >= 0)
		{
			ASnowball* nextGridSnowball = gridReference->GetGrid()[x][y]->GetSnowball();
			if (gridReference->GetGrid()[x][y]->IsBlocked()) 
			{ 
				UE_LOG(LogTemp, Warning, TEXT("BLOCKED!"));
				return false; 
			}
			else if (nextGridSnowball != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("HAS BALL"));
				if (gridReference->CheckSnowball(x, y, i_x, i_y))
				{
					UE_LOG(LogTemp, Warning, TEXT("MOVE BOTH"));
					ASnowball* willHitSnowball = nextGridSnowball->Move(x + i_x , y + i_y);
					UE_LOG(LogTemp, Warning, TEXT("ADD COMMAND: player: %d, %d, snowball: %d, %d"), gridX, gridY, x, y);
					Command newCommand = Command(gridX, gridY, willHitSnowball, nextGridSnowball, x, y, nextGridSnowball->GetActorScale3D());
					currentCommands.Add(newCommand);
					MovePlayer(x, y);
					return true;
				}
				else { return false; }
			}
			else
			{
				//move player
				Command newCommand = Command(gridX, gridY, nullptr, nullptr, 0, 0, FVector().ZeroVector);
				currentCommands.Add(newCommand);
				UE_LOG(LogTemp, Warning, TEXT("ADD COMMAND: %d, %d"), gridX, gridY);
				MovePlayer(x, y);
				return true;
			}
		}
		else 
		{ 
			UE_LOG(LogTemp, Warning, TEXT("OUT OF GRID!"));
			return false; 
		}
	}

	return false;
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

	//TODO: bind U and R
	PlayerInputComponent->BindAction("Undo", IE_Pressed, this, &APlayerCharacter::Undo);
	PlayerInputComponent->BindAction("Redo", IE_Pressed, this, &APlayerCharacter::Redo);
}

