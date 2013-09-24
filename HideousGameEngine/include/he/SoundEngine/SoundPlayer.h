//
//  SoundPlayer.h
//  HideousGameEngine
//
//  Created by Sid on 22/09/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_SoundPlayer_h
#define HideousGameEngine_SoundPlayer_h
#include <string>

#define MAX_EFFECTS 10

namespace he{
	
	class Sound {
	public:
		Sound(const char *filename, const char *extn, int loop = -1);
		~Sound();

		void *player_;	// AVAudioPlayer
		std::string name_;
	};
	
	class SoundPlayer {
	public:
		SoundPlayer();
		~SoundPlayer();
		
		Sound *music;
		Sound *effects[MAX_EFFECTS];
		int effects_counter;
	};
	
	void SoundPlayer_PlayMusic(SoundPlayer *player, const char *filename, const char *extn);
	void SoundPlayer_PlayEffect(SoundPlayer *player, const char *filename, const char *extn, int repeat = 0);
	void SoundPlayer_StopAllEffects(SoundPlayer *player);

	extern SoundPlayer *g_SoundPlayer;
}


#endif
