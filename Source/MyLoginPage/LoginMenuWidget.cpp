// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginMenuWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "FriendListName.h"


ULoginMenuWidget::ULoginMenuWidget()
{

	ConstructorHelpers::FClassFinder<UUserWidget> FriendListBPClass(TEXT("/Game/LoginScreen/WBP_FriendRow"));
	if (!ensure(FriendListBPClass.Class != nullptr)) return;
	FriendListClass = FriendListBPClass.Class;
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *FriendListClass->GetName());
}


//void ULoginMenuWidget::NativeConstruct()
//{
	//Super::NativeConstruct();
bool ULoginMenuWidget::Initialize() {


	bool Success = Super::Initialize();
	UE_LOG(LogTemp, Warning, TEXT("Found class"))
	InitializeDummyUserLoginCredential();

	if (!ensure(LoginButton != nullptr)) return false;
	LoginButton->OnClicked.AddDynamic(this, &ULoginMenuWidget::OnLoginButtonClicked);
	return true;
}


void ULoginMenuWidget::InitializeDummyUserLoginCredential()
{
	UserData EData;
	//EData.UserName = "swap";
	EData.PassWord = "123";
	UserMap.Add("swap", EData);
	//EData.UserName = "xyz";
	EData.PassWord = "1234";
	UserMap.Add("xyz", EData);

}

void ULoginMenuWidget::OnLoginButtonClicked()
{
	if (!ensure(UserNameEditableTextBox != nullptr)) return;
	FString Username = UserNameEditableTextBox->GetText().ToString();
	if (!ensure(PassWordEditableTextBox != nullptr)) return;
	const FString& Password = PassWordEditableTextBox->GetText().ToString();

	UserData* FoundUserData = UserMap.Find(Username);
	if (FoundUserData != nullptr)
	{
		if (Password == FoundUserData->PassWord)
		{
			ErrorMessage->SetText(FText::FromString("login SuccessFully"));


			if (!ensure(LoginSwitcher != nullptr)) return;
			if (!ensure(FriendPageWidget != nullptr)) return;
			LoginSwitcher->SetActiveWidget(FriendPageWidget);
			SetFriendList();

		}
		else
		{
			ErrorMessage->SetText(FText::FromString("Please Enter The Correct Password "));
		}
	}
	else
	{
		ErrorMessage->SetText(FText::FromString("Please Enter The Correct UserName "));
	}
}


void ULoginMenuWidget::SetFriendList() {

	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;
	FString Username = UserNameEditableTextBox->GetText().ToString();
	UserLoginName->SetText(FText::FromString(Username));
	
	if (!ensure(FriendListClass != nullptr)) return;

	for (auto It = UserMap.CreateConstIterator(); It; ++It)
	{
		UFriendListName* FriendRow = CreateWidget<UFriendListName>(World, FriendListClass);
		if (!ensure(FriendRow != nullptr)) return;

		FriendRow->FriendName->SetText(FText::FromString(It.Key()));

		FriendList->AddChild(FriendRow);
	}

	


}




