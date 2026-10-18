#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkyfallCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SKYFALL_API ASkyfallCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ASkyfallCharacter();
protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void TurnCamera(float Value);
    void LookCamera(float Value);
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<USpringArmComponent> CameraBoom;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<UCameraComponent> FollowCamera;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controls", meta=(ClampMin="0.1", ClampMax="5.0")) float LookSensitivity = 1.0f;
};