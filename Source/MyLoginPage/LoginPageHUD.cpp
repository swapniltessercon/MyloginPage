// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPageHUD.h"
#include "UObject/ConstructorHelpers.h"


ALoginPageHUD::ALoginPageHUD()
{
    ConstructorHelpers::FClassFinder<UUserWidget> LoginBPClass(TEXT("/Game/WBP_loginWidget"));
	if (LoginBPClass.Class != NULL)
	{
	LoginClass = LoginBPClass.Class;
	}
}

void ALoginPageHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("found HUDClass..."))

	if (!ensure(LoginClass != nullptr)) return;
	Widget = CreateWidget(GetWorld(),LoginClass);

	if (!ensure(Widget != nullptr)) return;
	Widget->AddToViewport();

}