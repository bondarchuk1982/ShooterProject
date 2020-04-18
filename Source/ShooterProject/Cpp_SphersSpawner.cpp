// Fill out your copyright notice in the Description page of Project Settings.
#include <ctime>
#include <algorithm>
#include <string>

#include "Cpp_SphersSpawner.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ACpp_SphersSpawner::ACpp_SphersSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACpp_SphersSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACpp_SphersSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_spheres.erase(std::remove_if(m_spheres.begin(), m_spheres.end(),
		[=](auto sphere) {
			if (sphere->IsActorBeingDestroyed()) {
				auto dist = FVector::Dist(m_spawnPoint, sphere->GetActorLocation());

				if (dist <= m_spawnRadius) {
					++totalScore;
				}

				return true;
			}

			return false;
		}), m_spheres.end());

	CheckTotalLevel();
}

void ACpp_SphersSpawner::OnSpawn()
{
	m_spawnPoint = CharacterPoint;
	GenerateNewSpheres(m_spawnCountSpheres, 2000, 80);
}

void ACpp_SphersSpawner::GenerateNewSpheres(float newCount, float newRadius, float minDistance)
{
	std::srand(unsigned(std::time(0)));

	auto radius = static_cast<int>(newRadius);
	auto count = static_cast<int>(newCount);

	for (int32 i = 0; i < count; ++i) {
		int totalRadius = i < 10 ? m_spawnRadius : radius;

		auto random2DPoint = FMath::RandPointInCircle(totalRadius);
		auto newPoint = FVector(random2DPoint.X, random2DPoint.Y, std::rand() % 240 + 10);
		auto location = m_spawnPoint + newPoint;
		bool isNewPoint = true;

		for (auto const &sphere : m_spheres) {
			auto dist = FVector::Dist(newPoint, sphere->GetActorLocation());

			if (dist < minDistance) {
				isNewPoint = false;
			}
		}

		if (isNewPoint) {
			SpawnNewSphere(location);
		}
	}
}

void ACpp_SphersSpawner::SpawnNewSphere(FVector location)
{
	if (SphereToSpawn) {
		UWorld* const World = GetWorld();

		if (World) {
			auto sphere = World->SpawnActor(SphereToSpawn, &location, &m_rotation);
			m_spheres.push_back(sphere);
		}
	}
}

void ACpp_SphersSpawner::CheckTotalLevel()
{
	if (totalScore >= totalLevel * 10) {
		m_spawnPoint = CharacterPoint;
		GenerateNewSpheres(m_spawnCountSpheres + m_spawnCountSpheres * totalLevel * 0.1,
							m_spawnRadius + m_spawnRadius * totalLevel * 0.05, 80);

		++totalLevel;
	}
}
