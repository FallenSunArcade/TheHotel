// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HTL_CameraActor.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class HTL_API AHTL_CameraActor : public AActor
{
	GENERATED_BODY()

public:
	AHTL_CameraActor();

protected:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxSpeed;

	UPROPERTY()
	APlayerController* PlayerController;
};
