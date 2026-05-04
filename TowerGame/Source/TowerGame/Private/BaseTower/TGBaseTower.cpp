#include "BaseTower/TGBaseTower.h"
#include "Materials/MaterialInstanceDynamic.h"

ABaseTower::ABaseTower()
{
	// 게임플레이 중 기본 틱 비활성화
	PrimaryActorTick.bCanEverTick = false;

	// 베이스 메시
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	// 충돌 (기본값)
	BaseMesh->SetCollisionProfileName(TEXT("BlockAll"));

	// 무기 부착점
	MountPoint = CreateDefaultSubobject<USceneComponent>(TEXT("MountPoint"));
	MountPoint->SetupAttachment(RootComponent);

	// 큐브 높이의 절반 위치로 무기 부착점 이동 (50.f)
	MountPoint->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
}

void ABaseTower::SetPreviewMode()
{
	// 충돌 없음
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 투명도 처리
	DynamicMaterial = BaseMesh->CreateDynamicMaterialInstance(0);

	if (DynamicMaterial)
	{
		// 머티리얼에 'Opacity'라는 파라미터가 있어야 작동합니다.
		DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), 0.5f);
	}
}

void ABaseTower::FinalizeInstallation()
{
	// 충돌 켜기
	BaseMesh->SetCollisionProfileName(TEXT("BlockAll"));
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// 불투명하게 복구
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), 1.0f);
	}
}
