// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include"Kismet/GameplayStatics.h"


// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn||ReturnDistanceToPlayer()>FireRange) { return; }

	RotateTurret(PlayerPawn->GetActorLocation());

}

void APawnTurret::CheckFireCondition(){


	if (!PlayerPawn) {return;}//make sure we hav valid player reference

	if (ReturnDistanceToPlayer() <= FireRange) {
		Fire();
	}

	//if player is in range then fire
}
float APawnTurret::ReturnDistanceToPlayer() {
	if (!PlayerPawn) { return 0.0f; } //make sure we hav valid player reference

	float Distance = ((PlayerPawn->GetActorLocation()-GetActorLocation()).Size());
	return Distance;
}

void  APawnTurret::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}