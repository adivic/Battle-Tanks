// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "BattleTank/BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

 void ATankAIController::Tick(float DeltaSeconds) {
	 Super::Tick(DeltaSeconds);

	 auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	 auto ControlledTank = Cast<ATank>(GetPawn());

	 if (ensure(PlayerTank)) {
		 //Move towords the player
		 MoveToActor(PlayerTank, AcceptanceRadius);
		 //Aim towords the player

		 ControlledTank->AimAt(PlayerTank->GetActorLocation());
		 
		 // Fire if ready
		 ControlledTank->Fire();
	 }
}
