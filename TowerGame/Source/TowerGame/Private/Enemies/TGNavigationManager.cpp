// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/TGNavigationManager.h"

#include "Enemies/TGCoreBase.h"
#include "Enemies/TGEnemyBase.h"

// Sets default values
ATGNavigationManager::ATGNavigationManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATGNavigationManager::BeginPlay()
{
	Super::BeginPlay();
}

void ATGNavigationManager::RegisterEnemy(ATGEnemyBase* Enemy)
{
	if (!Enemy) return;

	AliveEnemies.AddUnique(Enemy);
}

void ATGNavigationManager::UnRegisterEnemy(ATGEnemyBase* Enemy)
{
	if (!Enemy) return;

	AliveEnemies.Remove(Enemy);
}

FVector ATGNavigationManager::GetCoreLocation() const
{
	if (!CoreActor)
	{
		return FVector::ZeroVector;
	}
	
	return CoreActor->GetActorLocation();
}

bool ATGNavigationManager::CanPlaceBuildingTemporary(const FVector& BuildLocation) const
{
	return true;
}

void ATGNavigationManager::NotifyBuildingPlacedTemporary(const FVector& BuildLocation)
{
	RepathAllEnemies();
}

void ATGNavigationManager::RepathAllEnemies()
{
	for (ATGEnemyBase* Enemy: AliveEnemies)
	{
		if (!Enemy) continue;
		
		Enemy->RequestRepath();
	}
}

