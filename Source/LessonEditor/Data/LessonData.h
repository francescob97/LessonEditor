// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LessonData.generated.h"


USTRUCT()
struct FLessonPropertiesData
{
    GENERATED_BODY()

    UPROPERTY()
    FString Author;

    UPROPERTY()
    FString Description;

    FLessonPropertiesData()
        : Author(TEXT("")), Description(TEXT("")) {
    }
};

/**
 * 
 */
UCLASS()
class LESSONEDITOR_API ULessonData : public UObject
{
	GENERATED_BODY()
public:
    UPROPERTY()
    int32 LessonID;

    UPROPERTY()
    FString LessonName;

    UPROPERTY()
    FString LessonMode;

    UPROPERTY()
    FLessonPropertiesData Properties;

    bool LoadFromXML(const FString& FilePath);
    bool SaveToXML(const FString& FilePath);

};
