// Fill out your copyright notice in the Description page of Project Settings.


#include "SLessonTabBar.h"
#include "../LessonManager.h"
#include "../Data/LessonData.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Styling/SlateTypes.h"
#include "Framework/Application/SlateApplication.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLessonTabBar::Construct(const FArguments& InArgs)
{
    LessonManager = InArgs._LessonManager;

    LessonManager->OnLessonListChanged.AddRaw(this, &SLessonTabBar::RebuildTabs);
    LessonManager->OnActiveLessonChanged.AddRaw(this, &SLessonTabBar::RebuildTabs);


    ChildSlot
    [
        SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
            [
                SAssignNew(TabContainer, SHorizontalBox)
                       
            ]
			+ SHorizontalBox::Slot()   
            .Padding(5,0)
            [
                SAssignNew(AddTabButton, SButton)
					.ButtonStyle(FAppStyle::Get(), "SimpleButton")
					.Text(FText::FromString("+"))
					.OnClicked(FOnClicked::CreateSP(this, &SLessonTabBar::OnAddTabButtonClicked))
			]
        
    ];

    RebuildTabs();
}

void SLessonTabBar::RebuildTabs()
{
    if (!TabContainer.IsValid() || !LessonManager.IsValid())
        return;

    TabContainer->ClearChildren();

    const TArray<TObjectPtr<ULessonData>>& Lessons = LessonManager->OpenLessons;
    for (int32 i = 0; i < Lessons.Num(); ++i)
    {
        const bool bIsActive = (i == LessonManager->ActiveLessonIndex);
        const FString TabLabel = Lessons[i]->LessonName.IsEmpty() ? TEXT("Untitled") : Lessons[i]->LessonName;

        TabContainer->AddSlot()
            .AutoWidth()
            .Padding(5, 2)
            [
                SNew(SButton)
                    .ButtonColorAndOpacity(bIsActive ? FLinearColor(0.2f, 0.4f, 1.f) : FLinearColor(0.15f, 0.15f, 0.15f))
                    .OnClicked(FOnClicked::CreateSP(this, &SLessonTabBar::OnTabClicked, i))
                    [
                        SNew(STextBlock)
                            .Text(FText::FromString(TabLabel))
                            .ColorAndOpacity(FSlateColor::UseForeground())
                    ]
            ];
    }
}

FReply SLessonTabBar::OnTabClicked(int32 Index)
{
    if (LessonManager.IsValid())
        LessonManager->SetActiveLesson(Index);

    return FReply::Handled();
}

FReply SLessonTabBar::OnAddTabButtonClicked()
{
    return FReply::Handled();
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION
