#include "SkyfallVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

ASkyfallVehiclePawn::ASkyfallVehiclePawn()
{
    PrimaryActorTick.bCanEverTick = true;
    VehicleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
    SetRootComponent(VehicleBody);
    VehicleBody->SetSimulatePhysics(true);
    VehicleBody->SetCollisionProfileName(TEXT("PhysicsActor"));
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(VehicleBody);
    CameraBoom->TargetArmLength = 650.0f;
    CameraBoom->SetRelativeLocation(FVector(-100.0f, 0.0f, 180.0f));
    CameraBoom->bUsePawnControlRotation = true;
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
    AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

void ASkyfallVehiclePawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!VehicleBody || !VehicleBody->IsSimulatingPhysics()) return;
    const FVector Forward = VehicleBody->GetForwardVector();
    if (FMath::Abs(ThrottleInput) > KINDA_SMALL_NUMBER) VehicleBody->AddForce(Forward * (ThrottleInput * EngineForce));
    if (FMath::Abs(SteeringInput) > KINDA_SMALL_NUMBER) {
        const float SpeedFactor = FMath::Clamp(VehicleBody->GetPhysicsLinearVelocity().Size() / 1200.0f, 0.15f, 1.0f);
        VehicleBody->AddTorqueInRadians(FVector(0.0f, 0.0f, SteeringInput * 18000000.0f * SpeedFactor));
    }
    if (BrakeInput > 0.0f) {
        const FVector Velocity = VehicleBody->GetPhysicsLinearVelocity();
        VehicleBody->AddForce(-Velocity.GetSafeNormal() * BrakeInput * BrakeStrength);
    }
}
void ASkyfallVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("VehicleThrottle"), this, &ASkyfallVehiclePawn::SetThrottle);
    PlayerInputComponent->BindAxis(TEXT("VehicleSteer"), this, &ASkyfallVehiclePawn::SetSteering);
    PlayerInputComponent->BindAxis(TEXT("VehicleBrake"), this, &ASkyfallVehiclePawn::SetBrake);
    PlayerInputComponent->BindAction(TEXT("VehicleReset"), IE_Pressed, this, &ASkyfallVehiclePawn::ResetVehicle);
}
void ASkyfallVehiclePawn::SetThrottle(float Value) { ThrottleInput = FMath::Clamp(Value, -1.0f, 1.0f); }
void ASkyfallVehiclePawn::SetSteering(float Value) { SteeringInput = FMath::Clamp(Value, -1.0f, 1.0f); }
void ASkyfallVehiclePawn::SetBrake(float Value) { BrakeInput = FMath::Clamp(Value, 0.0f, 1.0f); }
void ASkyfallVehiclePawn::ResetVehicle()
{
    if (!VehicleBody) return;
    SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100.0f), false, nullptr, ETeleportType::TeleportPhysics);
    SetActorRotation(FRotator(0.0f, GetActorRotation().Yaw, 0.0f), ETeleportType::TeleportPhysics);
    VehicleBody->SetPhysicsLinearVelocity(FVector::ZeroVector);
    VehicleBody->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
}
