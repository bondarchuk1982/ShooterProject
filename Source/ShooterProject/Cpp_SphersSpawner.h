// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include <vector>

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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
	TSubclassOf<class AActor> SphereToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere spawn")
	FVector CharacterPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sphere spawn")
	int32 totalScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sphere spawn")
	int32 totalLevel = 1;

private:
	void GenerateNewSpheres(float count, float radius, float minDistance);
	void SpawnNewSphere(FVector location);
	void CheckTotalLevel();

	std::vector<AActor*> m_spheres;
	FRotator m_rotation = FRotator::ZeroRotator;
	int32 m_spawnRadius = 1500;
	int32 m_spawnCountSpheres = 15;
	FVector m_spawnPoint;
};
