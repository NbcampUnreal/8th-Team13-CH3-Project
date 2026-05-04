#include "BaseTower.h"
#include "Materials/MaterialInstanceDynamic.h"

ABaseTower::ABaseTower()
{
	// 발판은 움직이지 않으니 틱을 끔(최적화)
	PrimaryActorTick.bCanEverTick = false;

	// 발판메시
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	// 길막 (기본값)
	BaseMesh->SetCollisionProfileName(TEXT("BlockAll"));

	// 무기 설치지점
	MountPoint = CreateDefaultSubobject<USceneComponent>(TEXT("MountPoint"));
	MountPoint->SetupAttachment(RootComponent);

	// 큐브 높이에 맞춰서 설치 위치를 윗면(50.f)으로 고정
	MountPoint->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
}

void ABaseTower::SetPreviewMode()
{
	// 충돌끄기
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 반투명 처리
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

	// 2. 불투명하게 복구
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), 1.0f);
	}
}