#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SkyfallAnimInstance.generated.h"

/**
 * Animation data for the SKYFALL locomotion Anim Blueprint.
 * Create an Anim Blueprint based on this class and connect these values
 * to a locomotion State Machine (Idle/Start/Walk/Run/Jump/Fall/Land).
 */
UCLASS(Transient, Blueprintable)
class SKYFALL_API USkyfallAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    float GroundSpeed = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    float Direction = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    bool bIsInAir = false;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    bool bIsAccelerating = false;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    bool bIsMoving = false;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    bool bShouldMove = false;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    float MovementInputAmount = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="SKYFALL|Animation")
    FVector Velocity = FVector::ZeroVector;
};
