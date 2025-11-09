// Fill out your copyright notice in the Description page of Project Settings.


#include "AppHUD.h"
#include "UIComponents/SLessonEditorRoot.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void AAppHUD::BeginPlay()
{
	Super::BeginPlay();

    if (GEngine && GEngine->GameViewport)
    {
        LessonEditorRoot = SNew(SLessonEditorRoot).OwningHud(this);
        GEngine->GameViewport->AddViewportWidgetContent(
            SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(LessonEditorRoot.ToSharedRef())
        );

        if (PlayerOwner)
        {
            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(LessonEditorRoot);
            PlayerOwner->SetInputMode(InputMode);
			PlayerOwner->bShowMouseCursor = true;
        }
    }
}
