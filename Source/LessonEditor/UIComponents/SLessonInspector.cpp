// Fill out your copyright notice in the Description page of Project Settings.


#include "SLessonInspector.h"
#include "Styling/AppStyle.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLessonInspector::Construct(const FArguments& InArgs)
{
	
    ChildSlot
    [
        SNew(SBorder)                
        .BorderImage(FAppStyle::Get()
            .GetBrush("Graph.Panel.SolidBackground"))
        .Padding(FMargin(8.0f))
        [               
            SNew(SScrollBox)
            + SScrollBox::Slot()
            [
                SNew(SVerticalBox)
				+ SVerticalBox::Slot()
                [
                    SNew(STextBlock)
                    .Text(FText::FromString("Lesson Inspector"))			
                    //.Font(FSlateFontInfo("Verdana", 36))
                ]
            ]                   
        ]
    ];	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
