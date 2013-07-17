//
//  TransformTest.h
//  HideousGameEngine
//
//  Created by Sid on 14/07/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__TransformTest__
#define __HideousGameEngine__TransformTest__
#include <memory>

#include <he/Main/HideousGame.h>
#include <he/Shaders/ColorShader.h>
#include <he/UI/GradientView.h>
#include <he/UI/View.h>

namespace he {
	class ColorShader;
	class Gradient;
	
	class View;
}

class Universe : public he::View {
public:
	Universe(const he::Transform &transform);
	virtual void Update(float dt);
	virtual void Render();	
private:
};

class HeavenlyBody : public he::GradientView {
public:
	HeavenlyBody(const he::Transform &transform, he::Gradient *grad, float speed);
	virtual void Update(float dt);
	virtual void Render();
private:
	float speed_;
};


class TransformTest : public he::Game {
public:
	
private:
	virtual void init();
	virtual void update(float dt);
	virtual void render();

	std::unique_ptr<he::ColorShader> shader_;
	std::unique_ptr<he::Gradient> gradient_;
	std::unique_ptr<Universe> universe_;
};

#endif /* defined(__HideousGameEngine__TransformTest__) */
