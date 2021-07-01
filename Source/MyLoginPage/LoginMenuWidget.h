// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoginWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "LoginMenuWidget.generated.h"

struct UserData
{
	//FString UserName;
	FString PassWord;
};

/**
 * 
 */

UCLASS()
class MYLOGINPAGE_API ULoginMenuWidget : public ULoginWidget
{
	GENERATED_BODY()

public:

	ULoginMenuWidget(const FObjectInitializer& ObjectInitializer);

	TMap<FString, UserData> UserMap;
	void SelectIndex(uint32 Index);

	//UFUNCTION()
		void HTTPFunction();

	//UFUNCTION()
		void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
protected:
	virtual bool Initialize() override;
	void InitializeDummyUserLoginCredential();
    void SetFriendList();
	
	
	UPROPERTY(meta = (BindWidget))
		class UButton* LoginButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ErrorMessage;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* UserLoginName;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* UserNameEditableTextBox;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* PassWordEditableTextBox;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* LoginSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* FriendPageWidget;

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* FriendList;

	UFUNCTION()
		void OnLoginButtonClicked();


private:
	TSubclassOf<class UUserWidget> FriendListClass;
	TSubclassOf<class UUserWidget> FriendChatClass;
	TOptional<uint32> SelectedIndex;

	class ULoginWidget* LoginMenu;
	
	UPROPERTY()
		UUserWidget* FriendChatWidget;

};
