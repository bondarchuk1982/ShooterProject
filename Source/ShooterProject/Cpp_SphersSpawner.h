// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "Engine/Public/EngineUtils.h"

#include "Cpp_SphersSpawner.generated.h"

UCLASS()
class SHOOTERPROJECT_API ACpp_SphersSpawner : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACpp_SphersSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Sphere spawn")
	void OnSpawn();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere spawn")
	TSubclassOf<class AActor> SphereToSpawn; // Actor for spawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere spawn")
	FVector CharacterPoint; // Player location

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sphere spawn")
	int32 totalScore = 0; // Variable for read total score 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sphere spawn")
	int32 totalLevel = 1; // Variable for read total level

private:
	// 80 - minimum distance between spheres
	void GenerateNewSpheres(float count, float radius, float minDistance = 80.0);
	void SpawnNewSphere(FVector location);
	void CheckTotalLevel();

	TArray<AActor*> m_spheres; // Conteiner for all spheres
	FRotator m_rotation = FRotator::ZeroRotator; // For spheres not need rotation, so using ZeroRotator
	int32 m_startSpawnRadius = 2000; // Maximum radius for start spawn spheres
	int32 m_spawnRadiusForNextLevel = 1500; // Radiuse for passing the level
	int32 m_spawnCountSpheres = 15; // Count spheres for start game
	FVector m_spawnPoint; // The position around which spheres are spawned
};
