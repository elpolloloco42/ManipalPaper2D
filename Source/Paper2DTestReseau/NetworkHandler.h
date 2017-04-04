// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "NetworkHandler.generated.h"

UCLASS()
class PAPER2DTESTRESEAU_API ANetworkHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetworkHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FSocket		*_socket;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Network")
		virtual bool	InitConnection(FString nickname, FString address, FString port);
	UFUNCTION(BlueprintCallable, Category = "Network")
		virtual void	CloseConnection();
		virtual bool	GetResponse();

};
