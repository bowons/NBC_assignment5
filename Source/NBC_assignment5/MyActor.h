// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class NBC_ASSIGNMENT5_API AMyActor : public AActor
{
	GENERATED_BODY()
    // Push Test Auto Login Test
private:
    float TotalDistance = 0.0f;
    int EventCount = 0;
    FTimerHandle TimerHandle;

public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool MoveEvent(const FVector& EventLocation);
    void TimerAction();
    void Turn();
	void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
