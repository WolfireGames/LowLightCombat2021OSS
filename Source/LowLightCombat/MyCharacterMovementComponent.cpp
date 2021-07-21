// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterMovementComponent.h"
#include "MyCharacter.h"

void UMyCharacterMovementComponent::SetSprinting(bool sprinting) 
{
    WantsToSprint = sprinting;
}
 
bool UMyCharacterMovementComponent::GetSprinting()
{
	return WantsToSprint;
}

void UMyCharacterMovementComponent::SetDashing(bool dashing)
{
	WantsToDash = dashing;
}
 

bool UMyCharacterMovementComponent::GetDashing()
{
	return WantsToDash;
}

FNetworkPredictionData_Client* UMyCharacterMovementComponent::GetPredictionData_Client() const
{
   
    if (ClientPredictionData == nullptr)
    {
        // Return our custom client prediction class instead
        UMyCharacterMovementComponent* MutableThis = const_cast<UMyCharacterMovementComponent*>(this);
        MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_My(*this);
    }

    return ClientPredictionData;
} 

float UMyCharacterMovementComponent::GetMaxSpeed() const
{ 
    switch (MovementMode)
    {
    case MOVE_Walking:
    case MOVE_NavWalking:
    {
        if (IsCrouching())
        {
            return MaxWalkSpeedCrouched;
        }
        else
        {
            if (WantsToSprint)
            {
                return SprintSpeed;
            }
			 

            return RunSpeed;
        }
    }
    case MOVE_Falling:
        return RunSpeed;
    case MOVE_Swimming:
        return MaxSwimSpeed;
    case MOVE_Flying:
        return MaxFlySpeed;
    case MOVE_Custom:
        return MaxCustomMovementSpeed;
    case MOVE_None:
    default:
        return 0.f;
    }
}

float UMyCharacterMovementComponent::GetMaxAcceleration() const
{
	if (IsMovingOnGround()) 
	{
		if (WantsToSprint) 
		{
			return SprintAcceleration;
		}

		return RunAcceleration;
	}

	return Super::GetMaxAcceleration();
}

void UMyCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	WantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	WantsToDash = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
}

void FSavedMove_My::Clear()
{
	Super::Clear();

	// Clear all values
	SavedWantsToSprint = 0; 
	SavedWantsToDash = 0;
}

uint8 FSavedMove_My::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	/* There are 4 custom move flags for us to use. Below is what each is currently being used for:
	FLAG_Custom_0		= 0x10, // Sprinting
	FLAG_Custom_1		= 0x20, // Firing
	FLAG_Custom_2		= 0x40, // Unused
	FLAG_Custom_3		= 0x80, // Unused
	*/

	// Write to the compressed flags 
	if (SavedWantsToSprint)
		Result |= FLAG_Custom_0; 

	if (SavedWantsToDash)
		Result |= FLAG_Custom_1;

	return Result;
}

bool FSavedMove_My::CanCombineWith(const FSavedMovePtr& NewMovePtr, ACharacter* Character, float MaxDelta) const
{
	const FSavedMove_My* NewMove = static_cast<const FSavedMove_My*>(NewMovePtr.Get());

	// As an optimization, check if the engine can combine saved moves.
    if (SavedWantsToSprint != NewMove->SavedWantsToSprint)
	{
		return false;
	}

	return Super::CanCombineWith(NewMovePtr, Character, MaxDelta);
}

void FSavedMove_My::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UMyCharacterMovementComponent* charMov = static_cast<UMyCharacterMovementComponent*>(Character->GetCharacterMovement());
	if (charMov)
	{
		// Copy values into the saved move
		SavedWantsToSprint = charMov->WantsToSprint; 
		SavedWantsToDash = charMov->WantsToDash;
	}
}

void FSavedMove_My::PrepMoveFor(class ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	UMyCharacterMovementComponent* charMov = Cast<UMyCharacterMovementComponent>(Character->GetCharacterMovement());
	if (charMov)
	{
		// Copt values out of the saved move
		charMov->WantsToSprint = SavedWantsToSprint; 
		charMov->WantsToDash = SavedWantsToDash;
	}
}

FNetworkPredictionData_Client_My::FNetworkPredictionData_Client_My(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}

FSavedMovePtr FNetworkPredictionData_Client_My::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_My());
}