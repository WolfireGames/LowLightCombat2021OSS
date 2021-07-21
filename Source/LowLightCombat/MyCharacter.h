// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


class UMyCharacterMovementComponent;

UCLASS(Blueprintable)
class LOWLIGHTCOMBAT_API AMyCharacter : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Movement")
	UMyCharacterMovementComponent* GetMyMovementComponent() const;


    UFUNCTION(BlueprintPure, Category = "Math|Random", meta = (NotBlueprintThreadSafe))
    static FVector SeededUnitVectorInConeInRadians(FVector ConeDir, float ConeHalfAngleInRadians, float seed);
};
