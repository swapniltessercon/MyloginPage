// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"



void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
   
	InitializeDummyUserLoginCredential();
	
	if (!ensure(LoginButton != nullptr)) return;
	LoginButton->OnClicked.AddUniqueDynamic(this, &ULoginWidget::OnLoginButtonClicked);
}


void ULoginWidget::InitializeDummyUserLoginCredential()
{
	UserData EData;
	//EData.UserName = "swap";
	EData.PassWord = "123";
	UserMap.Add("swap", EData);
	//EData.UserName = "xyz";
	EData.PassWord = "1234";
	UserMap.Add("xyz", EData);

}

void ULoginWidget::OnLoginButtonClicked()
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

	
   
