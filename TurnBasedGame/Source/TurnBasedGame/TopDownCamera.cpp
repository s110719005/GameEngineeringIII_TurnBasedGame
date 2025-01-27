// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCamera.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATopDownCamera::ATopDownCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//ME: Set up camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDown Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ATopDownCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

