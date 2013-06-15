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

namespace he {
	
	Game::Game(GLKVector3 clear_color) :
	clear_color_(clear_color)
	{
		g_EventLoop = new EventLoop;
		g_AnimationLoop = new AnimationLoop;
		
		he_Trace("he::Game: loaded");
	}
	
	Game::~Game(){
		delete g_Screen;
		delete g_EventLoop;
		delete g_AnimationLoop;
		he_Trace("he::Game: unloaded");
	}
	
	void Game::Init(const GLKVector2 &window_size){
		g_Screen = new Screen(window_size.x, window_size.y);
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
	
	
	GameAllocator::GameAllocator(GLKVector3 clear_color) :
	clear_color_(clear_color),
	game_(nullptr)
	{}
	
	GameAllocator::~GameAllocator(){
		if(game_){
			delete game_;
		}
	}
	
	Game* GameAllocator::Allocate(const GLKVector2 &window_size){
		game_ = allocate(clear_color_);
		game_->Init(window_size);
		return game_;
	}
}
///EOF
