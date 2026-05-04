// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/TGEnemyBase.h"

#include "Enemies/TGEnemyAIController.h"
#include "Enemies/TGNavigationManager.h"

// Sets default values
ATGEnemyBase::ATGEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	AIControllerClass = ATGEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATGEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// NavigationManger 등록 해제
	if (NavigationManager)
	{
		NavigationManager->UnRegisterEnemy(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

void ATGEnemyBase::InitializeEnemy(ATGNavigationManager* InNavigationManager)
{
	if (!InNavigationManager) return;
	
	// Enemy 등록
	UE_LOG(LogTemp, Warning, TEXT("네비게이션 등록"));
	NavigationManager = InNavigationManager;
	NavigationManager->RegisterEnemy(this);
	
	// 경로 탐색
	RequestRepath();
}

void ATGEnemyBase::RequestRepath()
{
	if (!NavigationManager) return;
	
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController) return; 
	
	// 목적지 위치 get
	const FVector CoreLocation = NavigationManager->GetCoreLocation();
	
	//목적지로 이동
	AIController->MoveToLocation(CoreLocation);
}

void ATGEnemyBase::SetNavigationManager(ATGNavigationManager* InNavigationManager)
{
	NavigationManager = InNavigationManager;
}


