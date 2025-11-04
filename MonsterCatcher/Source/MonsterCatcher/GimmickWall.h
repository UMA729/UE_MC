// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GimmickWall.generated.h"

UCLASS()
class MONSTERCATCHER_API AGimmickWall : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WallMesh;

	// Sets default values for this actor's properties
	AGimmickWall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartMoveUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool isMoving = false;
	float MoveSpeed = 200.f;
	float MoveDistance = 300.f;
	float MoveSoFar = 0.f;
};
