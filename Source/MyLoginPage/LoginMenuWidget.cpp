// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginMenuWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "LoginWidget.h"
#include "FriendListName.h"


ULoginMenuWidget::ULoginMenuWidget()
{

	ConstructorHelpers::FClassFinder<UUserWidget> FriendListBPClass(TEXT("/Game/LoginScreen/WBP_FriendRow"));
	if (!ensure(FriendListBPClass.Class != nullptr)) return;
	FriendListClass = FriendListBPClass.Class;
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *FriendListClass->GetName());
}









