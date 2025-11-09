// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "../LessonManager.h"

class AAppHUD;
class SLessonTabBar;
class ULessonData;

class LESSONEDITOR_API SLessonEditorRoot : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLessonEditorRoot) {}
		SLATE_ARGUMENT(TWeakObjectPtr<AAppHUD>, OwningHud);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TWeakObjectPtr<AAppHUD> OwningHud;

	TSharedPtr<FLessonManager> LessonManager;
	TSharedPtr<SLessonTabBar> TabBar;
};
