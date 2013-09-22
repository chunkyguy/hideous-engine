//
//  HideousGame.cpp
//  HideousGameEngine
//
//  Created by Sid on 15/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Main/HideousGame.h>

#include <he/Animation/AnimationLoop.h>
#include <he/Utils/Utils.h>
#include <he/Utils/DebugHelper.h>
#include <he/Animation/AnimationLoop.h>
#include <he/EventLoop/Gesture.h>
#include <he/Utils/Screen.h>
#include <he/Font/Font.h>
#include <he/SoundEngine/SoundPlayer.h>

namespace he {
	
	void Game::Init(const GLKVector3 &clear_color, const GLKVector2 &window_size)	{
		clear_color_ = clear_color;

		g_Screen = new Screen(window_size.x, window_size.y);
		g_EventLoop = new EventLoop;
		g_AnimationLoop = new AnimationLoop;
		g_FontLib = new FontLibrary;
		g_SoundPlayer = new SoundPlayer;
		
		init();
		he_Trace("he::Game: loaded\n");
	}
	
	Game::~Game(){
		delete g_Screen;
		delete g_EventLoop;
		delete g_AnimationLoop;
		delete g_FontLib;
		delete g_SoundPlayer;
		he_Trace("he::Game: unloaded\n");
	}
		
	void Game::Update(float dt){
		// power the animation loop
		he::g_AnimationLoop->Update(dt);
		update(dt);
	}
	
	void Game::Render(){
		glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		render();
	}
	
	void Game::Pause(bool pause){
		
	}
	
	
	GameConfig::GameConfig(GLKVector3 clear_color) :
	clear_color_(clear_color),
	game_(nullptr)
	{}
	
	GameConfig::~GameConfig(){
		if(game_){
			delete game_;
		}
	}
	
	Game* GameConfig::CreateGame(const GLKVector2 &window_size){
		game_ = alloc_game();
		game_->Init(clear_color_, window_size);
		return game_;
	}
}
///EOF
