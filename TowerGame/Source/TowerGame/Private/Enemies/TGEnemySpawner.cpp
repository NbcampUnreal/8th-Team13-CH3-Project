// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/TGEnemySpawner.h"

#include "EngineUtils.h"
#include "Enemies/TGEnemyBase.h"
#include "Enemies/TGNavigationManager.h"

// Sets default values
ATGEnemySpawner::ATGEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

ATGEnemyBase* ATGEnemySpawner::SpawnEnemy(TSubclassOf<ATGEnemyBase> EnemyClass)
{
	if (!EnemyClass) return nullptr;
	
	UWorld* World = GetWorld();
	if (!World) return nullptr;
	
	if (!NavigationManager)
	{
		// NavigationManager 탐색
		for (TActorIterator<ATGNavigationManager> It(World); It; ++It){
			NavigationManager = *It;
			break;
		}
		
		// NavigationManager 탐색 실패
		if (!NavigationManager){
			UE_LOG(LogTemp, Error, TEXT("NavigationManger을 찾지 못했습니다"));
			return nullptr;
		}
		
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	
	// Enemy 생성
	ATGEnemyBase* SpawnEnemy = GetWorld()->SpawnActor<ATGEnemyBase>(
		EnemyClass, GetActorTransform(), SpawnParams);
	
	if (!SpawnEnemy) return nullptr;
	
	// Observer System 등록
	SpawnEnemy->InitializeEnemy(NavigationManager);
	
	return SpawnEnemy;
}


