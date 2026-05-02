// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TGActorBase.h"
#include "TGSingleGrid.generated.h"

UCLASS()
class TOWERGAME_API ATGSingleGrid : public ATGActorBase
{
	GENERATED_BODY()
	//	그리드 위에 배치되는 최소 단위 클래스입니다.
	//	개별 칸 관리에 사용됩니다.
public:
	ATGSingleGrid();
	
	
protected:
	
	//	월드에 위치를 표시하기 위한 임시 컴포넌트입니다.
	//	ToDo : 디버깅용 표시 방법이 없어도 될 때 삭제하세요.
	UPROPERTY(EditDefaultsOnly, Category = "TowerGame|Grid")
	TObjectPtr<UStaticMeshComponent> Visualizer;

};
