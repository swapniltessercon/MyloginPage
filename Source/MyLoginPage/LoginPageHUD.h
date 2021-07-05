// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "LoginPageHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYLOGINPAGE_API ALoginPageHUD : public AHUD
{
	GENERATED_BODY()
public:
	ALoginPageHUD();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<UUserWidget> LoginWidgetClass;
	class ULoginWidget* loginWidget;
};
