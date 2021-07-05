// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendListName.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Slate/SlateBrushAsset.h"
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Engine/TextureRenderTarget2D.h"
#include "LoginMenuWidget.h"
#include "InChatWidget.h"


void UFriendListName::Setup(class ULoginMenuWidget* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	FString ImageURL = TEXT("https://d1nhio0ox7pgb.cloudfront.net/_img/v_collection_png/128x128/shadow/businessman.png");
	UAsyncTaskDownloadImage* ImageDownloadTask = NewObject<UAsyncTaskDownloadImage>();
	ImageDownloadTask->OnSuccess.AddDynamic(this, &UFriendListName::OnSetImage);
	ImageDownloadTask->Start(ImageURL);
	FriendButton->OnClicked.AddDynamic(this, &UFriendListName::OnFriendButtonClicked);
}

void UFriendListName::OnFriendButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("UFriendListName::OnFriendButtonClicked Found OnClicked= %d"), Index);
	FString GetFriendName= FriendName->GetText().ToString();
	Parent->SelectIndex(Index,GetFriendName);

}


void UFriendListName::OnSetImage(UTexture2DDynamic* Texture)
{
	UE_LOG(LogTemp, Warning, TEXT("UFriendListName::OnSetImage OsetImageCheck=%d"), Index);
	FriendImage->SetBrushFromTextureDynamic(Texture);
}