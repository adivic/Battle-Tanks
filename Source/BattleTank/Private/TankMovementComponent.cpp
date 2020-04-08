// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack *LeftTrackSet, UTankTrack* RightTrackSet) {

	LeftTrack = LeftTrackSet;
	RightTrack = RightTrackSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack || !RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack || !RightTrack)) return;
	Throw *= 2;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow);
}
