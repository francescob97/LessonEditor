// Fill out your copyright notice in the Description page of Project Settings.


#include "SLessonToolbar.h"
#include "../Data/LessonData.h"
#include "Framework/Commands/UIAction.h"
#include "Styling/SlateIconFinder.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"

#include "EditorStyleSet.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLessonToolbar::Construct(const FArguments& InArgs)
{
	LessonManager = InArgs._LessonManager;

	ComboItems.Add(MakeShared<FString>("VI"));
	ComboItems.Add(MakeShared<FString>("MP"));
	ComboItems.Add(MakeShared<FString>("TEST"));

	const FLessonToolbarStyle* Style = &FLessonToolbarStyle::GetDefault();

	ULessonData* ActiveLesson = LessonManager->GetActiveLesson();


	ChildSlot
		[
			SNew(SBorder)
				.Padding(FMargin(4))
				.BorderImage(FAppStyle::Get()
					.GetBrush("Graph.Panel.SolidBackground"))

				[
					SNew(SBox)
						.HeightOverride(30.f) // altezza barra
						[
							SNew(SHorizontalBox)


							// ================= LEFT =================
							+SHorizontalBox::Slot()
							.AutoWidth()
							[
								MakeLeftToolbar()
							]


							// ============ SPACER ============
							+SHorizontalBox::Slot()
							.FillWidth(1.f)
							[
								SNew(SSpacer)
							]


							// ================= DIFF &  =================
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								MakeDiffToolbar()
							]


							// ============ SPACER ============
							+SHorizontalBox::Slot()
							.FillWidth(1.f)
							[
								SNew(SSpacer)
							]


							// ================= CENTER =================
							+SHorizontalBox::Slot()
							.AutoWidth()
							[
								MakeCenterToolbar()
							]


							// ============ SPACER ============
							+SHorizontalBox::Slot()
							.FillWidth(1.f)
							[
								SNew(SSpacer)
							]


							// ================= RIGHT =================
							+SHorizontalBox::Slot()
							.AutoWidth()
							[
								MakeToolbarSequenceBox()
							]
						]
				]
		];
}

TSharedRef<SWidget> SLessonToolbar::MakeLeftToolbar()
{
	return SNew(SHorizontalBox)

		+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			// === Import ===
			MakeToolbarButton(
				"Icons.Import",
				FText::FromString("Open Procedure"),
				FOnClicked::CreateSP(this, &SLessonToolbar::OnOpenProcedureFile))
		]

		+ SHorizontalBox::Slot().AutoWidth().Padding(2, 0)
		[
			// === SAVE ===
			MakeToolbarButton(
				 "Icons.Save",
				 //"Icons.SaveChanged"
				 FText::FromString("Save Procedure"),					
				 FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))
		]

		+ SHorizontalBox::Slot().AutoWidth().Padding(2, 0)
		[
			// === Open Folder ===
			MakeToolbarButton(
				"Icons.BrowseContent",
				FText::FromString("Open Folder"),
				FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))
		];
}

TSharedRef<SWidget> SLessonToolbar::MakeDiffToolbar()
{
	return SNew(SHorizontalBox)

		+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			// === DIFF BTN ===
			MakeToolbarButton(
				"Icons.Tasks",
				FText::FromString("Diff from last edit"),
				FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))
		]

	+ SHorizontalBox::Slot().AutoWidth().Padding(2, 0)
		[
			// === FIND BTN ===
			MakeToolbarButton(
				"Icons.Search",
				FText::FromString("Search for"),					
				FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))
		];
}


TSharedRef<SWidget> SLessonToolbar::MakeCenterToolbar()
{
	return SNew(SHorizontalBox)

		+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			// === COMBO ===
			SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&ComboItems)
				.OnGenerateWidget(this, &SLessonToolbar::GenerateComboItem)
				[
					SNew(STextBlock)
						.Text(FText::FromString("Mode"))
				]
		]

	+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)
		[
			MakeToolbarButton(
				"LevelEditor.AddActor",
				FText::FromString("Show / Add Window"),
				FOnClicked::CreateSP(this, &SLessonToolbar::OnSaveProcedureFIle))
		];
}

TSharedRef<SWidget> SLessonToolbar::GenerateComboItem(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}

TSharedRef<SWidget> SLessonToolbar::MakeToolbarButton(const FName& Icon, const FText& Tooltip,FOnClicked OnClicked, FLinearColor ColorOpacity)
{
	const FLessonToolbarStyle* Style = &FLessonToolbarStyle::GetDefault();

	return SNew(SButton)
		.ToolTipText(Tooltip)	
		.ButtonStyle(&Style->ButtonStyle)		
		.OnClicked(OnClicked)
		.Content()
		[
			SNew(SImage)
				.Image(FAppStyle::GetBrush(Icon))
				.ColorAndOpacity(ColorOpacity)
		];
}

TSharedRef<SWidget> SLessonToolbar::MakeToolbarSequenceBox()
{
	return 
		SNew(SHorizontalBox)

		// === PLAY ===
		+ SHorizontalBox::Slot().AutoWidth()
		[
			SNew(SButton)
				//.ButtonStyle(&Style->GetWidgetStyle<FButtonStyle>("MyToolbar.Button"))
				.ToolTipText(FText::FromString("Play"))
				[
					SNew(SImage)
						.Image(FAppStyle::GetBrush("PlayWorld.PlayInViewport"))

				]
		]

		// === STEP ===
		+ SHorizontalBox::Slot().AutoWidth()
		[
			SNew(SButton)
				//.ButtonStyle(&Style->GetWidgetStyle<FButtonStyle>("MyToolbar.Button"))
				.ToolTipText(FText::FromString("Step"))
				[
					SNew(SImage)
						//.Image(F::GetBrush("Icons.SingleFrameAdvance"))
				]
		]

		// === PAUSE ===
		+ SHorizontalBox::Slot().AutoWidth()
		[
			SNew(SButton)
				//.ButtonStyle(&Style->GetWidgetStyle<FButtonStyle>("MyToolbar.Button"))
				.ToolTipText(FText::FromString("Pause"))
				[
					SNew(SImage)
						.Image(FAppStyle::GetBrush("PlayWorld.PausePlaySession.Small"))
				]
		]

		// === STOP ===
		+ SHorizontalBox::Slot().AutoWidth()
		[
			SNew(SButton)
				//.ButtonStyle(&Style->GetWidgetStyle<FButtonStyle>("MyToolbar.Button"))
				.ToolTipText(FText::FromString("Stop"))
				[
					SNew(SImage)
						.Image(FAppStyle::GetBrush("PlayWorld.StopPlaySession.Small"))
				]
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
			EFileDialogFlags::Multiple,
			OutFiles
		);

		if (bOpened && OutFiles.Num() > 0)
		{
			OnFileSelected(OutFiles);
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
