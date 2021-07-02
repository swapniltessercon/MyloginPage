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

void UInChatWidget::SetupInChatWidget(ULoginMenuWidget* InParent)
{
	LoginParent = InParent;
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
		UMessageChatWidget* MessageRow = CreateWidget<UMessageChatWidget>(World, ChatListClass);
		if (!ensure(MessageRow != nullptr)) return;	

		if (!ensure(LoginParent != nullptr)) return;
		LoginParent->FriendMessageSend(UserMessage);

		MessageRow->UserMessage->SetText(FText::FromString(UserMessage));	   
		UserMessageEditableTextBox->SetText(FText::FromString(""));
		MessageChatBox->AddChild(MessageRow);
	}
}