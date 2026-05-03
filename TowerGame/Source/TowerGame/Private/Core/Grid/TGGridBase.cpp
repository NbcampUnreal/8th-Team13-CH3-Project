// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Grid/TGGridBase.h"
#include "Core/Grid/TGSingleGrid.h"


ATGGridBase::ATGGridBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

ATGSingleGrid* ATGGridBase::GetSingleGridFromPosition(const FVector Position)
{
	FVector2D Pos = FVector2D(Position.X, Position.Y);
	return GetSingleGridFromPosition(Pos);
}

ATGSingleGrid* ATGGridBase::GetSingleGridFromPosition(const FVector2D Position)
{
	int X = Position.X / GridSize;
	int Y = Position.Y / GridSize;
	if (X < 0 || X >= GridX || Y < 0 || Y >= GridY)	return nullptr;

	return GridActors[Y][X];
}

FIntPoint ATGGridBase::GetPointFromPosition(const FVector Position) const
{
	FVector2D Pos = FVector2D(Position.X, Position.Y);
	return GetPointFromPosition(Pos);
}

FIntPoint ATGGridBase::GetPointFromPosition(const FVector2D Position) const
{
	int X = Position.X / GridSize;
	int Y = Position.Y / GridSize;
	if (X < 0) X = 0;
	else if (X >= GridX) X = GridX - 1;
	if (Y < 0) Y = 0;
	else if (Y >= GridY) Y = GridY - 1;
	return FIntPoint(X, Y);
}

bool ATGGridBase::CanBePlacedBuilding(FIntPoint Point)
{
	bBuildingPlaced[Point.Y][Point.X] = true;

	//	1. 진입점이 막혀있으면 안됨
	//	2. 도착점이 막혀있으면 안됨
	bool bBlocked = true;
	for (int32 i = 0; i < GridX; i++)
	{
		if (!bBuildingPlaced[0][i])
		{
			bBlocked = false;
			break;
		}
		else if (!bBuildingPlaced[GridY - 1][i])
		{
			bBlocked = false;
			break;
		}
	}

	if (bBlocked)
	{	//	진입점 또는 진출점이 막히게 됨
		bBuildingPlaced[Point.Y][Point.X] = false;
		return false;
	}

	//	3. 경로가 막혀있으면 안됨
	if (!PathFinding())
	{
		bBuildingPlaced[Point.Y][Point.X] = false;
		return false;
	}

	return true;
}

void ATGGridBase::PlacingBuilding(FIntPoint Point)
{
	bBuildingPlaced[Point.Y][Point.X] = true;

	if (Point.Y == 0)
	{
		EntryPoints.Remove(Point);
	}
	if (Point.Y == GridY - 1)
	{
		ExitPoints.Remove(Point);
	}
}

void ATGGridBase::BeginPlay()
{
	Super::BeginPlay();

	GridActors.SetNum(GridY);
	bBuildingPlaced.SetNum(GridY);
	for (int32 i = 0; i < GridY; i++)
	{
		GridActors[i].Reserve(GridX);
		bBuildingPlaced[i].Reserve(GridX);
		for (int32 j = 0; j < GridX; j++)
		{
			ATGSingleGrid* NewGrid = GetWorld()->SpawnActor<ATGSingleGrid>();
			GridActors[i].Add(NewGrid);
			bBuildingPlaced[i].Add(false);
		}
	}
	PlacingGrid();
}

void ATGGridBase::PlacingGrid()
{
	FVector OriginPos = GetActorLocation();

	for (int32 i = 0; i < GridY; i++)
	{
		for (int32 j = 0; j < GridX; j++)
		{
			ATGSingleGrid* SingleGrid = GridActors[i][j];
			FVector GridPos = OriginPos;
			GridPos.X += (GridSize * j) + (GridSize / 2);
			GridPos.Y += (GridSize * i) + (GridSize / 2);
			SingleGrid->SetActorLocation(GridPos);
			if (i == 0)
			{	//	진입점
				EntryPoints.Add(FIntPoint(j, i));
			}
			else if (i == GridY - 1)
			{	//	진출점
				ExitPoints.Add(FIntPoint(j, i));
			}
		}
	}
}

bool ATGGridBase::PathFinding()
{	//	경로간 비용이 없으므로 BFS로 패스파인딩
	//	맵이 과도하게 커질 경우 비효율 적일 수 있으나 현재 수준에선 적절하다고 판단됨
	//	방문 배열 생성
	TArray<TArray<bool>> Visited;
	Visited.SetNum(GridY);
	for (int32 i = 0; i < GridY; i++)
	{
		Visited[i].Init(false, GridX);
	}

	//	모든 열린 진입점을 동시에 출발점으로 추가 (멀티소스 BFS)
	TArray<FIntPoint> Queue;	//	탐색큐
	for (const FIntPoint& Entry : EntryPoints)
	{
		if (!bBuildingPlaced[Entry.Y][Entry.X])
		{
			Visited[Entry.Y][Entry.X] = true;
			Queue.Add(Entry);
		}
	}

	//	탐색 방향
	const int32 DX[] = { 1, -1, 0, 0 };
	const int32 DY[] = { 0, 0, 1, -1 };

	for (int32 Head = 0; Head < Queue.Num(); Head++)
	{	
		const FIntPoint Current = Queue[Head];

		if (ExitPoints.Contains(Current))
		{	//	탐색큐의 위치가 도착점
			return true;
		}

		//	각 방향 확인
		for (int32 d = 0; d < 4; d++)
		{
			const int32 NX = Current.X + DX[d];
			const int32 NY = Current.Y + DY[d];

			//	인덱스 벗어남
			if (NX < 0 || NX >= GridX || NY < 0 || NY >= GridY) continue;
			//	이미 방문 or 막힌 곳
			if (Visited[NY][NX] || bBuildingPlaced[NY][NX]) continue;

			//	방문한 위치는 큐에 넣기
			Visited[NY][NX] = true;
			Queue.Add(FIntPoint(NX, NY));
		}
	}

	//	탐색 완료 했으나 길찾기 실패
	return false;
}
