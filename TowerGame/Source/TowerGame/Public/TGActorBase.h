// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TGActorBase.generated.h"

UCLASS()
class TOWERGAME_API ATGActorBase : public AActor
{
	GENERATED_BODY()
	
	//	태그 관리 등 틍정 상황에 대비 하기 위한 베이스 액터 클래스입니다.
	//	bCanEverTick 을 생성자에서 false로 변경합니다.
	//	Tick 함수를 사용해야 하는 액터라면 반드시 확인하세요.
	
public:	
	// Sets default values for this actor's properties
	ATGActorBase();
	
};
