// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/DataStructures.h"
#include "Online.h"
#include "FindSessionsCallbackProxy.h"
#include "CubeGameInstance.generated.h"


// Delegate to update the server sessions after a search
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionSearchFinishedDelegate);

/**
 * 
 */
UCLASS()
class CUBEARENA_API UCubeGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UCubeGameInstance(const FObjectInitializer& ObjectInitializer);
	
public:
	// Host a game
	bool HostSession(struct FUniqueNetIdRepl UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	void FindSessions(struct FUniqueNetIdRepl UserId, bool bIsLAN, bool bIsPresence);
	void OnFindSessionsComplete(bool bWasSuccessful);

	bool JoinSession(struct FUniqueNetIdRepl UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void StartOnlineGame();
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void FindOnlineGames();
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void JoinOnlineGame();
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void DestroySessionAndLeaveGame();

	/*UFUNCTION(BlueprintCallable, Category = "Network|Test")
		class FOnlineSessionSettings* GetCurrentSessionSettings();*/

public:
	// Delegates to manage the network responses.
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	// Handles for the session delegates
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	// Stores information about the game session.
	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	// Stores information about the search results.
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	// Update the UI and tell them to refresh the sessions list.
	FOnSessionSearchFinishedDelegate Cube_OnUpdateSessionsResultUI;

	// For blueprint communication
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<FBlueprintSessionResult> BlueprintSessionResults;

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		EPlayerLocation CurrentLocation;
};
