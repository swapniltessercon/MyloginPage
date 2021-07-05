// Fill out your copyright notice in the Description page of Project Settings.


#include "InChatWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"
#include "MessageChatWidget.h"
#include "LoginMenuWidget.h"




UInChatWidget::UInChatWidget(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ChatListBPClass(TEXT("/Game/LoginScreen/WBP_ChatMessage"));
	if (!ensure(ChatListBPClass.Class != nullptr)) return;
	ChatListClass = ChatListBPClass.Class;
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *ChatListClass->GetName());

}

void UInChatWidget::SetupInChatWidget(ULoginMenuWidget* InParent, FString GetFrndName )
{
	LoginParent = InParent;
	UE_LOG(LogTemp, Warning, TEXT("UInChatWidget::SetupInChatWidget Found FrndName= %s"), *GetFrndName);
	FrndName->SetText(FText::FromString(GetFrndName));
}



bool UInChatWidget::Initialize() {

	bool Success = Super::Initialize();
	if (!Success) return false;
	if (!ensure(SendMessageButton != nullptr)) return false;
	SendMessageButton->OnClicked.AddDynamic(this, &UInChatWidget::OnSendMessageButtonClicked);
	return true;
}

void UInChatWidget::OnSendMessageButtonClicked()
{
    UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	FString UserMessage = UserMessageEditableTextBox->GetText().ToString();
	if (!UserMessage.IsEmpty())
	{
		if (!ensure(LoginParent != nullptr)) return;
		LoginParent->FriendMessageSend(UserMessage);
	    MessageRow = CreateWidget<UMessageChatWidget>(World, ChatListClass);
		if (!ensure(MessageRow != nullptr)) return;
		UE_LOG(LogTemp, Warning, TEXT("UInChatWidget::SetupInChatWidget Found FrndName ...%s"), *UserMessage);
		MessageRow->UserMessage->SetText(FText::FromString(UserMessage));
		
	}
}

void UInChatWidget::SendMessagetowidget()
{
	MessageChatBox->AddChild(MessageRow);
	UserMessageEditableTextBox->SetText(FText::FromString(""));
}