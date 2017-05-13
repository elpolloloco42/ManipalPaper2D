// Fill out your copyright notice in the Description page of Project Settings.

#include "Paper2DTestReseau.h"
#include "FServerListener.h"

FServerListener* FServerListener::Runnable = NULL;

FServerListener::FServerListener(FSocket *socket)
{
	this->_socket = socket;
	this->_finished = false;
	this->_thread = FRunnableThread::Create(this, TEXT("FServerListener"), 0, TPri_BelowNormal);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("THREAD STARTED !!"));
}

FServerListener::~FServerListener()
{
	if (this->_thread) {
		this->_thread->Kill(true);
		delete this->_thread;
		this->_thread = nullptr;
	}
}



bool FServerListener::Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Init"));
	return true;
}

uint32		FServerListener::Run()
{
	uint8	*data = (uint8*)TCHAR_TO_UTF8("");
	uint32	size = 0;
	int32	read = 0;
	FString	message;

	FPlatformProcess::Sleep(1);
	while (!this->_finished)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.4f, FColor::Yellow, TEXT("Trying to receive..."));
		while (this->_socket->HasPendingData(size) == true) {
			/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("SOMETHING TO READ"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(size) + TEXT("bytes to get"));*/
			this->_socket->Recv(data, size, read);
			message = UTF8_TO_TCHAR(data);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Received"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(read) + TEXT(" bytes"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Received : " + message);
			this->_lastMessage = message;
			this->_messagePool.Push(message);
			//else
			//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("Nothing to read on the server"));
		}
		FPlatformProcess::Sleep(0.5);
	}
		return (0);
}

FString		FServerListener::GetLastMessage()
{
	if (this->_messagePool.Num() == 0)
		return FString("");
	return this->_messagePool.Pop();
}

void FServerListener::Stop()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Stop"));
}

FServerListener	*FServerListener::StartThread(FSocket *socket)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading()) {
		Runnable = new FServerListener(socket);
	}
	return Runnable;
}

void FServerListener::Finish()
{
	this->_finished = true;
	if (this->Runnable) {
		delete Runnable;
		Runnable = NULL;
	}
}