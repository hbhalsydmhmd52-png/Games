#include "SkyfallAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USkyfallAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    const APawn* Pawn = TryGetPawnOwner();
    if (!IsValid(Pawn))
    {
        GroundSpeed = 0.0f;
        Direction = 0.0f;
        bIsInAir = false;
        bIsAccelerating = false;
        bIsMoving = false;
        bShouldMove = false;
        MovementInputAmount = 0.0f;
        Velocity = FVector::ZeroVector;
        return;
    }

    Velocity = Pawn->GetVelocity();
    const FVector HorizontalVelocity(Velocity.X, Velocity.Y, 0.0f);
    GroundSpeed = HorizontalVelocity.Size();
    Direction = CalculateDirection(Velocity, Pawn->GetActorRotation());
    MovementInputAmount = Pawn->GetLastMovementInputVector().Size();
    bIsMoving = GroundSpeed > 3.0f;

    const ACharacter* Character = Cast<ACharacter>(Pawn);
    if (Character)
    {
        const UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
        bIsInAir = Movement ? Movement->IsFalling() : false;
        bIsAccelerating = Movement
            ? !Movement->GetCurrentAcceleration().IsNearlyZero()
            : false;
        bShouldMove = GroundSpeed > 3.0f && MovementInputAmount > 0.05f;
    }
    else
    {
        bIsInAir = false;
        bIsAccelerating = false;
        bShouldMove = bIsMoving;
    }
}
