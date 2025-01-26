// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolGridObject.h"
#include "GridPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TURNBASEDGAME_API UGridPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridPool();

	UFUNCTION(BlueprintCallable, Category = "Object pool")
		APoolGridObject* SpawnPooledObject(UWorld* world);

	UPROPERTY(EditAnywhere, Category = "Object Pool")
	TSubclassOf<class APoolGridObject> pooledObjectSubclass;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	TSubclassOf<class APoolGridObject> pooledObstacleSubclass;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
	int gridSizeX;

	UPROPERTY(EditAnywhere, Category = "Object Pool")
	int gridSizeY;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	float pooledObjectLifeTime = 5.0f;

	UFUNCTION()
	void OnGridHit(APoolGridObject* gridActor);

	TArray<TArray<APoolGridObject*>> GetGrid();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	TArray<APoolGridObject*> ObjectPool;
	TArray<int> SpawnedPoolIndex;
	TArray<TArray<APoolGridObject*>> grid;
	TArray<TArray<APoolGridObject*>> obstacle;
};
