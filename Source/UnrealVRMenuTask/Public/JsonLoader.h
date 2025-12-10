// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/NoExportTypes.h"
#include "JsonLoader.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FCategory
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	int32 IdCategory;

	UPROPERTY(BlueprintReadWrite)
	FString CategoryName;

	 	
	UPROPERTY(BlueprintReadWrite)
	FString CategoryThumbLink;

	UPROPERTY(BlueprintReadWrite)
	UTexture2DDynamic* CategoryThumb;
	
	UPROPERTY(BlueprintReadWrite)
	FString CategoryDescription;
};


USTRUCT(BlueprintType, Blueprintable)
struct FCategoriesResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FCategory> Categories;
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UNREALVRMENUTASK_API UJsonLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Delegate for completion callback
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnCategoriesLoaded, bool, bSuccess, const FCategoriesResponse&, Data);

	UFUNCTION(BlueprintCallable, Category = "JsonLoader")
	static void LoadCategories(FOnCategoriesLoaded OnComplete);

	UFUNCTION(BlueprintCallable, Category = "JsonLoader")
	static void LoadJsonFromURL(const FString& URL, FOnCategoriesLoaded OnComplete);

protected:
	static void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnCategoriesLoaded OnComplete);
	

public:

	
protected:


};
