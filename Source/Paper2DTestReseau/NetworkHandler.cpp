// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper2DTestReseau.h"
#include "NetworkHandler.h"


// Sets default values
ANetworkHandler::ANetworkHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->_socket = NULL;
	this->_serverListener = NULL;
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
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Trying to connect to '") + ip.ToString() + "'...");
	bool connected = this->_socket->Connect(*addr);
	if (!connected)
		return false;
	//this->_serverListener = FServerListener::StartThread(this->_socket);
	return true;
}

bool	ANetworkHandler::GetResponse()
{
	uint8	*data = (uint8*)TCHAR_TO_UTF8("");
	uint32	size = 0;
	int32	read = 0;
	FString	message;

	while (this->_socket->HasPendingData(size) == false)
		true;
	this->_socket->Recv(data, size, read);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Received : ") + FString::FromInt(read));
	message = UTF8_TO_TCHAR(data);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("message : ") + message);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("size : ") + FString::FromInt(size));
	if (size > 3)
		this->ExtractMessage(message, size);
	if (message.Contains("201") == true)
		return true;
	else
		return false;
}

void	ANetworkHandler::ExtractMessage(FString message, int size)
{
	FString	newMessage;
	int		i = 4;

	while (i != size)
		newMessage += message[i++];
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Adding : ") + newMessage);
	this->_lastMessage = newMessage;
}

FString	ANetworkHandler::GetLastMessage()
{
	return this->_lastMessage;
	//	return this->_serverListener->GetLastMessage();
}

void	ANetworkHandler::Send101(FString nickName)
{
	FString serialized = TEXT("101 ") + nickName;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("sending '") + serialized + "'");
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar) + 1;
	int32 sent = 0;
	this->_socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void	ANetworkHandler::Send102()
{
	FString serialized = TEXT("102");
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar) + 1;
	int32 sent = 0;
	this->_socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void	ANetworkHandler::Send103(FString lobbyName)
{
	FString serialized = TEXT("103 ") + lobbyName;
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar) + 1;
	int32 sent = 0;
	this->_socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void	ANetworkHandler::Send104(FString lobbyName)
{
	FString serialized = TEXT("103 ") + lobbyName;
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar) + 1;
	int32 sent = 0;
	this->_socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void ANetworkHandler::CloseSocket()
{
	if (this->_socket)
		this->_socket->Close();
}

void	ANetworkHandler::CloseThread()
{
	this->_serverListener->Finish();
}