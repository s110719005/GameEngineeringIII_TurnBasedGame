// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPool.h"
#include "Snowball.h"

// Sets default values
ASnowball::ASnowball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ASnowball::CheckCanMove(int i_x, int i_y)
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

ASnowball* ASnowball::Move(int i_x, int i_y)
{
	//if hit another snowball
	ASnowball* snowball = gridReference->GetGrid()[i_x][i_y]->GetSnowball();
	gridReference->RemoveSnowball(gridX, gridY);
	if (snowball != nullptr)
	{
		if (snowball->GetActorScale3D().X > this->GetActorScale3D().X)
		{
			this->SetActorScale3D(snowball->GetActorScale3D());
		}
		snowball->SetActorHiddenInGame(true);
		GrowSnowBall();
	}
	gridX = i_x;
	gridY = i_y;
	gridReference->AddSnowball(gridX, gridY, this);
	this->SetActorLocation(FVector(100 * i_x, 100 * i_y, 50));
	return snowball;
}

void ASnowball::GrowSnowBall()
{
	UE_LOG(LogTemp, Warning, TEXT("GROW"));
	this->SetActorScale3D(this->GetActorScale() + FVector(0.3f, 0.3f, 0.3f));
}

int ASnowball::GridX()
{
	return gridX;
}

int ASnowball::GridY()
{
	return gridY;
}

// Called when the game starts or when spawned
void ASnowball::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorLocation(FVector(100 * gridX, 100 * gridY, 50));
	if (gridActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SEARCHING GRID"));
		gridReference = gridActor->FindComponentByClass<UGridPool>();
		if (gridReference != nullptr)
		{
			gridReference->AddSnowball(gridX, gridY, this);
		}
	}
	
}

// Called every frame
void ASnowball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

