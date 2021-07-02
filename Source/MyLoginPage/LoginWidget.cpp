// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
//#include "UObject/ConstructorHelpers.h"
//#include "Components/WidgetSwitcher.h"
//#include "Components/Button.h"
//#include "Components/EditableTextBox.h"
//#include "Components/TextBlock.h"


void ULoginWidget::UserSetup()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}



	
   
