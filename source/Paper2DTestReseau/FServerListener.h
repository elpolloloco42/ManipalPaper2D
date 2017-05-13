// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include	"Sockets.h"
#include	"Array.h"

/**
 * 
 */
class PAPER2DTESTRESEAU_API FServerListener : public FRunnable
{
	static  FServerListener	*Runnable;

public:
	FServerListener(FSocket *socket);
	virtual ~FServerListener();

	static FServerListener	*StartThread(FSocket *socket);

	FSocket		*_socket;
	FRunnableThread* _thread;
	bool		_finished;
	FString		_lastMessage;
	TArray<FString>		_messagePool;

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	virtual FString GetLastMessage();

	virtual void Finish();

};
