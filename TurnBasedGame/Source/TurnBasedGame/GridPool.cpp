// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPool.h"

// Sets default values for this component's properties
UGridPool::UGridPool()
{
	
}

APoolGridObject* UGridPool::SpawnPooledObject(UWorld* world)
{
	grid.SetNum(gridSizeY);

	for (int i = 0; i < gridSizeY; i++)
	{
		grid[i].SetNum(gridSizeX);
		for (int j = 0; j < gridSizeX; j++)
		{
			//grid[i][j] = 0;
			APoolGridObject* gridActor = world->SpawnActor<APoolGridObject>(pooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
			
			if (gridActor != nullptr)
			{
				UE_LOG(LogClass, Log, TEXT("GENERATE GRID AT: %d, %d"), i, j);
				gridActor->SetActorLocation(FVector(100 * i, 100 * j, 10));
				gridActor->SetGridIndex(i, j);
				gridActor->OnGridHit.AddDynamic(this, &UGridPool::OnGridHit);
				grid[i][j] = gridActor;
			}
		}
	}
	grid[4][0]->SetIsBlocked(true);
	grid[3][0]->SetIsBlocked(true);
	grid[4][1]->SetIsBlocked(true);
	grid[3][1]->SetIsBlocked(true);
	grid[1][3]->SetIsBlocked(true);
	grid[0][3]->SetIsBlocked(true);
	return nullptr;
}


void UGridPool::OnGridHit(APoolGridObject* gridActor)
{
}

// Called when the game starts
void UGridPool::BeginPlay()
{
	if (pooledObjectSubclass != nullptr)
	{
		UWorld* const World = GetWorld();
		
		if (World != nullptr)
		{
			SpawnPooledObject(World);
		}
	}
}


