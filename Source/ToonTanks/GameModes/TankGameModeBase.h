// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
class APawnTank;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
private:

	int32 TargetTurrets = 0;
	int32 GetTargetTurretCount();

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"));
	APawnTank* PlayerTank;


public :
	void ActorDied(AActor* DeadActor);
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	
};
