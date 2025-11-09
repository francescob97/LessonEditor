// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class ULessonData;
/**
 * 
 */
class LESSONEDITOR_API FLessonManager : public TSharedFromThis<FLessonManager>
{
public:
  
    UPROPERTY() // UPROPERTY() protegge l'array dal GC
    TArray<TObjectPtr<ULessonData>> OpenLessons;

    int32 ActiveLessonIndex = INDEX_NONE;

    /*
    * DELEGATES
    */

    DECLARE_MULTICAST_DELEGATE(FOnLessonListChanged);
    DECLARE_MULTICAST_DELEGATE(FOnActiveLessonChanged);
    
    FOnLessonListChanged OnLessonListChanged;    
    FOnActiveLessonChanged OnActiveLessonChanged;

public:
    void AddLesson(ULessonData* Lesson);
    void SetActiveLesson(int32 Index);
    void RemoveLesson(int32 Index);

    ULessonData* GetActiveLesson() const;
};