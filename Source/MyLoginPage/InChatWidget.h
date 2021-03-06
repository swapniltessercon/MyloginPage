// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoginWidget.h"
#include "InChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYLOGINPAGE_API UInChatWidget : public ULoginWidget
{
	GENERATED_BODY()

public:
	UInChatWidget(const FObjectInitializer& ObjectInitializer);
    void SetupInChatWidget(class ULoginMenuWidget* InParent, FString GetFrndName);
	void SendMessagetowidget();

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* MessageChatBox;

	class UMessageChatWidget* MessageRow;
	
protected:
	virtual bool Initialize() override;
	UFUNCTION()
	void OnSendMessageButtonClicked();

private:
	TSubclassOf<class UUserWidget> ChatListClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* SendMessageButton;

    UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* UserMessageEditableTextBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FrndName;

	class ULoginMenuWidget* LoginParent;

};
