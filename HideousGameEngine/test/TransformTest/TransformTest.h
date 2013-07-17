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
	Universe(const he::Frame &frame) :
	View(frame)
	{}
	
	virtual void Update(float dt) {
		View::Update(dt);
	}
	
	virtual void Render() {
		View::Render();
	}
	
private:
};

class HeavenlyBody : public he::GradientView {
public:
	HeavenlyBody(const he::Frame &frame, he::Gradient *grad) :
	he::GradientView(frame, grad)
	{}
	
	virtual void Update(float dt) {
		GradientView::Update(dt);
	}
	
	virtual void Render() {
		GradientView::Render();
	}

private:
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
