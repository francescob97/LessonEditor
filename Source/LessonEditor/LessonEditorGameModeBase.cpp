// Fill out your copyright notice in the Description page of Project Settings.


#include "LessonEditorGameModeBase.h"
#include "AppHUD.h"

ALessonEditorGameModeBase::ALessonEditorGameModeBase()
{
	PlayerControllerClass = APlayerController::StaticClass();
	HUDClass = AAppHUD::StaticClass();
}