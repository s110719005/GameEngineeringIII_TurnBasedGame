// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolGridObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridHit, APoolGridObject*, PoolActor);


UCLASS()
class TURNBASEDGAME_API APoolGridObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolGridObject();

	FOnGridHit OnGridHit;

	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetGridIndex(int x, int y);
	void SetIsBlocked(bool i_isBlocked);
	void CheckGrid();

	bool IsActive();
	bool IsBlocked();
	int GetGridIndexX();
	int GetGridIndexY();


protected:
	bool isActive;
	float lifeSpan = 0.0f;
	UPROPERTY(VisibleAnywhere, Category = "Grid")
	bool isBlocked;
	UPROPERTY(VisibleAnywhere, Category = "Grid")
	int gridX;
	UPROPERTY(VisibleAnywhere, Category = "Grid")
	int gridY;


	//FTimerHandel LifeSpanTimer;

};
