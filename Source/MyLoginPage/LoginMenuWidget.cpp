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
#include "InChatWidget.h"
#include "HttpModule.h"
#include "Http.h"
#include "Json.h"
#include "Interfaces/IHttpRequest.h"




ULoginMenuWidget::ULoginMenuWidget(const FObjectInitializer& ObjectInitializer)
{

	ConstructorHelpers::FClassFinder<UUserWidget> FriendListBPClass(TEXT("/Game/LoginScreen/WBP_FriendRow"));
	if (!ensure(FriendListBPClass.Class != nullptr)) return;
	FriendListClass = FriendListBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> FriendChatBPClass(TEXT("/Game/LoginScreen/WBP_ChatWindow"));
	if (!ensure(FriendChatBPClass.Class != nullptr)) return;
	FriendChatClass = FriendChatBPClass.Class;
}

bool ULoginMenuWidget::Initialize() 
{
	bool Success = Super::Initialize();

	UE_LOG(LogTemp, Warning, TEXT("Found class"))
	InitializeDummyUserLoginCredential();
	LoginButton->OnClicked.AddDynamic(this, &ULoginMenuWidget::OnLoginButtonClicked);
	return true;
	
}


void ULoginMenuWidget::InitializeDummyUserLoginCredential()
{
	UserData EData;
	EData.PassWord = "123";
	UserMap.Add("swap", EData);
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
	FString Password = PassWordEditableTextBox->GetText().ToString();

    FString HttpUrl = TEXT("https://matrix-client.matrix.org/_matrix/client/r0/login");
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginMenuWidget::OnResponseReceived);
	HttpRequest->SetURL(HttpUrl);
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/json");
	FString UserLoginJsonBody = FString::Printf(TEXT("{\"type\":\"m.login.password\", \"user\":\"%s\", \"password\":\"8bvDhCd7idq4y$P\"}"), *Username);
	
	//HttpRequest->SetContentAsString("{\"type\":\"m.login.password\", \"user\":\"swapnil_tessercon\", \"password\":\"8bvDhCd7idq4y$P\"}");
	UE_LOG(LogTemp, Warning, TEXT("ULoginMenuWidget::OnLoginButtonClicked  Login =  .. %s"),*UserLoginJsonBody)
	HttpRequest->SetContentAsString(UserLoginJsonBody);
	HttpRequest->ProcessRequest();

}

void ULoginMenuWidget::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("HTTPResponse for login .. %s"), *Response->GetContentAsString());

	if (Response->GetResponseCode() == 200)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			AccessToken1 = JsonObject->GetStringField(TEXT("access_token"));
			UE_LOG(LogTemp, Warning, TEXT("HTTPResponse for login .. %s"), *AccessToken1);
		}

		if (LoginButton != nullptr)
		{
			if (!ensure(FriendPageWidget != nullptr)) return;
			LoginSwitcher->SetActiveWidget(FriendPageWidget);
			SetFriendList();
		}
	}
}


void ULoginMenuWidget::SetFriendList() 
{
	UWorld* World = GetWorld();
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


void ULoginMenuWidget::SelectIndex(uint32 Index)
{

	if (FriendChatWidget != nullptr)
	{
		FriendChatWidget->RemoveFromViewport();
		FriendChatWidget = nullptr;
	}

	if (!ensure(FriendChatClass != nullptr)) return;
	FriendChatWidget = CreateWidget(GetWorld(), FriendChatClass);

	if (FriendChatWidget != nullptr)
	{
		
		UInChatWidget* FriendChatWidgetActual = Cast<UInChatWidget>(FriendChatWidget);
		if (FriendChatWidgetActual != nullptr)
		{
			FriendChatWidgetActual->SetupInChatWidget(this);
			FriendChatWidgetActual->AddToViewport();
		}
	}
}




void ULoginMenuWidget::FriendMessageSend(FString FrndMessge)
{
	UE_LOG(LogTemp, Warning, TEXT("HTTPResponse for login .. %s"), *FrndMessge)
	UE_LOG(LogTemp, Warning, TEXT("ULoginMenuWidget::FriendMessageSend  AccessToken =  .. %s"), *AccessToken1)

	FString HttpAccessTokenUrl = TEXT("https://matrix-client.matrix.org/_matrix/client/r0/rooms/!hikUCgTbSkfhynJAnG:matrix.org/send/m.room.message?access_token=");
	HttpAccessTokenUrl += AccessToken1;

	UE_LOG(LogTemp, Warning, TEXT("ULoginMenuWidget::FriendMessageSend  AccessTokenURL =  .. %s"), *HttpAccessTokenUrl)
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ULoginMenuWidget::OnMessageResponseReceived);
	HttpRequest->SetURL(HttpAccessTokenUrl);
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/json");
	FString FrndJsonBodyMessage = FString::Printf(TEXT("{\"msgtype\":\"m.text\", \"body\":\"%s\"}"), *FrndMessge);
	UE_LOG(LogTemp, Warning, TEXT("ULoginMenuWidget::FriendMessageSend  FRNDMEssageBOdy =  .. %s"), *FrndJsonBodyMessage)
	HttpRequest->SetContentAsString(FrndJsonBodyMessage);
	HttpRequest->ProcessRequest();
}

void ULoginMenuWidget::OnMessageResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	


}





