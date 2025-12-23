// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "../LessonManager.h"
#include "../Styles/LessonToolbarWidgetStyle.h"

#define HBOX_SEPARATOR_SLOT() \
    SHorizontalBox::Slot() \
    .AutoWidth() \
    .Padding(5.f, 0.f) \
    [ \
        SNew(SSeparator) \
    ]

/**
 * 
 */
class LESSONEDITOR_API SLessonToolbar : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLessonToolbar) {}	
		SLATE_ARGUMENT(TSharedPtr<FLessonManager>, LessonManager)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<FLessonManager> LessonManager;

	TSharedRef<SWidget> MakeLeftToolbar();
	TSharedRef<SWidget> MakeDiffToolbar();
	TSharedRef<SWidget> MakeCenterToolbar();


	TArray<TSharedPtr<FString>> ComboItems;
	TSharedRef<SWidget> GenerateComboItem(TSharedPtr<FString> InItem);

	static TSharedRef<SWidget> MakeToolbarButton(
		const FName& Icon,
		const FText& Tooltip,	
		FOnClicked OnClicked,
		FLinearColor ColorOpacity = FLinearColor::White
	);

	static TSharedRef<SWidget> MakeToolbarSequenceBox();
	TSharedPtr<FString> SelectedComboItem;


	FReply OnOpenProcedureFile();
	void OnFileSelected(const TArray<FString>& FilePaths);

	FReply OnSaveProcedureFIle();

	//FReply OnCloseProcedureFIle();
};
