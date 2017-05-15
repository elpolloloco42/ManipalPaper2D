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
	uint32	size;

	FPlatformProcess::Sleep(1);
	while (!this->_finished)
	{
		size = 0;
		if (this->_socket->HasPendingData(size) == true) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("RECEIVEDATA WITH SIZE = ") + FString::FromInt(size));
			this->ReceiveData(size);
		}
		FPlatformProcess::Sleep(0.5);
	}
		return (0);
}

void		FServerListener::ReceiveData(uint32 size)
{
	uint8	data[100000];
	int32	bytes_read;
	FString	message;

	this->_socket->Recv(data, size, bytes_read);
	data[bytes_read] = 0;
	message = UTF8_TO_TCHAR(data);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(bytes_read) + TEXT(" bytes"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Received : " + message);
	this->_lastMessage = message;
	this->_messagePool.Push(message);
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