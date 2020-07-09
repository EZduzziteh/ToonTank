// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay() {

	TargetTurrets = GetTargetTurretCount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	HandleGameStart();
	Super::BeginPlay();
}

int32 ATankGameModeBase::GetTargetTurretCount() {
	TSubclassOf<APawnTurret> ClassToFind;
	ClassToFind = APawnTurret::StaticClass();
	TArray<AActor*>TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);
	return TurretActors.Num();
}

void ATankGameModeBase::HandleGameStart() {

	GameStart();
}
void ATankGameModeBase::HandleGameOver(bool PlayerWon) {

	GameOver(PlayerWon);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) {

	if (DeadActor == PlayerTank) {
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
		DestroyedTurret->PawnDestroyed();
		TargetTurrets--;
		if (TargetTurrets <= 0) {
			HandleGameOver(true);
		}
	}
}