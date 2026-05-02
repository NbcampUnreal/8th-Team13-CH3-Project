// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Grid/TGSingleGrid.h"

ATGSingleGrid::ATGSingleGrid()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	//	ToDo : 헤더를 확인하고 삭제해야 할 때. 함께 삭제해주세요
	Visualizer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Visualizer->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh.Succeeded())
	{
		Visualizer->SetStaticMesh(CubeMesh.Object);
	}
	//	ToDoEnd
	
}
