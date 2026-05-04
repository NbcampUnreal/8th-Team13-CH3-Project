#include "BaseTower/TGBaseTower.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"

ABaseTower::ABaseTower()
{
	// ������ �������� ������ ƽ�� ��(����ȭ)
	PrimaryActorTick.bCanEverTick = false;

	// ���Ǹ޽�
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	// �渷 (�⺻��)
	BaseMesh->SetCollisionProfileName(TEXT("BlockAll"));

	// ���� ��ġ����
	MountPoint = CreateDefaultSubobject<USceneComponent>(TEXT("MountPoint"));
	MountPoint->SetupAttachment(RootComponent);

	// ť�� ���̿� ���缭 ��ġ ��ġ�� ����(50.f)���� ����
	MountPoint->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
}

void ABaseTower::SetPreviewMode()
{
	// �浹����
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ������ ó��
	DynamicMaterial = BaseMesh->CreateDynamicMaterialInstance(0);

	if (DynamicMaterial)
	{
		// ��Ƽ���� 'Opacity'��� �Ķ���Ͱ� �־�� �۵��մϴ�.
		DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), 0.5f);
	}
}

void ABaseTower::FinalizeInstallation()
{
	// �浹 �ѱ�
	BaseMesh->SetCollisionProfileName(TEXT("BlockAll"));
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// 2. �������ϰ� ����
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), 1.0f);
		//test
	}
}
