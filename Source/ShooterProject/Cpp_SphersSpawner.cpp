// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpp_SphersSpawner.h"

#include <ctime>

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
	// Checking marked spheres for destroing
	m_spheres.RemoveAll([=](auto sphere) {
			if (sphere->IsActorBeingDestroyed()) { // If marked for destroy, remove from container
				auto dist = FVector::Dist(m_spawnPoint, sphere->GetActorLocation()); // The distance between the spawn point and the center of the sphere

				if (dist <= m_spawnRadiusForNextLevel) { // If the sphere to be destroyed is in radius to pass the level, then we increase the score
					++totalScore; // Increment score
				}

				return true;
			}

			return false;
		});

	// Check the score for passing the level
	CheckTotalLevel();
}

void ACpp_SphersSpawner::OnSpawn()
{
	m_spawnPoint = CharacterPoint; // Set the spawn point at the player’s point
	GenerateNewSpheres(m_spawnCountSpheres, m_startSpawnRadius); // Generate spheres for start game
}

void ACpp_SphersSpawner::GenerateNewSpheres(float newCount, float newRadius, float minDistance)
{
	std::srand(unsigned(std::time(0))); // For std::rand()

	for (int32 i = 0; i < newCount;) {
		float totalRadius = i < 10 ? m_spawnRadiusForNextLevel : newRadius; // Guarantee the presence of 10 spheres in the radius for passing the level

		auto random2DPoint = FMath::RandPointInCircle(totalRadius); // Generate a new random 2D position of the sphere in radius along the XY axes
		// Add the generated position to the FVector and generate additionally along the Z axis
		auto newPoint = FVector(random2DPoint.X, random2DPoint.Y, std::rand() % 240 + 10);
		auto location = m_spawnPoint + newPoint; // Set a new point for the appearance of a sphere
		bool isNewPoint = true; // Correct New Position Flag

		for (auto const &sphere : m_spheres) {
			auto dist = FVector::Dist(newPoint, sphere->GetActorLocation()); // Check for violation of the minimum distance between the spheres

			if (dist < minDistance) { // If the minimum distance is violated, switch the flag to the incorrect position
				isNewPoint = false;
			}
		}

		if (isNewPoint) { // If the new position is correct, generate a new sphere at this point
			SpawnNewSphere(location);
			++i; // Increment "i" for next iteration
		}
	}
}

void ACpp_SphersSpawner::SpawnNewSphere(FVector location)
{
	if (SphereToSpawn) {
		UWorld* const World = GetWorld(); // Get the world

		if (World) {
			auto sphere = World->SpawnActor(SphereToSpawn, &location, &m_rotation); // Generate a new sphere
			m_spheres.Add(sphere); // Add to container
		}
	}
}

void ACpp_SphersSpawner::CheckTotalLevel()
{
	if (totalScore >= totalLevel * 10) { // Check score exceeded or equal to the requirement for a new level
		m_spawnPoint = CharacterPoint; // Save the current player position as a spawn point

		// Generate new spheres with an increment of the radius and the count of spheres for the current level
		// 0.1 - 10% in level increment for count spheres
		// 0.05 - 5% in level increment for radius spawn
		GenerateNewSpheres(m_spawnCountSpheres + m_spawnCountSpheres * totalLevel * 0.1,
							m_startSpawnRadius + m_startSpawnRadius * totalLevel * 0.05);

		++totalLevel; // Increment the current level
	}
}
