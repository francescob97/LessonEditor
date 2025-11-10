
// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "LessonToolbarWidgetStyle.generated.h"

/**
 *
 */
USTRUCT()
struct LESSONEDITOR_API FLessonToolbarStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FLessonToolbarStyle();
	virtual ~FLessonToolbarStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FLessonToolbarStyle& GetDefault();

	// Parametri dello stile
	UPROPERTY(EditAnywhere, Category = Appearance)
	FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FButtonStyle AddButtonStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FComboBoxStyle ComboBoxStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle TextStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FSlateBrush SeparatorBrush;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FSlateBrush BackgroundBrush;

};

/**
 */
UCLASS(hidecategories = Object, MinimalAPI)
class ULessonToolbarWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))
	FLessonToolbarStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}
};
