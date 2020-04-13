// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterProjectSphere.h"

// Sets default values
AShooterProjectSphere::AShooterProjectSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterProjectSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterProjectSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

