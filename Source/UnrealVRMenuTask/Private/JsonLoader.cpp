// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonLoader.h"

#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"


void UJsonLoader::LoadCategories(FOnCategoriesLoaded OnComplete)
{
    LoadJsonFromURL("https://www.themealdb.com/api/json/v1/1/categories.php", OnComplete);
}

void UJsonLoader::LoadJsonFromURL(const FString& URL, FOnCategoriesLoaded OnComplete)
{
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL(URL);
    HttpRequest->SetHeader("Content-Type", "application/json");
    
    HttpRequest->OnProcessRequestComplete().BindStatic(&UJsonLoader::OnResponseReceived, OnComplete);
    HttpRequest->ProcessRequest();
}

void UJsonLoader::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FOnCategoriesLoaded OnComplete)
{
    FCategoriesResponse ResultData;
    bool bSuccess = false;
    
    if (bWasSuccessful && Response.IsValid())
    {
        if (Response->GetResponseCode() == 200)
        {
            FString JsonString = Response->GetContentAsString();
            
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
            
            if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
            {
                // Get the "categories" array
                const TArray<TSharedPtr<FJsonValue>>* CategoriesArray;
                if (JsonObject->TryGetArrayField(TEXT("categories"), CategoriesArray))
                {
                    for (const TSharedPtr<FJsonValue>& CategoryValue : *CategoriesArray)
                    {
                        TSharedPtr<FJsonObject> CategoryObj = CategoryValue->AsObject();
                        
                        FCategory Category;
                        Category.IdCategory = CategoryObj->GetIntegerField(TEXT("idCategory"));
                        Category.CategoryName = CategoryObj->GetStringField(TEXT("strCategory"));
                        Category.CategoryThumbLink = CategoryObj->GetStringField(TEXT("strCategoryThumb"));
                        Category.CategoryDescription = CategoryObj->GetStringField(TEXT("strCategoryDescription"));
                        
                        ResultData.Categories.Add(Category);
                    }
                    
                    bSuccess = true;
                    UE_LOG(LogTemp, Log, TEXT("Loaded %d categories"), ResultData.Categories.Num());
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON from DB"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("HTTP Error: %d"), Response->GetResponseCode());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
    }

    OnComplete.ExecuteIfBound(bSuccess, ResultData);
}