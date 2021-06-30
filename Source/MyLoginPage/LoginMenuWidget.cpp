// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginMenuWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Components/TextBlock.h"
#include "FriendListName.h"


ULoginMenuWidget::ULoginMenuWidget()
{

	ConstructorHelpers::FClassFinder<UUserWidget> FriendListBPClass(TEXT("/Game/LoginScreen/WBP_FriendRow"));
	if (!ensure(FriendListBPClass.Class != nullptr)) return;
	FriendListClass = FriendListBPClass.Class;
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *FriendListClass->GetName());


	ConstructorHelpers::FClassFinder<UUserWidget> FriendChatBPClass(TEXT("/Game/LoginScreen/WBP_ChatWindow"));
	if (!ensure(FriendChatBPClass.Class != nullptr)) return;
	FriendChatClass = FriendChatBPClass.Class;
	
	

	//UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *FriendChatClass->GetName());
}

bool ULoginMenuWidget::Initialize() 
{


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
	UserMap.Add("Ronaldo", EData);
	EData.PassWord = "1245";
	UserMap.Add("Messi", EData);


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
			PassWordEditableTextBox->SetText(FText::FromString(""));
			UserNameEditableTextBox->SetText(FText::FromString(""));
		}
	}
	else
	{
		ErrorMessage->SetText(FText::FromString("Please Enter The Correct UserName "));
		PassWordEditableTextBox->SetText(FText::FromString(""));
		UserNameEditableTextBox->SetText(FText::FromString(""));
	}
}


void ULoginMenuWidget::SetFriendList() 
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;
	FString Username = UserNameEditableTextBox->GetText().ToString();
	UserLoginName->SetText(FText::FromString(Username));
	if (!ensure(FriendListClass != nullptr)) return;
	uint32 i = 0;
	for (auto It = UserMap.CreateConstIterator(); It; ++It)
	{
		if (Username != It.Key())
		{
			UFriendListName* FriendRow = CreateWidget<UFriendListName>(World, FriendListClass);
			if (!ensure(FriendRow != nullptr)) return;
			FriendRow->FriendName->SetText(FText::FromString(It.Key()));
			FriendRow->Setup(this, i);
			++i;
			FriendList->AddChild(FriendRow);
		}
	}
}


void ULoginMenuWidget::SelectIndex(uint32 Index, FString FrndName)
{
	SelectedIndex = Index;
	UE_LOG(LogTemp, Warning, TEXT("Selected index %d."), SelectedIndex.GetValue());
	if (!ensure(FriendChatClass != nullptr)) return;
	Widget = CreateWidget(GetWorld(), FriendChatClass);
	Widget->AddToViewport();
}


//void ULoginMenuWidget::OnSetImage(UTexture2DDynamic* Texture)
//{
//
//	UE_LOG(LogTemp, Warning, TEXT("onsetImage"));
//	UWorld* World = this->GetWorld();
//	if (!ensure(World != nullptr)) return;
//	UFriendListName* FriendRow = CreateWidget<UFriendListName>(World, FriendListClass);
//	FriendRow->FriendImage->SetBrushFromTextureDynamic(Texture);
////	FriendList->AddChild(FriendRow);
//}


