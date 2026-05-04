// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TGPlayer.h"

// Sets default values
ATGPlayer::ATGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

