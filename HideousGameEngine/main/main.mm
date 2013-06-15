//
//  main.m
//  HideousGameEngine
//
//  Created by Sid on 02/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import "HideousEngine.h"
#import "Game.h"

int main(int argc, char *argv[]){
	GameAllocator ga(GLKVector3Make(0.5, 0.5, 0.5));
	return HideousEngineInit(argc, argv, ga);
}
