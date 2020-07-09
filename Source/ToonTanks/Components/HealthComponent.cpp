// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = StartHealth;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();
	if (Owner) {

		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to Owner"));
	}
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {

	if (Damage == 0|| CurrentHealth == 0) { return; }

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, StartHealth);
	if (CurrentHealth <= 0) {
		if (GameModeRef) {
			GameModeRef->ActorDied(Owner);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to GameMode"));
		}
	}
}


