// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "../LessonManager.h"

class SLessonToolbar;
class SLessonGraphPanel;
class SLessonInspector;
class ULessonData;
class FLessonManager;

class LESSONEDITOR_API SLessonPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLessonPanel) {}
		SLATE_ARGUMENT(TSharedPtr<FLessonManager>, LessonManager)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/** Mostra/nasconde i pannelli laterali */
	void SetPropertiesVisible(bool bVisible);
	void SetInspectorVisible(bool bVisible);

	/** Cambia modalità della finestra centrale (Graph o List) */
	void SetGraphMode(bool bGraphMode);

private:
	TSharedPtr<FLessonManager> LessonManager;

	TSharedPtr<SLessonToolbar> toolbar;

	TSharedPtr<SSplitter> MainSplitter;

	/** Pannelli interni */
	TSharedPtr<SWidget> PropertiesPanel;
	TSharedPtr<SWidget> GraphPanel;
	TSharedPtr<SLessonInspector> InspectorPanel;

	TSharedPtr<SWidget> centralPanel;
	
	//TSharedPtr<SLessonProperties> PropertiesPanel;
	TSharedPtr<SLessonGraphPanel> graphPanel;
	//TSharedPtr<SLessonGraphPanel> ListPanel; // alternativa al graph


	 /** Splitter orizzontale principale */

	/** Stato visibilità pannelli laterali */
	bool bPropertiesVisible = true;
	bool bInspectorVisible = true;

	/** Modalità corrente: Graph (true) o List (false) */
	bool bIsGraphMode = true;

	/** Ricostruisce il layout dello splitter */
	void RebuildLayout();
};
