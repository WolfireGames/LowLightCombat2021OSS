// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "MyCharacterMovementComponent.h"


// Sets default values
AMyCharacter::AMyCharacter(const class FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UMyCharacterMovementComponent* AMyCharacter::GetMyMovementComponent() const {
	return static_cast<UMyCharacterMovementComponent*>(GetCharacterMovement());
}

FVector AMyCharacter::SeededUnitVectorInConeInRadians(FVector ConeDir, float ConeHalfAngleInRadians, float seed)
{
    if (ConeHalfAngleInRadians > 0.f)
    { 
        int const interval = 1000; 
        unsigned long lfsr = seed; 
        unsigned long bit;
 
        bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
        lfsr = (lfsr >> 1) | (bit << 31);
      
        float const RandU = (lfsr % interval) / 1000.0;
        lfsr = seed * 3;
        bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
        lfsr = (lfsr >> 1) | (bit << 31);
        float const RandV = (lfsr % interval) / 1000.0;
        /*
        float const RandU = testRandU; FMath::FRand();
        float const RandV = testRandV; FMath::FRand();
        */
        // Get spherical coords that have an even distribution over the unit sphere
        // Method described at http://mathworld.wolfram.com/SpherePointPicking.html	
        float Theta = 2.f * PI * RandU;
        float Phi = FMath::Acos((2.f * RandV) - 1.f);

        // restrict phi to [0, ConeHalfAngleRad]
        // this gives an even distribution of points on the surface of the cone
        // centered at the origin, pointing upward (z), with the desired angle
        Phi = FMath::Fmod(Phi, ConeHalfAngleInRadians);

        // get axes we need to rotate around
        FMatrix const DirMat = FRotationMatrix(ConeDir.Rotation());
        // note the axis translation, since we want the variation to be around X
        FVector const DirZ = DirMat.GetScaledAxis(EAxis::X);
        FVector const DirY = DirMat.GetScaledAxis(EAxis::Y);

        FVector Result = ConeDir.RotateAngleAxis(Phi * 180.f / PI, DirY);
        Result = Result.RotateAngleAxis(Theta * 180.f / PI, DirZ);

        // ensure it's a unit vector (might not have been passed in that way)
        Result = Result.GetSafeNormal();

        return Result;
    }
    else
    {
        return ConeDir.GetSafeNormal();
    }
}

