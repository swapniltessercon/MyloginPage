// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPageHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.h"


ALoginPageHUD::ALoginPageHUD()
{
    ConstructorHelpers::FClassFinder<ULoginWidget> LoginBPClass(TEXT("/Game/WBP_loginWidget"));
	if (LoginBPClass.Class != NULL)
	{
		LoginWidgetClass = LoginBPClass.Class;
	}

}

void ALoginPageHUD::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ALoginPageHUD::BeginPlay Found HUDClass "))
	if (!ensure(LoginWidgetClass != nullptr)) return;
	loginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
	if (!ensure(loginWidget != nullptr)) return;
	loginWidget->AddToViewport();
	loginWidget->UserSetup();
}