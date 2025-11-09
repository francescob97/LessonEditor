// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AppHUD.generated.h"

/**
 * 
 */
UCLASS()
class LESSONEDITOR_API AAppHUD : public AHUD
{
	GENERATED_BODY()

protected:
	//virtual void DrawHUD() override;
	void BeginPlay() override;
	
	TSharedPtr<class SLessonEditorRoot> LessonEditorRoot;
	TSharedPtr<class SWidget> WidgetContainer;
};
