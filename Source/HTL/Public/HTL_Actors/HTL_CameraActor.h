// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HTL_CameraActor.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UAnimMontage;

UCLASS()
class HTL_API AHTL_CameraActor : public AActor
{
	GENERATED_BODY()

public:
	AHTL_CameraActor();

	void StartVideo();

	void SetOutroMaterial(UMaterialInterface* OutroMaterial);

	void InsertTape();

	void PanIn();
	
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

	UPROPERTY(EditAnywhere, Category = TV)
	UStaticMeshComponent* TV;

	UPROPERTY(EditAnywhere, Category = TV)
	UMaterialInterface* IntroMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = TV)
	UMaterialInterface* Transparent = nullptr;

	UPROPERTY(EditAnywhere, Category = VCR)
	USkeletalMeshComponent* VCR;

	UPROPERTY(EditAnywhere, Category = VCR)
	UAnimMontage* InsertTapeMontage = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Camera")
	bool bStartPressed = false;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	AActor* ActorToLerpTo = nullptr;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MovementInterpolationSpeed  = 1.f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	bool bIsOutro = false;
	
	UPROPERTY()
	APlayerController* PlayerController;
};
