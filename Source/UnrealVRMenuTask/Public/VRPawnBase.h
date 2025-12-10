// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonLoader.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "VRPawnBase.generated.h"

UCLASS()
class UNREALVRMENUTASK_API AVRPawnBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawnBase();

protected:
	UFUNCTION()
	void OnCategoriesLoaded(bool bSuccess, const FCategoriesResponse& Data);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCategoriesLoaded);

protected:

	

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnCategoriesLoaded OnCategoriesLoadedDelegate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FCategory> Categories;
	

};
