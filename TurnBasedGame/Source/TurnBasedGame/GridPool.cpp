// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPool.h"

// Sets default values for this component's properties
UGridPool::UGridPool()
{
	
}

APoolGridObject* UGridPool::SpawnPooledObject(UWorld* world)
{
	grid.SetNum(gridSizeY);
	obstacle.SetNum(gridSizeY);

	for (int i = 0; i < gridSizeY; i++)
	{
		grid[i].SetNum(gridSizeX);
		obstacle[i].SetNum(gridSizeX);
		for (int j = 0; j < gridSizeX; j++)
		{
			//grid[i][j] = 0;
			APoolGridObject* gridActor = world->SpawnActor<APoolGridObject>(pooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
			APoolGridObject* obstacleActor = world->SpawnActor<APoolGridObject>(pooledObstacleSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
			
			if (gridActor != nullptr)
			{
				UE_LOG(LogClass, Log, TEXT("GENERATE GRID AT: %d, %d"), i, j);
				gridActor->SetActorLocation(FVector(100 * i, 100 * j, 10));
				gridActor->SetGridIndex(i, j);
				gridActor->OnGridHit.AddDynamic(this, &UGridPool::OnGridHit);
				grid[i][j] = gridActor;

				obstacleActor->SetActorLocation(FVector(100 * i, 100 * j, 10));
				obstacleActor->SetGridIndex(i, j);
				obstacleActor->SetActive(false);
				obstacle[i][j] = obstacleActor;
			}
		}
	}
	grid[4][0]->SetIsBlocked(true);
	grid[3][0]->SetIsBlocked(true);
	grid[4][1]->SetIsBlocked(true);
	grid[3][1]->SetIsBlocked(true);
	grid[1][3]->SetIsBlocked(true);
	grid[0][3]->SetIsBlocked(true);
	grid[4][0]->SetActive(false);
	grid[3][0]->SetActive(false);
	grid[4][1]->SetActive(false);
	grid[3][1]->SetActive(false);
	grid[1][3]->SetActive(false);
	grid[0][3]->SetActive(false);
	obstacle[4][0]->SetActive(true);
	obstacle[3][0]->SetActive(true);
	obstacle[4][1]->SetActive(true);
	obstacle[3][1]->SetActive(true);
	obstacle[1][3]->SetActive(true);
	obstacle[0][3]->SetActive(true);
	return nullptr;
}


void UGridPool::OnGridHit(APoolGridObject* gridActor)
{
}

TArray<TArray<APoolGridObject*>> UGridPool::GetGrid()
{
	return grid;
}

void UGridPool::AddSnowball(int i_x, int i_y, ASnowball* i_snowball)
{
	grid[i_x][i_y]->SetSnowball(i_snowball);
}

void UGridPool::RemoveSnowball(int i_x, int i_y)
{
	grid[i_x][i_y]->SetSnowball(nullptr);
}

bool UGridPool::CheckSnowball(int i_x, int i_y, int i_moveX, int i_moveY)
{
	if (grid[i_x][i_y]->GetSnowball() != nullptr)
	{
		return grid[i_x][i_y]->GetSnowball()->CheckCanMove(i_moveX, i_moveY);
	}
	return false;
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


