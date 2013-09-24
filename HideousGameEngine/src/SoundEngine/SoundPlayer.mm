//
//  SoundPlayer.m
//  HideousGameEngine
//
//  Created by Sid on 22/09/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/SoundEngine/SoundPlayer.h>

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#include <he/Utils/ResourcePath.hpp>

namespace he {
 
 /********************************************************************************************************************************
  * MARK: Utilities
  ********************************************************************************************************************************/
 namespace {
  
  bool Sound_IsPlaying(Sound *sound) {
   return ([(AVAudioPlayer*)sound->player_ isPlaying]) ? true : false;
  }
  
  void Sound_Play(Sound *sound) {
   if (!Sound_IsPlaying(sound)) {
    [(AVAudioPlayer*)sound->player_ play];
   }
  }
  void Sound_Pause(Sound *sound) {
   if (Sound_IsPlaying(sound)) {
    [(AVAudioPlayer*)sound->player_ pause];
   }
  }
  void Sound_Stop(Sound *sound) {
   if (Sound_IsPlaying(sound)) {
    [(AVAudioPlayer*)sound->player_ stop];
   }
  }
  
  void Sound_SetRepeat(Sound *sound, int repeat) {
   [(AVAudioPlayer*)sound->player_ setNumberOfLoops:repeat];
  }
  
  AVAudioPlayer * LoadSound(const char *filepath){
   NSURL *url = [NSURL fileURLWithPath:[NSString stringWithUTF8String:filepath]];
   assert(url);
   
   NSError *error = nil;
   AVAudioPlayer *sound_player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
   assert(!error);
   
   return sound_player;
  }
 }
 
 /********************************************************************************************************************************
  * MARK: Sound
  ********************************************************************************************************************************/
 Sound::Sound(const char *filepath, int loop) :
 player_(LoadSound(filepath)),
 name_(filepath)
 {
  [(AVAudioPlayer*)player_ setNumberOfLoops:loop];
  [(AVAudioPlayer*)player_ prepareToPlay];
 }
 
 Sound::~Sound() {
  if ([(AVAudioPlayer*)player_ isPlaying]) {
   [(AVAudioPlayer*)player_ stop];
  }
  [(AVAudioPlayer*)player_ release];
  player_ = 0;
 }
 
 
 /********************************************************************************************************************************
  * MARK: SoundPlayer
  ********************************************************************************************************************************/
 
 SoundPlayer::SoundPlayer() :
 music(0),
 effects(),
 effects_counter(0)
 {
  for (int i = 0; i < MAX_EFFECTS; ++i) {
   effects[i] = 0;
  }
 }
 
 SoundPlayer::~SoundPlayer() {
  delete music;
  for (int i = 0; i < MAX_EFFECTS; ++i) {
   if (effects[i]) {
    delete effects[i];
   }
  }
 }
 
 void SoundPlayer_StopAllEffects(SoundPlayer *player) {
  for (int i = 0; i < MAX_EFFECTS; ++i) {
   if (player->effects[i]) {
    Sound_Stop(player->effects[i]);
   }
  }
 }
 
 void SoundPlayer_PlayMusic(SoundPlayer *player, const char *filepath) {
  if (player->music) {
   if (player->music->name_ == filepath) {
    if (!Sound_IsPlaying(player->music)) {
     Sound_Play(player->music);
    }
    return;	// Must be playing already
   }
   // Must be loading a new sound as music, delete the older one, as only one music file is allowed to play
   delete player->music;
  }
  player->music = new Sound(filepath);
  Sound_Play(player->music);
 }
 
 void SoundPlayer_PlayEffect(SoundPlayer *player, const char *filepath, int repeat) {
  // Search if already loaded
  for (int i = 0; i < MAX_EFFECTS; ++i) {
   Sound *s = player->effects[i];
   if (s && (s->name_ == filepath)) {
    if(!Sound_IsPlaying(s)) {	// If not playing, play
     Sound_SetRepeat(s, repeat);
     Sound_Play(s);
     return;
    }
   }
  }
  
  // Not loaded or loaded but playing.
  // Find a empty slot and play (again)
  for (int i = 0; i < MAX_EFFECTS; ++i) {
   if (player->effects[i] == 0) {
    player->effects[i] = new Sound(filepath, repeat);
    Sound_Play(player->effects[i]);
    return;
   }
  }
  
  // All slot occupied.
  // Search a non-playing slot and play
  for (int i = 0; i < MAX_EFFECTS; ++i) {
   if (Sound_IsPlaying(player->effects[i])) {
    delete player->effects[i];
    player->effects[i] = new Sound(filepath, repeat);
    Sound_Play(player->effects[i]);
    return;
   }
  }
 }
 
 SoundPlayer *g_SoundPlayer = nullptr;
 
} /* namespace he*/


// EOF
