// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Grid/TGGridBase.h"
#include "Core/Grid/TGSingleGrid.h"


ATGGridBase::ATGGridBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

ATGSingleGrid* ATGGridBase::GetSingleGridFromPosition(FVector Position)
{
	FVector2D pos = FVector2D(Position.X, Position.Y);
	return GetSingleGridFromPosition(pos);
}

ATGSingleGrid* ATGGridBase::GetSingleGridFromPosition(FVector2D position)
{
	int row = position.X / GridSize;
	int col = position.Y / GridSize;
	if (row < 0 || row >= GridRow || col < 0 || col >= GridCol)	return nullptr;
	
	return GridActors[row * GridCol + col];
}

void ATGGridBase::BeginPlay()
{
	Super::BeginPlay();

	GridActors.Reserve(GridRow * GridCol);
	for (int32 i = 0; i < GridRow * GridCol; i++)
	{
		ATGSingleGrid* NewGrid = GetWorld()->SpawnActor<ATGSingleGrid>();
		GridActors.Add(NewGrid);
	}
	PlacingGrid();
}

void ATGGridBase::PlacingGrid()
{
	FVector OriginPos = GetActorLocation();
	
	for (int32 i = 0; i < GridCol; i++)
	{
		for (int32 j = 0; j < GridRow; j++)
		{
			ATGSingleGrid* SingleGrid = GridActors[j * GridCol + i];
			FVector GridPos = OriginPos;
			GridPos.X += (GridSize * j) + (GridSize / 2);
			GridPos.Y += (GridSize * i) + (GridSize / 2);
			SingleGrid->SetActorLocation(GridPos);
		}
	}
}

