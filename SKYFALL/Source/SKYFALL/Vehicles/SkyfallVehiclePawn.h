#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SkyfallVehiclePawn.generated.h"
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class SKYFALL_API ASkyfallVehiclePawn : public APawn
{
    GENERATED_BODY()
public:
    ASkyfallVehiclePawn();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    UFUNCTION(BlueprintCallable, Category="Vehicle") void ResetVehicle();
protected:
    void SetThrottle(float Value);
    void SetSteering(float Value);
    void SetBrake(float Value);
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Vehicle") TObjectPtr<UStaticMeshComponent> VehicleBody;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<USpringArmComponent> CameraBoom;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera") TObjectPtr<UCameraComponent> FollowCamera;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle|Tuning") float EngineForce = 850000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Vehicle|Tuning") float BrakeStrength = 450000.0f;
private:
    float ThrottleInput = 0.0f;
    float SteeringInput = 0.0f;
    float BrakeInput = 0.0f;
    FTransform LastSafeTransform;
};