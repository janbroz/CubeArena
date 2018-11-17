// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeGameInstance.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/OnlineReplStructs.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <Engine/Engine.h>
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "OnlineSubsystemUtils.h"
#include "Player/MenuPlayerController.h"

UCubeGameInstance::UCubeGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentLocation = EPlayerLocation::MainMenu;

	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UCubeGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UCubeGameInstance::OnStartOnlineGameComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UCubeGameInstance::OnJoinSessionComplete);
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UCubeGameInstance::OnDestroySessionComplete);
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UCubeGameInstance::OnFindSessionsComplete);

	CurrentLocation = EPlayerLocation::MainMenu;
}


bool UCubeGameInstance::HostSession(FUniqueNetIdRepl UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid() && UserId.IsValid())
		{
			SessionSettings = MakeShareable(new FOnlineSessionSettings());

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			SessionSettings->Set(SETTING_MAPNAME, FString("Lobby"), EOnlineDataAdvertisementType::ViaOnlineService);
			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			return Sessions->CreateSession(*UserId, SessionName, *SessionSettings);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsytem found!"));
		}
		return false;
	}
	return false;
}


void UCubeGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
				Sessions->StartSession(SessionName);

				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("The session was good")));
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Holi"));
}

void UCubeGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
		if (bWasSuccessful)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Lobby", true, "listen");
			
		}
	}
}

void UCubeGameInstance::FindSessions(FUniqueNetIdRepl UserId, bool bIsLAN, bool bIsPresence)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid() && UserId.IsValid())
		{
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			
			SessionSearch->bIsLanQuery = bIsLAN;
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->PingBucketSize = 150;

			if (bIsPresence)
			{
				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
			}

			TSharedRef<FOnlineSessionSearch> SearchSettingRef = SessionSearch.ToSharedRef();

			OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			Sessions->FindSessions(*UserId, SearchSettingRef);
		}
	}
	else
	{
		OnFindSessionsComplete(false);
	}
}

void UCubeGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
			if (SessionSearch->SearchResults.Num() > 0)
			{
				BlueprintSessionResults.Empty();
				FString Str = FString::FromInt(SessionSearch->SearchResults.Num());
				UE_LOG(LogTemp, Warning, TEXT("The number is: %s"), *Str);
				for (int32 SearchIndx = 0; SearchIndx < SessionSearch->SearchResults.Num(); SearchIndx++)
				{
					 // Log something.
					FBlueprintSessionResult Result;
					Result.OnlineResult = SessionSearch->SearchResults[SearchIndx];
					BlueprintSessionResults.Add(Result);
				}
			}
		}
	}

	if (Cube_OnUpdateSessionsResultUI.IsBound())
	{
		Cube_OnUpdateSessionsResultUI.Broadcast();
	}
}

bool UCubeGameInstance::JoinSession(FUniqueNetIdRepl UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	CurrentLocation = EPlayerLocation::Lobby;
	bool bSuccessful = false;
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid() && UserId.IsValid())
		{
			OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			bSuccessful = Sessions->JoinSession(*UserId, SessionName, SearchResult);

			if (!bSuccessful)
			{
				CurrentLocation = EPlayerLocation::MainMenu;
			}
		}
	}

	return bSuccessful;
}

void UCubeGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			APlayerController* const PlayerController = GetFirstLocalPlayerController();
			FString TravelURL;
			if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
			{
				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
			}

			// Make sure that local players update the lobby widget correctly
			AMenuPlayerController* MenuPC = Cast<AMenuPlayerController>(PlayerController);
			if (MenuPC)
			{
				MenuPC->ShowLobby();
			}
		}
	}
}

void UCubeGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				UGameplayStatics::OpenLevel(GetWorld(), "MainMenu", true);
			}
		}
	}
}

void UCubeGameInstance::StartOnlineGame()
{
	CurrentLocation = EPlayerLocation::Lobby;
	ULocalPlayer* const Player = GetFirstGamePlayer();
	HostSession(Player->GetPreferredUniqueNetId(), GameSessionName, true, true, 4);
}

void UCubeGameInstance::FindOnlineGames()
{
	ULocalPlayer* const Player = GetFirstGamePlayer();
	FindSessions(Player->GetPreferredUniqueNetId(), true, true);
}

void UCubeGameInstance::JoinOnlineGame()
{
	ULocalPlayer* const Player = GetFirstGamePlayer();

	FOnlineSessionSearchResult SearchResult;
	if (SessionSearch->SearchResults.Num() > 0)
	{
		for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
		{
			if (SessionSearch->SearchResults[i].Session.OwningUserId != Player->GetPreferredUniqueNetId())
			{
				SearchResult = SessionSearch->SearchResults[i];
				JoinSession(Player->GetPreferredUniqueNetId(), GameSessionName, SearchResult);
				break;
			}
		}
	}
}

void UCubeGameInstance::DestroySessionAndLeaveGame()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
			Sessions->DestroySession(GameSessionName);
		}
	}
}

//FOnlineSessionSettings* UCubeGameInstance::GetCurrentSessionSettings()
//{
//	FOnlineSessionSettings* CurrentSettings = nullptr;
//	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
//	if (OnlineSubsystem)
//	{
//		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
//		if (Sessions.IsValid()) {
//			CurrentSettings = Sessions->GetSessionSettings(GameSessionName);
//		}
//	}
//	return CurrentSettings;
//}