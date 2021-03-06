//////////////////////////////////////////////////////////////////////////////////////////////
/*
	FSMClientBase State machine
	
	File generated 17/05/2010 at 20:50:18
	
	Do not edit this file directly.
	Use Rapido! by Cedric Guillemet.
	
	Rapido! is licensed under GPLV2. Here is a copy of Rapido! License :
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; version 2 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
*/
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FSMClientBase_H__
#define FSMClientBase_H__

///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ZFSM.h"

#include "FSMClientFFA.h"
#include "FSMClientLanChoseShip.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

enum {
Type_NewGameSet,
Type_ServerMapLoaded,
Type_ClientMapLoaded

};

///////////////////////////////////////////////////////////////////////////////////////////////////




/*

*/
typedef struct NewGameSet
{

} NewGameSet;




/*

*/
typedef struct ServerMapLoaded
{

} ServerMapLoaded;




/*

*/
typedef struct ClientMapLoaded
{

} ClientMapLoaded;



///////////////////////////////////////////////////////////////////////////////////////////////////

class FSMClientBase : public ZFSM
{
public:
	FSMClientBase()
	{
		
		mGameMode = -1;
		mState = InitialState;
		EnterInitialState();
		
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	void Tick(float timeEllapsed);

	//////////////////////////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////////////////////////
	void Handle(const NewGameSet& mes)
{
	switch(mState)
	{
		case InitialState:
			HandleInitialState(mes);
			break;
		case LoadingMap:
			HandleLoadingMap(mes);
			break;
		case LoadingMapServerFinishedLoading:
			HandleLoadingMapServerFinishedLoading(mes);
			break;
		case MapLoaded:
			HandleMapLoaded(mes);
			break;
		case ReadyForGame:
			HandleReadyForGame(mes);
			break;
	}
}

void Handle(const ServerMapLoaded& mes)
{
	switch(mState)
	{
		case InitialState:
			HandleInitialState(mes);
			break;
		case LoadingMap:
			HandleLoadingMap(mes);
			break;
		case LoadingMapServerFinishedLoading:
			HandleLoadingMapServerFinishedLoading(mes);
			break;
		case MapLoaded:
			HandleMapLoaded(mes);
			break;
		case ReadyForGame:
			HandleReadyForGame(mes);
			break;
	}
}

void Handle(const ClientMapLoaded& mes)
{
	switch(mState)
	{
		case InitialState:
			HandleInitialState(mes);
			break;
		case LoadingMap:
			HandleLoadingMap(mes);
			break;
		case LoadingMapServerFinishedLoading:
			HandleLoadingMapServerFinishedLoading(mes);
			break;
		case MapLoaded:
			HandleMapLoaded(mes);
			break;
		case ReadyForGame:
			HandleReadyForGame(mes);
			break;
	}
}



	//////////////////////////////////////////////////////////////////////////////////////////////
protected:

	enum STATE
	{
	InitialState,
LoadingMap,
LoadingMapServerFinishedLoading,
MapLoaded,
ReadyForGame

	};

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	STATE mState;
	ZRushGame *mGame;
// All the sub FSM
FSMClientFFA mFSMClientFFA;
FSMClientLanChoseShip mFSMClientLCS;
FSMClientRaceStart mFSMClientRaceStart;
int mGameMode;

	//////////////////////////////////////////////////////////////////////////////////////////////
	
	void SetState(STATE newState)
	{
			switch(mState)
	{
		case InitialState:
			LeaveInitialState();
			break;
		case LoadingMap:
			LeaveLoadingMap();
			break;
		case LoadingMapServerFinishedLoading:
			LeaveLoadingMapServerFinishedLoading();
			break;
		case MapLoaded:
			LeaveMapLoaded();
			break;
		case ReadyForGame:
			LeaveReadyForGame();
			break;
	}
mState = newState;	switch(newState)
	{
		case InitialState:
			EnterInitialState();
			break;
		case LoadingMap:
			EnterLoadingMap();
			break;
		case LoadingMapServerFinishedLoading:
			EnterLoadingMapServerFinishedLoading();
			break;
		case MapLoaded:
			EnterMapLoaded();
			break;
		case ReadyForGame:
			EnterReadyForGame();
			break;
	}
		
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	inline void TickInitialState(float timeEllapsed)
{


}
inline void TickLoadingMap(float timeEllapsed)
{



}
inline void TickLoadingMapServerFinishedLoading(float timeEllapsed)
{


}
inline void TickMapLoaded(float timeEllapsed)
{


}
inline void TickReadyForGame(float timeEllapsed)
{

mFSMClientFFA.Tick(timeEllapsed);
mFSMClientLCS.Tick(timeEllapsed);
    
}

	
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	inline void EnterInitialState()
{


}
inline void EnterLoadingMap()
{

mFSMClientFFA.Init();
mFSMClientLCS.Init();
mFSMClientRaceStart.Init();
mGame->ShowHUD(false);
mGame->AllowInGameMenu(false);
GProtoGui->HideEndResults();
mGame->HandleNewGameSet();



}
inline void EnterLoadingMapServerFinishedLoading()
{


}
inline void EnterMapLoaded()
{

mGame->SendNetMessage(ZNMSG_ClientMapLoadingDone());
}
inline void EnterReadyForGame()
{



mGame->HandleLoadingDone();
gCameraMotion.SetCameraMapObserver();

bool bIsSoloGame = mGame->IsSoloGame();
// new sub state
switch (mGameMode)
{
case 0: // Raw
    mFSMClientFFA.mGame = mGame;
    mFSMClientFFA.SetState(FSMClientFFA::FFAAskSlot);
    GProtoGui->PlayNewMusic();
break;
case 1:// Classing Race
    if (bIsSoloGame)
    {
        mFSMClientFFA.mGame = mGame;
        mFSMClientFFA.SetState(FSMClientFFA::FFAAskSlot);
    }
    else
    {
        mFSMClientLCS.mGame = mGame;
        mFSMClientLCS.SetState(FSMClientLanChoseShip::PlayerOrSpectator);
    }
    GProtoGui->PlayNewMusic();
    break;
case 2: // menu
    //gCameraMotion.SetCameraMapObserver();
    gCameraMotion.SetCameraMapObserverMenu();
    GProtoGui->ShowMainMenu();
    GProtoGui->PlayNewMusic();
    break;
case 3: // Editor
    gCameraMotion.SetCameraUnused();
default:
break;
}
}

	
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	inline void LeaveInitialState()
{


}
inline void LeaveLoadingMap()
{


}
inline void LeaveLoadingMapServerFinishedLoading()
{


}
inline void LeaveMapLoaded()
{


}
inline void LeaveReadyForGame()
{


}

	
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	void HandleInitialState(const NewGameSet& mes)
{

}

void HandleInitialState(const ServerMapLoaded& mes)
{

}

void HandleInitialState(const ClientMapLoaded& mes)
{

}

void HandleLoadingMap(const NewGameSet& mes)
{
SetState(LoadingMap);
}

void HandleLoadingMap(const ServerMapLoaded& mes)
{

}

void HandleLoadingMap(const ClientMapLoaded& mes)
{

}

void HandleLoadingMapServerFinishedLoading(const NewGameSet& mes)
{
SetState(LoadingMap);
}

void HandleLoadingMapServerFinishedLoading(const ServerMapLoaded& mes)
{

}

void HandleLoadingMapServerFinishedLoading(const ClientMapLoaded& mes)
{

}

void HandleMapLoaded(const NewGameSet& mes)
{
SetState(LoadingMap);
}

void HandleMapLoaded(const ServerMapLoaded& mes)
{

}

void HandleMapLoaded(const ClientMapLoaded& mes)
{

}

void HandleReadyForGame(const NewGameSet& mes)
{
SetState(LoadingMap);
}

void HandleReadyForGame(const ServerMapLoaded& mes)
{

}

void HandleReadyForGame(const ClientMapLoaded& mes)
{

}


	
	//////////////////////////////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void FSMClientBase::Tick(float timeEllapsed)
{
	ZFSM::Tick(timeEllapsed);
	
		switch(mState)
	{
		case InitialState:
			TickInitialState(timeEllapsed);
			break;
		case LoadingMap:
			TickLoadingMap(timeEllapsed);
			break;
		case LoadingMapServerFinishedLoading:
			TickLoadingMapServerFinishedLoading(timeEllapsed);
			break;
		case MapLoaded:
			TickMapLoaded(timeEllapsed);
			break;
		case ReadyForGame:
			TickReadyForGame(timeEllapsed);
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif

