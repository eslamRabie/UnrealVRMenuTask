// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawnBase.h"

#include "JsonLoader.h"

// Sets default values
AVRPawnBase::AVRPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AVRPawnBase::OnCategoriesLoaded(bool bSuccess, const FCategoriesResponse& Data)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully loaded %d categories"), Data.Categories.Num());
        Categories = Data.Categories;
		OnCategoriesLoadedDelegate.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load categories"));
	}
}

// Called when the game starts or when spawned
void AVRPawnBase::BeginPlay()
{

	UJsonLoader::FOnCategoriesLoaded Callback;
	Callback.BindDynamic(this, &AVRPawnBase::OnCategoriesLoaded);
	UJsonLoader::LoadJsonFromURL(TEXT("https://www.themealdb.com/api/json/v1/1/categories.php"), Callback);
	Super::BeginPlay();
}

// Called every frame
void AVRPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

