#include "SkyfallAICharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

ASkyfallAICharacter::ASkyfallAICharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AAIController::StaticClass();
}

void ASkyfallAICharacter::BeginPlay()
{
    Super::BeginPlay();
    UpdateDecision();
}

void ASkyfallAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    DecisionAccumulator += DeltaSeconds;
    if (DecisionAccumulator >= DecisionInterval)
    {
        DecisionAccumulator = 0.0f;
        UpdateDecision();
    }
}

APawn* ASkyfallAICharacter::FindNearestPlayer() const
{
    APawn* BestPawn = nullptr;
    float BestDistanceSquared = DetectionRadius * DetectionRadius;

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        const APlayerController* PC = It->Get();
        APawn* Candidate = PC ? PC->GetPawn() : nullptr;
        if (!IsValid(Candidate) || Candidate == this)
        {
            continue;
        }

        const float DistanceSquared = FVector::DistSquared(GetActorLocation(), Candidate->GetActorLocation());
        if (DistanceSquared < BestDistanceSquared)
        {
            BestDistanceSquared = DistanceSquared;
            BestPawn = Candidate;
        }
    }
    return BestPawn;
}

void ASkyfallAICharacter::UpdateDecision()
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (!AIController)
    {
        CurrentAIState = ESkyfallAIState::Idle;
        return;
    }

    APawn* NearestPlayer = FindNearestPlayer();
    if (NearestPlayer)
    {
        CurrentTarget = NearestPlayer;
        CurrentAIState = ESkyfallAIState::Chase;
        AIController->MoveToActor(NearestPlayer, 125.0f);
        return;
    }

    if (CurrentAIState == ESkyfallAIState::Chase && CurrentTarget.IsValid())
    {
        const float DistanceSquared = FVector::DistSquared(
            GetActorLocation(), CurrentTarget->GetActorLocation());
        if (DistanceSquared > LoseTargetRadius * LoseTargetRadius)
        {
            CurrentTarget.Reset();
        }
    }

    if (PatrolPoints.Num() == 0)
    {
        CurrentAIState = ESkyfallAIState::Idle;
        AIController->StopMovement();
        return;
    }

    if (PatrolIndex == INDEX_NONE)
    {
        PatrolIndex = 0;
    }

    AActor* Destination = PatrolPoints.IsValidIndex(PatrolIndex) ? PatrolPoints[PatrolIndex].Get() : nullptr;
    if (!IsValid(Destination))
    {
        PatrolIndex = (PatrolIndex + 1) % PatrolPoints.Num();
        CurrentAIState = ESkyfallAIState::Idle;
        return;
    }

    const float ArrivalDistanceSquared = FVector::DistSquared(GetActorLocation(), Destination->GetActorLocation());
    if (ArrivalDistanceSquared < FMath::Square(140.0f))
    {
        PatrolIndex = (PatrolIndex + 1) % PatrolPoints.Num();
        Destination = PatrolPoints[PatrolIndex].Get();
    }

    if (IsValid(Destination))
    {
        CurrentAIState = ESkyfallAIState::Patrol;
        AIController->MoveToActor(Destination, 90.0f);
    }
}
