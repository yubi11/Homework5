#include "homework5.h"

// Sets default values
Ahomework5::Ahomework5()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Ahomework5::BeginPlay()
{
    Super::BeginPlay();

    // 게임 시작 시 좌표 이동 시작
    move();
}

// Called every frame
void Ahomework5::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// 0 또는 1을 랜덤으로 반환하는 함수
int32 Ahomework5::step()
{
    return FMath::RandRange(0, 1);
}

// 두 좌표간 거리를 구하는 함수 (코드 스니펫 활용)
float Ahomework5::distance(FVector first, FVector second)
{
    float dx = first.X - second.X;
    float dy = first.Y - second.Y;
    return FMath::Sqrt(dx * dx + dy * dy);
}

// 특정 확률로 이벤트 발생시키는 함수 (코드 스니펫 활용)
bool Ahomework5::TriggerEventWithProbability(float Probability)
{
    int32 RandomValue = FMath::RandRange(1, 100); // 1 ~ 100의 난수 생성
    if (RandomValue <= Probability)
    {
        UE_LOG(LogTemp, Log, TEXT("Event Triggered!"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Event Not Triggered"));
        return false;
    }
}

// 메인 이동 함수
void Ahomework5::move()
{
    // TArray와 FVector를 활용한 좌표 관리 (코드 스니펫 활용)
    TArray<FVector> VectorArray;

    // 시작 좌표 (0, 0, 0) 추가 - Z축은 항상 0
    FVector CurrentPosition(0.0f, 0.0f, 0.0f); // 과제에선 FVector2D start로 보기를 제공했지만 알아보기 힘들어서 변수명 변경 및 3D 좌표 출럭하게 2D로 안 함.
    VectorArray.Add(CurrentPosition);

    UE_LOG(LogTemp, Warning, TEXT("=== 좌표 이동 시작 ==="));
    UE_LOG(LogTemp, Display, TEXT("시작 좌표: X = %.0f, Y = %.0f, Z = %.0f"),
        CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z);

    float TotalDistance = 0.0f;
    int32 EventCount = 0;

    // 10회 이동
    for (int32 i = 1; i <= 10; i++)
    {
        // 이전 좌표 저장
        FVector PreviousPosition = CurrentPosition;

        // 새로운 좌표 계산 (step 함수 활용, Z축은 변동없음)
        int32 StepX = step();
        int32 StepY = step();
        CurrentPosition.X += StepX;
        CurrentPosition.Y += StepY;
        // CurrentPosition.Z는 0으로 유지

        // 새로운 좌표를 배열에 추가
        VectorArray.Add(CurrentPosition);

        // 현재 좌표 출력 (필수 기능)
        UE_LOG(LogTemp, Display, TEXT("Step %d: 현재 좌표 X = %.0f, Y = %.0f, Z = %.0f"),
            i, CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z);

        // === 도전 기능 시작 ===

        // 이동 거리 계산 (distance 함수 활용)
        float StepDistance = distance(PreviousPosition, CurrentPosition);
        TotalDistance += StepDistance;
        UE_LOG(LogTemp, Display, TEXT("Step %d: 이동 거리 %.2f"), i, StepDistance);

        // 50% 확률로 랜덤 이벤트 발생 (TriggerEventWithProbability 함수 활용)
        if (TriggerEventWithProbability(50.0f))
        {
            EventCount++;
        }

        // === 도전 기능 끝 ===
    }

    // 모든 좌표 출력
    UE_LOG(LogTemp, Warning, TEXT("=== 모든 이동 경로 ==="));
    for (int32 i = 0; i < VectorArray.Num(); i++)
    {
        const FVector& Vec = VectorArray[i];
        UE_LOG(LogTemp, Display, TEXT("Vector %d: X = %.0f, Y = %.0f, Z = %.0f"),
            i, Vec.X, Vec.Y, Vec.Z);
    }

    // 최종 결과 출력
    UE_LOG(LogTemp, Warning, TEXT("=== 이동 완료 ==="));
    UE_LOG(LogTemp, Display, TEXT("최종 좌표: X = %.0f, Y = %.0f, Z = %.0f"),
        CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z);
    UE_LOG(LogTemp, Display, TEXT("총 이동 거리: %.2f"), TotalDistance);
    UE_LOG(LogTemp, Display, TEXT("총 이벤트 발생 횟수: %d"), EventCount);
}
