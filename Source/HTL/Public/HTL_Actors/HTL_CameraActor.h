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

	void StartPressed();
	
protected:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

	void ChangeToIntroMaterial();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = TV)
	UStaticMeshComponent* TV;

	UPROPERTY(EditAnywhere, Category = TV)
	UMaterialInterface* IntroMaterial = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Menu Camera")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Menu Camera")
	bool bStartPressed = false;
	
	UPROPERTY(EditAnywhere, Category = "Menu Camera")
	AActor* ActorToLerpTo = nullptr;

	UPROPERTY(EditAnywhere, Category = "Menu Camera")
	float MovementInterpolationSpeed  = 1.f;
	
	UPROPERTY()
	APlayerController* PlayerController;
};
