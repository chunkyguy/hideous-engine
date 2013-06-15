//
//  HideousGame.h
//  HideousGameEngine
//
//  Created by Sid on 15/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_HideousGame_h
#define HideousGameEngine_HideousGame_h
#include <he/Utils/GLKMath_Additions.h>
#include <he/Utils/Utils.h>

namespace he {
	
	
	class Game{
	public:
		Game(GLKVector3 clear_color);
		virtual ~Game();
		void Init(const GLKVector2 &window_size);
		void Update(float dt);
		void Render();
		void Pause(bool pause);
		
	private:
		virtual void update(float dt) = 0;
		virtual void render() = 0;
		
		GLKVector3 clear_color_;
	};
	
	
	class GameAllocator {
	public:
		explicit GameAllocator(GLKVector3 clear_color);
		virtual ~GameAllocator();
		Game* Allocate(const GLKVector2 &window_size);
		
	private:
		GameAllocator();
		virtual Game* allocate(const GLKVector3 &clear_color) = 0;
		
		GLKVector3 clear_color_;
		Game *game_;
		
		DISALLOW_COPY_AND_ASSIGN(GameAllocator);
	};
}
#endif
