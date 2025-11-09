// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

UENUM()
enum class ELessonMode : uint8
{
    List,
    Graph
};


/**
 * 
 */
class LESSONEDITOR_API SLessonGraphPanel : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLessonGraphPanel) {}

        

    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

	//FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

 //   FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	//FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	//FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	//FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;

	////FReply OnFocusLost(const FFocusEvent& InFocusEvent) override;

	//FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;

	//FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;

    //// Zoom e pan
    //virtual int32 OnPaint(
    //    const FPaintArgs& Args,
    //    const FGeometry& AllottedGeometry,
    //    const FSlateRect& MyCullingRect,
    //    FSlateWindowElementList& OutDrawElements,
    //    int32 LayerId,
    //    const FWidgetStyle& InWidgetStyle,
    //    bool bParentEnabled
    //) const override;

    //virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    //virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    //virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
   
    //TSharedPtr<class SCanvas> GraphCanvas;
    //TArray<TSharedPtr<FString>> ComboItems;

    //TSharedRef<SWidget> OnGenerateComboItem(TSharedPtr<FString> InItem)
    //{
    //    return SNew(STextBlock).Text(FText::FromString(*InItem));
    //}

//private:
//    float ZoomLevel = 1.0f;
//    FVector2D PanOffset = FVector2D::ZeroVector;
//    mutable FVector2D LastMousePos;
//    mutable bool bPanning = false;
};
