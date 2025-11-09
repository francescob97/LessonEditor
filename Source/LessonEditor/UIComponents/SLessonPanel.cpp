// Fill out your copyright notice in the Description page of Project Settings.


#include "SLessonPanel.h"
#include "../Data/LessonData.h"
#include "SLessonToolbar.h"
#include "SLessonGraphPanel.h"
#include "SLessonInspector.h"

#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#include "SlateOptMacros.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLessonPanel::Construct(const FArguments& InArgs)
{
    LessonManager = InArgs._LessonManager;
    LessonManager->OnActiveLessonChanged.AddRaw(this, &SLessonPanel::RebuildLayout);


    //toolbar = SNew(SLessonToolbar);
	//PropertiesPanel = SNew(SLessonProperties);
	graphPanel = SNew(SLessonGraphPanel);
	//ListPanel = SNew(SLessonGraphPanel); // per ora usa stesso tipo
	InspectorPanel = SNew(SLessonInspector);
	
	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		[			
			//toolbar.ToSharedRef()
            SAssignNew(toolbar, SLessonToolbar)
				.LessonManager(LessonManager)
		]

		// Splitter principale (Properties | Graph/List | Inspector)
		+ SVerticalBox::Slot()
			.FillHeight(1.0f)
		[
			SAssignNew(MainSplitter, SSplitter)
            .PhysicalSplitterHandleSize(5.0f)
			.HitDetectionSplitterHandleSize(8.0f)
			.Orientation(Orient_Horizontal)
		]
		
	];

	RebuildLayout();
	
}
void SLessonPanel::SetPropertiesVisible(bool bVisible)
{
	bPropertiesVisible = bVisible;
	RebuildLayout();
}
void SLessonPanel::SetInspectorVisible(bool bVisible)
{
	bInspectorVisible = bVisible;
	RebuildLayout();
}
void SLessonPanel::SetGraphMode(bool bGraphMode)
{
	bIsGraphMode = bGraphMode;
	RebuildLayout();
}

void SLessonPanel::RebuildLayout()
{
    if (!MainSplitter.IsValid())
        return;

    MainSplitter->ClearChildren();


    ULessonData* Active = LessonManager->GetActiveLesson();

    if (!Active)
        return;

    // Aggiungi pannello sinistro (Properties)
    if (bPropertiesVisible)
    {
        MainSplitter->AddSlot()
            .Value(0.25f)
            [
                SNew(SBorder)
                    .BorderBackgroundColor(FLinearColor(0.7f, 0.7f, 0.7f))
                    .Padding(4)
                    [
                        //PropertiesPanel.ToSharedRef()
                        SNew(STextBlock).Text(FText::FromString("Properties Panel"))
                    ]
            ];
    }

    // Aggiungi pannello centrale (Graph o List)
    {
        TSharedRef<SWidget> CentralContent = bIsGraphMode ? graphPanel.ToSharedRef() :
            graphPanel.ToSharedRef();
            //ListPanel.ToSharedRef();

        MainSplitter->AddSlot()
            .Value(0.5f)
            [
                SNew(SBorder)
                    .BorderBackgroundColor(FLinearColor(0.08f, 0.08f, 0.08f))
                    .Padding(4)
                    [
                        CentralContent
                    ]
            ];
    }

    // Aggiungi pannello destro (Inspector)
    if (bInspectorVisible)
    {
        MainSplitter->AddSlot()
        .Value(0.25f)
        [
            SNew(SBorder)
            .BorderBackgroundColor(FLinearColor(0.66f, 0.66f, 0.66f))
            .Padding(4)
            [               
                InspectorPanel.ToSharedRef()
            ]
        ];
    }    

    /*TSharedRef<SWidget> Child = GraphPanel->GetChildren()->GetChildAt(0);
    if (Child->GetTypeAsString() == TEXT("STextBlock"))
    {
        TSharedPtr<STextBlock> GraphText = StaticCastSharedRef<STextBlock>(Child);
        GraphText->SetText(FText::FromString("Graph of " + Active->LessonName));
    }*/
}

//void SLessonPanel::RebuildLayout()
//{
//    // Svuota i pannelli precedenti
//    MainSplitter->ClearChildren();
//
//    // Layout principale
//    TSharedRef<SHorizontalBox> MainLayout = SNew(SHorizontalBox);
//
//    // Crea e aggiungi i 3 pannelli principali (ridimensionabili)
//    MainLayout->AddSlot()
//        .AutoWidth()
//        [
//            SAssignNew(PropertiesPanel, SBox)
//                .WidthOverride(250.f)
//                [
//                    SNew(STextBlock).Text(FText::FromString("Properties"))
//                ]
//        ];
//
//    MainLayout->AddSlot()
//        .FillWidth(1.f)
//        [
//            SAssignNew(GraphPanel, SBox)
//                [
//                    SNew(STextBlock)
//                        .Text(FText::FromString("Graph Area"))
//                ]
//        ];
//
//    MainLayout->AddSlot()
//        .AutoWidth()
//        [
//            SAssignNew(InspectorPanel, SBox)
//                .WidthOverride(250.f)
//                [
//                    SNew(STextBlock).Text(FText::FromString("Inspector"))
//                ]
//        ];
//
//    RootContainer->AddSlot()
//        [
//            SNew(SSplitter)
//                + SSplitter::Slot()[PropertiesPanel.ToSharedRef()]
//                + SSplitter::Slot()[GraphPanel.ToSharedRef()]
//                + SSplitter::Slot()[InspectorPanel.ToSharedRef()]
//        ];
//}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
