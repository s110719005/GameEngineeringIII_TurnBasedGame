// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Snowball.generated.h"

class UGridPool;

UENUM(BluePrintType)
enum class SnowballSize : uint8
{
	small = 0 UMETA(DisplayName = "Small"),
	medium = 1 UMETA(DisplayName = "Medium"),
	large = 2 UMETA(DisplayName = "Large")
};

UCLASS()
class TURNBASEDGAME_API ASnowball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnowball();
	bool CheckCanMove(int i_x, int i_y);
	ASnowball* Move(int i_x, int i_y);
	void GrowSnowBall();
	int GridX();
	int GridY();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Snowball")
	int gridX;
	UPROPERTY(EditAnywhere, Category = "Snowball")
	int gridY;
	UPROPERTY(EditAnywhere, Category = "Snowball")
	SnowballSize size;

	UPROPERTY(EditAnywhere, Category = "Grid")
	AActor* gridActor;

	UGridPool* gridReference;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
