// Fill out your copyright notice in the Description page of Project Settings.

#include "LessonToolbarWidgetStyle.h"
#include "SlateBasics.h"

FLessonToolbarStyle::FLessonToolbarStyle()
{
	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	ComboBoxStyle = FCoreStyle::Get().GetWidgetStyle<FComboBoxStyle>("ComboBox");
	TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");

	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	ButtonStyle
		.SetNormal(FSlateColorBrush(FLinearColor(0.18f, 0.18f, 0.18f)))
		.SetHovered(FSlateColorBrush(FLinearColor(0.25f, 0.25f, 0.25f)))
		.SetPressed(FSlateColorBrush(FLinearColor(0.10f, 0.10f, 0.10f)));

	// Pulsante Add (quello centrale tipo "Show Window")
	AddButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	AddButtonStyle
		.SetNormal(FSlateColorBrush(FLinearColor(0.10f, 0.35f, 0.10f)))
		.SetHovered(FSlateColorBrush(FLinearColor(0.15f, 0.45f, 0.15f)))
		.SetPressed(FSlateColorBrush(FLinearColor(0.08f, 0.25f, 0.08f)));

	// Testo
	TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
	TextStyle
		.SetFont(FSlateFontInfo(FCoreStyle::GetDefaultFont(), 10))
		.SetColorAndOpacity(FSlateColor(FLinearColor::White));

	// Separator
	SeparatorBrush = FSlateColorBrush(FLinearColor(0.3f, 0.3f, 0.3f));

	// Background
	BackgroundBrush = FSlateColorBrush(FLinearColor(0.05f, 0.05f, 0.05f));
}

FLessonToolbarStyle::~FLessonToolbarStyle()
{
}

const FName FLessonToolbarStyle::TypeName(TEXT("FLessonToolbarStyle"));

const FLessonToolbarStyle& FLessonToolbarStyle::GetDefault()
{
	static FLessonToolbarStyle Default;
	return Default;
}

void FLessonToolbarStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	OutBrushes.Add(&ButtonStyle.Normal);
	OutBrushes.Add(&AddButtonStyle.Normal);
	OutBrushes.Add(&SeparatorBrush);
	OutBrushes.Add(&BackgroundBrush);
}

