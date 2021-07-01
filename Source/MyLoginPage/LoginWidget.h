// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"



/**
 * 
 */
UCLASS()
class MYLOGINPAGE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UserSetup();
//public:
//		TMap<FString, UserData> UserMap;
//
//protected:
//	//virtual void BeginPlay() override;
//	void InitializeDummyUserLoginCredential();
//	
//	uint32 Size;
//	uint32 Index;
//	
//	//TMap<, UserData> UserMap;
//
//
//	UPROPERTY(meta = (BindWidget))
//		class UButton* LoginButton;
//
//	UPROPERTY(meta = (BindWidget))
//		class UTextBlock* ErrorMessage;
//
//	UPROPERTY(meta = (BindWidget))
//		class UEditableTextBox* UserNameEditableTextBox;
//
//	UPROPERTY(meta = (BindWidget))
//		class UEditableTextBox* PassWordEditableTextBox;
//
//
//	UPROPERTY(meta = (BindWidget))
//		class UWidgetSwitcher* LoginSwitcher;
//
//	UPROPERTY(meta = (BindWidget))
//		class UWidget* FriendPageWidget;
//
//	UPROPERTY(meta = (BindWidget))
//		class UPanelWidget* FriendList;
//	
//
//
//	UFUNCTION()
//	   void OnLoginButtonClicked();
//
//	void NativeConstruct() override;
//
//private:
//	
//	TSubclassOf<class UUserWidget> LoginClass;
//	/*TSubclassOf<class UUserWidget> FriendListClass;*/
//
//	class  ULoginMenuWidget* FriendMenu;
};
