// Fill out your copyright notice in the Description page of Project Settings.

#include "LessonManager.h"
#include "Data/LessonData.h"

void FLessonManager::AddLesson(ULessonData* Lesson)
{
    OpenLessons.Add(Lesson);
    ActiveLessonIndex = OpenLessons.Num() - 1;
    OnLessonListChanged.Broadcast();
    OnActiveLessonChanged.Broadcast();
}

void FLessonManager::SetActiveLesson(int32 Index)
{
    if (OpenLessons.IsValidIndex(Index) && ActiveLessonIndex != Index)
    {
        ActiveLessonIndex = Index;
        OnActiveLessonChanged.Broadcast();
    }
}

void FLessonManager::RemoveLesson(int32 Index)
{
    if (OpenLessons.IsValidIndex(Index))
    {
        OpenLessons.RemoveAt(Index);
        if (ActiveLessonIndex >= OpenLessons.Num())
            ActiveLessonIndex = OpenLessons.Num() - 1;

        OnLessonListChanged.Broadcast();
        OnActiveLessonChanged.Broadcast();
    }
}

ULessonData* FLessonManager::GetActiveLesson() const
{
    return OpenLessons.IsValidIndex(ActiveLessonIndex)
        ? OpenLessons[ActiveLessonIndex]
        : nullptr;
}
