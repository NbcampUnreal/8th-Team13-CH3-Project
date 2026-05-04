// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/TGWaveManager.h"

#include "Enemies/TGEnemyBase.h"
#include "Enemies/TGEnemySpawner.h"

FTGEnemySpawnInfo::FTGEnemySpawnInfo() : EnemyClass(nullptr), SpawnCount(0)
{
}

FTGWaveInfo::FTGWaveInfo() : SpawnInterval(1.0f), DelayAfterSpawnCompleted(5.0f)
{
}

// Sets default values
ATGWaveManager::ATGWaveManager() 
	: NextWaveIndex(0), 
	ActiveWaveIndex(0), 
	bIsSpawning(false), 
	CurrentSpawnInfoIndex(0), 
	SpawnedCountInCurrentInfo(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool ATGWaveManager::StartNextWave()
{
	if (bIsSpawning) return false;
	
	if (GetWorldTimerManager().IsTimerActive(NextWaveDelayTimerHandle)){
		GetWorldTimerManager().ClearTimer(NextWaveDelayTimerHandle);
	}
	
	if (!EnemySpawner) return  false;
	if (!HasNextWave()) return  false;
	
	// 현재 / 다음 웨이브 정보 갱신
	InitializeSpawnState(NextWaveIndex);
	NextWaveIndex++;
	
	// 웨이브 시작 이벤튼
	OnWaveStarted.Broadcast(ActiveWaveIndex);
	
	if (WaveInfos[ActiveWaveIndex].EnemySpawnInfos.Num() == 0){
		FinishCurrentWaveSpawn();
		return true;
	}
	
	bIsSpawning = true;
	
	// Spawm Timer 시작
	const float Interval = WaveInfos[ActiveWaveIndex].SpawnInterval;
	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ATGWaveManager::SpawnNextEnemy,
		Interval,
		true,
		0
	);
	
	return true;
}

void ATGWaveManager::SpawnNextEnemy()
{
	// 모든 Enemy Spawn이 끝났는가
	FTGWaveInfo& CurrentWave = WaveInfos[ActiveWaveIndex];
	if (!CurrentWave.EnemySpawnInfos.IsValidIndex(CurrentSpawnInfoIndex)){
		FinishCurrentWaveSpawn();
		return;
	}
	
	// SpawnInfo에서 지정된 수만큼 생성되었는가
	FTGEnemySpawnInfo& SpawnInfo = CurrentWave.EnemySpawnInfos[CurrentSpawnInfoIndex];
	if (SpawnedCountInCurrentInfo >= SpawnInfo.SpawnCount){
		if (!MoveToNextSpawnInfo()){
			FinishCurrentWaveSpawn();
		}
		return;
	}
	
	// 해당 Enemy가 비어 있는가
	if (!SpawnInfo.EnemyClass){
		if (!MoveToNextSpawnInfo()){
			FinishCurrentWaveSpawn();
		}
		return;
	}
	
	// Enemy 생성
	ATGEnemyBase* SpawnEnemy = EnemySpawner->SpawnEnemy(SpawnInfo.EnemyClass);
	if (SpawnEnemy) SpawnedCountInCurrentInfo++;
}

bool ATGWaveManager::MoveToNextSpawnInfo()
{
	// Enemy 생성에 사용할 인자 초기화
	CurrentSpawnInfoIndex++;
	SpawnedCountInCurrentInfo = 0;
	
	return WaveInfos[ActiveWaveIndex].EnemySpawnInfos.IsValidIndex(CurrentSpawnInfoIndex);
}

void ATGWaveManager::FinishCurrentWaveSpawn()
{
	// Timer 정리
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	
	// 현재 웨이브 종료 처리
	bIsSpawning = false;
	const bool bCanStartNextWave = HasNextWave();
	
	// Wave Spawn 종료 이벤트 
	OnWaveSpawnCompleted.Broadcast(ActiveWaveIndex, bCanStartNextWave);
	
	if (!bCanStartNextWave) return;
	
	// 웨이브 대기 시간 적용
	const float Delay = WaveInfos[ActiveWaveIndex].DelayAfterSpawnCompleted;
	GetWorldTimerManager().SetTimer(
		NextWaveDelayTimerHandle, 
		this,
		&ATGWaveManager::HandleNextWaveDelayFinished,
		Delay,
		false
	);
}

void ATGWaveManager::HandleNextWaveDelayFinished()
{
	StartNextWave();
}

void ATGWaveManager::InitializeSpawnState(int32 WaveIndex)
{
	// 새 웨이브 스폰 시작 상태 설정
	ActiveWaveIndex = WaveIndex;
	CurrentSpawnInfoIndex = 0;
	SpawnedCountInCurrentInfo = 0;
}

bool ATGWaveManager::HasNextWave() const
{
	return WaveInfos.IsValidIndex(NextWaveIndex);
}