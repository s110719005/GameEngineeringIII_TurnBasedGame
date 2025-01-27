// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopDownCamera.generated.h"

UCLASS()
class TURNBASEDGAME_API ATopDownCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATopDownCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//ME: SerializedField
	//ME: Also can use (VisableAnuwhere) : Readonly, or (EditAnyehere, BlueprintReadWrite)
	UPROPERTY(EditAnywhere); 
	class UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
