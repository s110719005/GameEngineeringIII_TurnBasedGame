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
		Command newCommand = Command(gridX, gridY);
		undoCommands.Add(newCommand);
		MovePlayer(currentCommands.Last().moveX, currentCommands.Last().moveY);
		currentCommands.Pop();
	}
}

void APlayerCharacter::Redo()
{
	if (undoCommands.Num() >= 1)
	{
		Command newCommand = Command(gridX, gridY);
		currentCommands.Add(newCommand);
		MovePlayer(undoCommands.Last().moveX, undoCommands.Last().moveY);
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
			if (gridReference->GetGrid()[x][y]->IsBlocked()) 
			{ 
				UE_LOG(LogTemp, Warning, TEXT("BLOCKED!"));
				return false; 
			}
			else
			{
				//move player
				Command newCommand = Command(gridX, gridY);
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

