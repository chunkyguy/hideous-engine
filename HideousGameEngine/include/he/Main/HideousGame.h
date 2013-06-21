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
	
	/** The base class for any Game object.
	 */
	class Game{
	public:
		/** Contructs a Game Object.
		 Does some basic stuffs like creating global vars, powering the AnimationLoop.
		 
		 @param clear_color The color to be used to flush the screen.
		 @param window_size The size of the window calculated.

		 @warning Don't call this directly. Expected to be called from GameConfig with necessary params.
		Instead subclass it and implement the virtual methods.
		 */
		void Init(const GLKVector3 &clear_color, const GLKVector2 &window_size);

		virtual ~Game();

		void Update(float dt);
		void Render();
		void Pause(bool pause);
		
	private:
		/** Start the game
		 At this point all the underground tasks are assumed to be over.
		 All the global vars are created and initialized.
		 */
		virtual void init() = 0;
		
		/** Supply the power to your game.
		 The animation engine and all the other (future) necessary elements of the engine
		 will be powered up
		 */
		virtual void update(float dt) = 0;
		
		/** Render all the entites
		 */
		virtual void render() = 0;
		
		GLKVector3 clear_color_;
	};
	

	/** Initialize the game creating process.
		Handles all the basic works, like window loading, and passes the control to allocate the game
		Subclass this, and proved the actual allocator for the actual game.
	 
		The actual purpose of this class is to provide an easy RAII mechanism to hold Game instance.
		Something as simple as this this:
	 
			int main(int argc, char *argv[])
			{
				MyGameConfig gc(GLKVector3Make(0.5, 0.5, 0.5));
				return HideousEngineInit(argc, argv, gc);
			}

	 */
	class GameConfig {
	public:
		/** Contruct the GameAllocator.
		 @param clear_color The color to be flushed at each render.
		 @note The params are expected to increase with time. 
		 Basically, they are the necessary configurations to handle the window and stuff.
		 */
		explicit GameConfig(GLKVector3 clear_color);
		virtual ~GameConfig();
		
		/** Actually create the game.
			Expected to be called from HideousEngine::HELoop after all the basic config is done.
		 */
		Game* CreateGame(const GLKVector2 &window_size);
		
	private:
		/** Override this method to allocate the actual game.
		 @warning Just do the memory allocation.
		 */
		virtual Game* alloc_game() = 0;
		
		GLKVector3 clear_color_;
		Game *game_;
		
		/** Disallow creating an object with default ctor, copy ctor or assignment operator.
		 */
		GameConfig();
		DISALLOW_COPY_AND_ASSIGN(GameConfig);
	};
}
#endif
