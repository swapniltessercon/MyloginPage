// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendListName.h"
#include "Components/Button.h"
#include "LoginMenuWidget.h"


void UFriendListName::Setup(class ULoginMenuWidget* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	FriendButton->OnClicked.AddDynamic(this, &UFriendListName::OnClicked);
}

void UFriendListName::OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Found OnClicked %d"), Index);
	Parent->SelectIndex(Index);
}
