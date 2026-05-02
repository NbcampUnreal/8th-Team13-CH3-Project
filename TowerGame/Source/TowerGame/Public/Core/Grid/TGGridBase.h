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

	UFUNCTION(BlueprintCallable, Category="TowerGame|Grid")
	ATGSingleGrid* GetSingleGridFromPosition(FVector Position);
	ATGSingleGrid* GetSingleGridFromPosition(FVector2D position);
	
protected:
	virtual void BeginPlay() override;
	
	//	각 그리드 크기에 맞게 싱글그리드들을 배치합니다
	//	원점을 전체 그리드 맵의 모서리로 합니다.
	void PlacingGrid();
	
	//	그리드 맵의 크기입니다.
	UPROPERTY(EditDefaultsOnly, Category="TowerGame|Grid")
	int GridRow;
	UPROPERTY(EditDefaultsOnly, Category="TowerGame|Grid")
	int GridCol;
	
	//	각 그리드의 크기입니다
	UPROPERTY(EditDefaultsOnly, Category="TowerGame|Grid")
	float GridSize;
	
	UPROPERTY(VisibleAnywhere, Category="TowerGame|Grid")
	TArray<ATGSingleGrid*> GridActors;
	
};
