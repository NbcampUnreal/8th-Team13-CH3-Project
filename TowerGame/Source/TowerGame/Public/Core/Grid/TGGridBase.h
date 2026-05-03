// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TGActorBase.h"
#include "TGGridBase.generated.h"

class ATGSingleGrid;

UCLASS()
class TOWERGAME_API ATGGridBase : public ATGActorBase
{
	GENERATED_BODY()
	//	월드에 배치되는 그리드 관리 클래스입니다.
public:
	ATGGridBase();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="TowerGame|Grid")
	ATGSingleGrid* GetSingleGridFromPosition(const FVector Position);
	ATGSingleGrid* GetSingleGridFromPosition(const FVector2D Position);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="TowerGame|Grid")
	FIntPoint GetPointFromPosition(const FVector Position) const;
	FIntPoint GetPointFromPosition(const FVector2D Position) const;

	UFUNCTION(BlueprintCallable, Category="TowerGame|Grid")
	bool CanBePlacedBuilding(FIntPoint Point);

	UFUNCTION(BlueprintCallable, Category="TowerGame|Grid")
	void PlacingBuilding(FIntPoint Point);

protected:
	virtual void BeginPlay() override;

	//	각 그리드 크기에 맞게 싱글그리드들을 배치합니다
	//	원점을 전체 그리드 맵의 모서리로 합니다.
	void PlacingGrid();

	//	그리드 맵의 X축 칸 수입니다.
	UPROPERTY(EditDefaultsOnly, Category="TowerGame|Grid")
	int GridX;
	//	그리드 맵의 Y축 칸 수입니다.
	UPROPERTY(EditDefaultsOnly, Category="TowerGame|Grid")
	int GridY;

	//	각 그리드의 크기입니다
	UPROPERTY(EditDefaultsOnly, Category="TowerGame|Grid")
	float GridSize;

private:
	
	bool PathFinding();
	
	TArray<TArray<bool>> bBuildingPlaced;
	TArray<TArray<ATGSingleGrid*>> GridActors;
	TSet<FIntPoint> EntryPoints;
	TSet<FIntPoint> ExitPoints;

};
