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
        // --- TAB CONTAINER ---

        SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
        .AutoWidth()
        [
            SAssignNew(TabContainer, SHorizontalBox)
        ]

        // --- ADD TAB BUTTON ---

        +SHorizontalBox::Slot()
        .AutoWidth() 
        .Padding(2, 0)
        [
            SAssignNew(AddTabButton, SButton)
                .ButtonStyle(FAppStyle::Get(), "SimpleButton")
                .ContentPadding(0)
                .OnClicked(FOnClicked::CreateSP(this, &SLessonTabBar::OnAddTabButtonClicked))
                [                
                    SNew(SBox)
                        .WidthOverride(28.f)
                        .HeightOverride(28.f)
                        .HAlign(HAlign_Center)
                        .VAlign(VAlign_Center)
                        [
                            SNew(STextBlock)
                                .Text(FText::FromString("+"))
                        ]
                ]
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
        const FString TabLabel = Lessons[i]->LessonName.IsEmpty() ? TEXT("Untitled") : (Lessons[i]->LessonName + " - " + Lessons[i]->LessonMode);

        TabContainer->AddSlot()
            .AutoWidth()
            .Padding(5, 2)
            [
                SNew(SButton)
                    .ButtonColorAndOpacity(bIsActive ? SelectedTabColor : UnselectedTabColor)
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
    if (LessonManager.IsValid())
    {
        //LessonManager->AddLesson();
        ULessonData* NewLesson = NewObject<ULessonData>();

        if (NewLesson)
        {
            NewLesson->LessonName = "";
            NewLesson->LessonMode = "VI";
            LessonManager->AddLesson(NewLesson);
        }
    }
    return FReply::Handled();
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION
