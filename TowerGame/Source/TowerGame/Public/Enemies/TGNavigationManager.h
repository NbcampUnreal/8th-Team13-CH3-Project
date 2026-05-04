// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TGNavigationManager.generated.h"

class ATGCoreBase;
class ATGEnemyBase;

UCLASS()
class TOWERGAME_API ATGNavigationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Unreal LifeCycle
	ATGNavigationManager();
	virtual void BeginPlay() override;

public:
	// 몬스터 등록
	void RegisterEnemy(ATGEnemyBase* Enemy);
	void UnRegisterEnemy(ATGEnemyBase* Enemy);
	
	FVector GetCoreLocation() const;
	
	// 그리드 연동 전 임시 사용 함수
	bool CanPlaceBuildingTemporary(const FVector& BuildLocation) const;
	void NotifyBuildingPlacedTemporary(const FVector& BuildLocation);
	
protected:
	// 목적지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Navigation")
	TObjectPtr<ATGCoreBase> CoreActor;
	
private:
	// 경로 재 탐색
	UPROPERTY()
	TArray<TObjectPtr<ATGEnemyBase>> AliveEnemies;
	
	void RepathAllEnemies();
	
};
