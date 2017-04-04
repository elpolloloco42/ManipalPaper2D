// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper2DTestReseau.h"
#include "NetworkHandler.h"


// Sets default values
ANetworkHandler::ANetworkHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetworkHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetworkHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool	ANetworkHandler::InitConnection(FString nickname, FString address, FString port)
{
	this->_socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	FIPv4Address ip;
	bool success = FIPv4Address::Parse(address, ip);
	if (success == false)
		return false;
	TSharedRef<FInternetAddr>	addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(FCString::Atoi(*port));
	if (addr->IsValid() == false)
		return false;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Trying to connect to '") + ip.ToString() + "'...");
	bool connected = this->_socket->Connect(*addr);
	if (!connected)
		return false;

	FString serialized = TEXT("101 ") + nickname;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("sending '") + serialized + "'");
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar) + 1;
	int32 sent = 0;
	bool successful = this->_socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
	return (this->GetResponse());
}

bool ANetworkHandler::GetResponse()
{
	uint8 *data = (uint8*)TCHAR_TO_UTF8("");
	int32 size = 128;
	int32 read;
	this->_socket->Recv(data, size, read);
	FString serialized(read, UTF8_TO_TCHAR(data));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("received '") + serialized + "'");
	if (serialized.Compare("202") == 0)
		return false;
	return true;
}


void ANetworkHandler::CloseConnection()
{
	this->_socket->Close();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Connexion to server closed."));
}