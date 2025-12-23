// Fill out your copyright notice in the Description page of Project Settings.


#include "SLessonEditorRoot.h"
#include "SLessonToolbar.h"
#include "SLessonTabBar.h"
#include "SLessonPanel.h"

#include "../AppHUD.h"
#include "GameFramework/PlayerController.h"

#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Styling/SlateColor.h"

#include "../Data/LessonData.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLessonEditorRoot::Construct(const FArguments& InArgs)
{
	OwningHud = InArgs._OwningHud;

    LessonManager = MakeShared<FLessonManager>();

    ChildSlot
    [
        SNew(SVerticalBox)

        // --- Tab Bar ---
        + SVerticalBox::Slot().AutoHeight().Padding(5)
        [
            SAssignNew(TabBar, SLessonTabBar)
                .LessonManager(LessonManager)
        ]

        // --- Editor Panel ---
        + SVerticalBox::Slot().FillHeight(1.f)
        [
            SNew(SLessonPanel)
                .LessonManager(LessonManager)
        ]
    ];


    //LessonManager->AddLesson();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
