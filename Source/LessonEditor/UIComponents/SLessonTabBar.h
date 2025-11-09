// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class FLessonManager;
class SButton;

/**
 * 
 */
class LESSONEDITOR_API SLessonTabBar : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLessonTabBar) {}	
		SLATE_ARGUMENT(TSharedPtr<FLessonManager>, LessonManager)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<FLessonManager> LessonManager;
	TSharedPtr<SHorizontalBox> TabContainer;

	TSharedPtr<SButton> AddTabButton;

	void RebuildTabs();
	FReply OnTabClicked(int32 Index);
	FReply OnAddTabButtonClicked();
};
