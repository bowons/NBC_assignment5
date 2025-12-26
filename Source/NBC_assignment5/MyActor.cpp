// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
    // 1초마다 반복되는 타이머 설정
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyActor::TimerAction, 1.0f, true);
}

// 50퍼 확률로 이벤트 발생
bool AMyActor::MoveEvent(const FVector &EventLocation)
{
	int RandomValue = FMath::RandRange(0, 1); // 0 아님 1

	if (RandomValue == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Event Occurred at Location: %s"), *EventLocation.ToString()));
		return true;
	}
	return false;
}

// 10번 반복, 매번 이동시 현재 좌표를 출력한다.
// 각 이동 시 마다, 50% 확률로 랜덤하게 이벤트가 발생하며 이벤트는 별도의 함수로 구현되어야 함
// 10회 이동후 총 이동 거리와 이벤트 발생 횟수를 출력
void AMyActor::TimerAction()
{
    if (EventCount < 10) 
    {
        FVector LastLocation = GetActorLocation(); // 현재 위치 저장

        Turn();
        Move();

        FVector CurrentLocation = GetActorLocation(); // 이동 후 위치 저장
        float DistanceMoved = FVector::Dist(LastLocation, CurrentLocation); // 이전 위치와 현재 위치 사이의 거리 계산하는 함수
        TotalDistance += DistanceMoved; // 누적
        LastLocation = CurrentLocation; // 현재 위치를 이전 위치로 업데이트

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Current Location: %s"), *CurrentLocation.ToString()));
        }

        if (MoveEvent(CurrentLocation))
        {
            EventCount++;
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Total Distance Moved: %.2f"), TotalDistance));
            GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Total Events Occurred: %d"), EventCount));
            GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
            EventCount = 0;
            TotalDistance = 0.0f;
        }
    }  
}

// 랜덤한 곳으로 회전하는 함수
// 원래 위치를 기준 Yaw 축을 중심으로 -180도에서 180도 사이의 랜덤한 각도 회전
void AMyActor::Turn()
{
	FRotator NewRotation = GetActorRotation();
	float RandomYaw = FMath::RandRange(-180.0f, 180.0f);

	NewRotation.Yaw += RandomYaw;
	SetActorRotation(NewRotation);	
}

// 랜덤한 곳으로 이동하는 함수
// 원래위치를 기준 500 유닛 이내의 랜덤 X, Z 위치로 이동
void AMyActor::Move()
{
	FVector NewLocation = GetActorLocation();
	float RandomX = FMath::RandRange(-500.0f, 500.0f);
	float RandomY = FMath::RandRange(-500.0f, 500.0f);

	NewLocation.X += RandomX;
	NewLocation.Y += RandomY;
	SetActorLocation(NewLocation);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

