// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoginWidget.h"
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
	ULoginMenuWidget();
	

public:
	TMap<FString, UserData> UserMap;

protected:
	//virtual void BeginPlay() override;
	virtual bool Initialize() override;
	void InitializeDummyUserLoginCredential();
    void SetFriendList();

	uint32 Size;
	uint32 Index;

	

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

	//void NativeConstruct() override;

private:

	TSubclassOf<class UUserWidget> LoginClass;
	TSubclassOf<class UUserWidget> FriendListClass;

	


};
