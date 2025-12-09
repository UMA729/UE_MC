// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GimmickActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class MONSTERCATCHER_API AGimmickActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGimmickActor();


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GimmickMesh;

	UPROPERTY(EditAnywhere, Category = Enemy, meta = (AllowPrivateAccess = "true"))
	bool MovingFloor; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* ButtonActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* EnemyActor;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Emerge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	bool isHit = false;
	float MoveSpeed = 200.f;
	float MoveDistance = 300.f;
	float MoveSoFar = 0.f;

};
