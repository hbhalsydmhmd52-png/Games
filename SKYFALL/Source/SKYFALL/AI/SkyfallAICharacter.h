#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkyfallAICharacter.generated.h"

UENUM(BlueprintType)
enum class ESkyfallAIState : uint8
{
    Idle       UMETA(DisplayName="Idle"),
    Patrol     UMETA(DisplayName="Patrol"),
    Chase      UMETA(DisplayName="Chase")
};

/**
 * Lightweight open-world civilian/enemy AI prototype.
 * Place patrol targets in the level and assign them in the Details panel.
 * Requires a NavMeshBoundsVolume for MoveTo requests to work.
 */
UCLASS()
class SKYFALL_API ASkyfallAICharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASkyfallAICharacter();
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="SKYFALL|AI")
    TArray<TObjectPtr<AActor>> PatrolPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SKYFALL|AI", meta=(ClampMin="100.0"))
    float DetectionRadius = 1400.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SKYFALL|AI", meta=(ClampMin="100.0"))
    float LoseTargetRadius = 1900.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SKYFALL|AI", meta=(ClampMin="0.1"))
    float DecisionInterval = 0.75f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SKYFALL|AI")
    ESkyfallAIState CurrentAIState = ESkyfallAIState::Idle;

protected:
    virtual void BeginPlay() override;

private:
    void UpdateDecision();
    APawn* FindNearestPlayer() const;

    int32 PatrolIndex = INDEX_NONE;
    float DecisionAccumulator = 0.0f;
    TWeakObjectPtr<APawn> CurrentTarget;
};
