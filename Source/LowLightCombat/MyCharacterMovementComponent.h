// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOWLIGHTCOMBAT_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

    friend class FSavedMove_My;
public:
    // Sets sprinting to either enabled or disabled
    UFUNCTION(BlueprintCallable, Category = "My Character Movement")
    void SetSprinting(bool sprinting);

    UFUNCTION(BlueprintCallable, Category = "My Character Movement")
    bool GetSprinting();

    UFUNCTION(BlueprintCallable, Category = "My Character Movement")
    void SetDashing(bool dashing);
     

    UFUNCTION(BlueprintCallable, Category = "My Character Movement")
    bool GetDashing();

    FNetworkPredictionData_Client* GetPredictionData_Client() const;
   // void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
    void  UpdateFromCompressedFlags(uint8 Flags);
    float GetMaxSpeed() const;
    float GetMaxAcceleration() const;
private:
    bool SprintKeyDown = false;
    uint8 WantsToSprint : 1; 	// The ground speed when running
    uint8 WantsToDash : 1;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Character Movement|Grounded", Meta = (AllowPrivateAccess = "true"))
    float RunSpeed = 300.0f;
    // The ground speed when sprinting
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Character Movement|Grounded", Meta = (AllowPrivateAccess = "true"))
    float SprintSpeed = 800.0f;
    // The acceleration when running
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Character Movement|Grounded", Meta = (AllowPrivateAccess = "true"))
    float RunAcceleration = 2000.0f;
    // The acceleration when sprinting
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My Character Movement|Grounded", Meta = (AllowPrivateAccess = "true"))
    float SprintAcceleration = 2000.0f;

};

class FSavedMove_My : public FSavedMove_Character
{
public:

    typedef FSavedMove_Character Super;

    // Resets all saved variables.
    virtual void Clear() override;
    // Store input commands in the compressed flags.
    virtual uint8 GetCompressedFlags() const override;
    // This is used to check whether or not two moves can be combined into one.
    // Basically you just check to make sure that the saved variables are the same.
    virtual bool CanCombineWith(const FSavedMovePtr& NewMovePtr, ACharacter* Character, float MaxDelta) const override;
    // Sets up the move before sending it to the server. 
    virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
    // Sets variables on character movement component before making a predictive correction.
    virtual void PrepMoveFor(class ACharacter* Character) override;

private:
    uint8 SavedWantsToSprint : 1; 
    uint8 SavedWantsToDash : 1;
};


class FNetworkPredictionData_Client_My : public FNetworkPredictionData_Client_Character
{
public:
    typedef FNetworkPredictionData_Client_Character Super;

    // Constructor
    FNetworkPredictionData_Client_My(const UCharacterMovementComponent& ClientMovement);

    //brief Allocates a new copy of our custom saved move
    virtual FSavedMovePtr AllocateNewMove() override;
};