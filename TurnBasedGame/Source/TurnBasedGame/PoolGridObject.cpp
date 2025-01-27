// Fill out your copyright notice in the Description page of Project Settings.


#include "GridPool.h"
#include "PoolGridObject.h"

// Sets default values
APoolGridObject::APoolGridObject()
{
	isBlocked = false;
}

void APoolGridObject::SetActive(bool i_isActive)
{
	isActive = i_isActive;
	SetActorHiddenInGame(!i_isActive);
}

void APoolGridObject::SetLifeSpan(float i_lifeTime)
{
	lifeSpan = i_lifeTime;
}

void APoolGridObject::SetGridIndex(int x, int y)
{
	gridX = x;
	gridY = y;
}

void APoolGridObject::SetIsBlocked(bool i_isBlocked)
{
	isBlocked = i_isBlocked;
}

void APoolGridObject::CheckGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("CHECK GRID"));
	OnGridHit.Broadcast(this);
}

void APoolGridObject::SetSnowball(ASnowball* i_snowball)
{
	//UE_LOG(LogTemp, Warning, TEXT("SET SNOWBALL"));
	snowball = i_snowball;
}

ASnowball* APoolGridObject::GetSnowball()
{
	return snowball;
}

bool APoolGridObject::IsActive()
{
	return isActive;
}

bool APoolGridObject::IsBlocked()
{
	return isBlocked;
}

int APoolGridObject::GetGridIndexX()
{
	return gridX;
}

int APoolGridObject::GetGridIndexY()
{
	return gridY;
}


