#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseTower.generated.h"

UCLASS()
class TOWER_API ABaseTower : public AActor
{
	GENERATED_BODY()

public:
	ABaseTower();

	// 벽 몸체 (길막)
	UPROPERTY(VisibleAnywhere, Category = "Tower|Base")
	UStaticMeshComponent* BaseMesh;

	// 무기를 설치할 포인트
	UPROPERTY(VisibleAnywhere, Category = "Tower|Base")
	USceneComponent* MountPoint;

	// 현재 위에 설치된 무기 액터 저장 (필요시 사용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower|Base")
	AActor* AttachedWeapon;

	/** 마우스를 따라다니는 프리뷰 상태 설정 (반투명, 충돌 무시) */
	void SetPreviewMode();

	/** 클릭 시 실제 설치 완료 처리 (불투명, 길막 활성화) */
	void FinalizeInstallation();

protected:
	// 런타임에 투명도를 조절하기 위한 다이나믹 머티리얼 인스턴스
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;
};