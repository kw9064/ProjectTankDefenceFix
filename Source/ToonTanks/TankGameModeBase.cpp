// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "TankPlayerController.h"

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		--TargetTurrets;
		if (TargetTurrets == 0)
		{
			if (TargetEnemys == 0)
			{
				GameOver(true);

			}
		}
	}
	else if (DeadActor)
	{
		--TargetEnemys;
		UE_LOG(LogTemp, Warning, TEXT("%d"), TargetEnemys);
		if (TargetTurrets == 0)
		{
			if (TargetEnemys == 0)
			{
				GameOver(true);

			}
		}
	}
}

int32 ATankGameModeBase::GetTargetEnemyCount()
{
	TArray<AActor*> Enemys;
	UGameplayStatics::GetAllActorsOfClass(this, Enemy, Enemys);
	UE_LOG(LogTemp, Warning, TEXT("%d"), (int32)Enemys.Num());

	return Enemys.Num();
}


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();

}

void ATankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
	TargetEnemys = GetTargetEnemyCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (TankPlayerController)
	{
		TankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			TankPlayerController,
			&ATankPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}

}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
	return Turrets.Num();
}
