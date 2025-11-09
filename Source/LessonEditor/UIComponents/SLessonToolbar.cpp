// Fill out your copyright notice in the Description page of Project Settings.


#include "SLessonToolbar.h"
#include "../Data/LessonData.h"
#include "Framework/Commands/UIAction.h"
#include "Styling/SlateIconFinder.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLessonToolbar::Construct(const FArguments& InArgs)
{
	LessonManager = InArgs._LessonManager;

	ComboItems.Add(MakeShared<FString>("Opzione 1"));
	ComboItems.Add(MakeShared<FString>("Opzione 2"));
	ComboItems.Add(MakeShared<FString>("Opzione 3"));

	ChildSlot
	[
		SNew(SHorizontalBox)

		// === OPEN ===
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(5, 0)
		[
			MakeToolbarButton(
				"Icons.Document",
				FText::FromString("Open Procedure"),
				"FlatButton.Default",
				FOnClicked::CreateSP(this, &SLessonToolbar::OnOpenProcedureFile))
		]

		+ HBOX_SEPARATOR_SLOT()

		// === SAVE ===
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(5, 0)
		[
			MakeToolbarButton(
				"Icons.Save",
				FText::FromString("Save Procedure"),
				"FlatButton.Default",
				FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))
		]

		+ HBOX_SEPARATOR_SLOT()

		// === Open Folder ===
		+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			MakeToolbarButton(
				"Icons.FolderOpen",
				FText::FromString("Save Procedure"),
				"FlatButton.Default",
				FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))

		]

		+ HBOX_SEPARATOR_SLOT()

		// === DIFF BTN ===
		+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			SNew(SButton)
			[
				SNew(STextBlock).Text(FText::FromString("Diff"))
			]
		]

		+ HBOX_SEPARATOR_SLOT()

		// === FIND BTN ===
		+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			MakeToolbarButton(
				"Icons.Search",
				FText::FromString("Search for"),
				"FlatButton.Default",
				FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))
		]

		+ HBOX_SEPARATOR_SLOT()

		// === COMBO ===
		+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&ComboItems)
				.OnGenerateWidget(this, &SLessonToolbar::GenerateComboItem)
				[
					SNew(STextBlock).Text(FText::FromString("Mode"))
				]
		]
	];
}

TSharedRef<SWidget> SLessonToolbar::GenerateComboItem(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}

TSharedRef<SWidget> SLessonToolbar::MakeToolbarButton(const FName& Icon, const FText& Tooltip, const FName& ButtonStyle, FOnClicked OnClicked, FLinearColor ColorOpacity)
{
	return SNew(SButton)
		.ToolTipText(Tooltip)
		.ButtonStyle(FAppStyle::Get(), ButtonStyle)
		.OnClicked(OnClicked)
		[
			SNew(SImage)
				.Image(FAppStyle::GetBrush(Icon))
				.ColorAndOpacity(ColorOpacity)
		];
}

FReply SLessonToolbar::OnSaveProcedureFIle()
{
	UE_LOG(LogTemp, Log, TEXT("Save button clicked!"));
	// LessonManager->GetActiveLesson()->SaveToXML();
	return FReply::Handled();
}


FReply SLessonToolbar::OnOpenProcedureFile()
{
	UE_LOG(LogTemp, Log, TEXT("Open procedure button clicked!"));

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();


	if (DesktopPlatform)
	{
		TArray<FString> OutFiles;
		const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

		const bool bOpened = DesktopPlatform->OpenFileDialog(
			ParentWindowHandle,
			TEXT("Seleziona file XML Lezione"),
			FPaths::ProjectContentDir(),
			TEXT(""),
			TEXT("XML Files (*.xml)|*.xml"),
			EFileDialogFlags::None,
			OutFiles
		);

		if (bOpened && OutFiles.Num() > 0)
		{
			OnFileSelected(OutFiles);
		}
	}

	if (LessonManager.IsValid())
	{
		auto Lesson = LessonManager->GetActiveLesson();
		if (Lesson)
		{
			Lesson->LessonName = TEXT("Loaded From XML");
			LessonManager->OnLessonListChanged.Broadcast();
			LessonManager->OnActiveLessonChanged.Broadcast();
		}
	}

	return FReply::Handled();
}

void SLessonToolbar::OnFileSelected(const TArray<FString>& FilePaths)
{	
	for (const FString& Path : FilePaths)
	{		
		UE_LOG(LogTemp, Log, TEXT("Path trovato: %s"), *Path);

		ULessonData* NewLesson = NewObject<ULessonData>();
	
		if (NewLesson && NewLesson->LoadFromXML(Path))
		{			
			LessonManager->AddLesson(NewLesson);
		}
	}

	//ULessonData* NewLesson = NewObject<ULessonData>();
	//if (NewLesson->LoadFromXML(FilePath))
	//{
	//	OnLessonLoaded.ExecuteIfBound(NewLesson); 
	//}
}

//FReply SLessonToolbar::OnCloseClicked()
//{
//	if (LessonManager.IsValid())
//	{
//		int32 Index = LessonManager->ActiveLessonIndex;
//		LessonManager->RemoveLesson(Index);
//	}
//	return FReply::Handled();
//}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
