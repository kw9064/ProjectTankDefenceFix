// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);

	//UFUNCTION(BlueprintImplementableEvent)
	int32 GetTargetEnemyCount();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 EnemyCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	bool DefinitionEnemy;*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 TargetEnemys = 0;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Enemy;
private:
	class ATank* Tank;
	class ATankPlayerController* TankPlayerController;

	//class ACharater* Enemy;

	float StartDelay = 3.0f;

	void HandleGameStart();

	int32 TargetTurrets = 0;
	int32 GetTargetTurretCount();
};
