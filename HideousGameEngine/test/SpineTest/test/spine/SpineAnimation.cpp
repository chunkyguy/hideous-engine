/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include "SpineAnimation.h"
#include <math.h>
#include <he/Utils/GLKMath_Additions.h>

#include "Bone.h"
#include "Skeleton.h"

namespace spine {
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Animation
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Animation::Animation (std::string name, int timelineCount) :
	duration_(0.0),
	name_(name),
	timeline_count_(timelineCount),
	timelines_(new Timeline *[timelineCount])
	{	}
	
	Animation::~Animation () {
		for (int i = 0; i < timeline_count_; ++i)
			delete timelines_[i];
		delete [] timelines_;
	}
	
	void Animation::Apply (Skeleton* skeleton, float time, bool loop) {
		int i, n = timeline_count_;
		
#ifdef __STDC_VERSION__
		if (loop && duration_) time = fmodf(time, duration_);
#else
		if (loop && duration_) time = (float)fmod(time, duration_);
#endif
		
		for (i = 0; i < n; ++i){
			timelines_[i]->Apply(skeleton, time, 1);
		}
	}
	
	void Animation::Mix ( Skeleton* skeleton, float time, bool loop, float alpha) const{
		int i, n = timeline_count_;
		
#ifdef __STDC_VERSION__
		if (loop && duration_) time = fmodf(time, duration_);
#else
		if (loop && duration_) time = (float)fmod(time, duration_);
#endif
		
		for (i = 0; i < n; ++i){
			timelines_[i]->Apply(skeleton, time, alpha);
		}
	}
	void Animation::SetDuration(float duration){
		duration_ = duration;
	}
	float Animation::GetDuration(){
		return duration_;
	}
	
	int Animation::GetTimelineCount(){
		return timeline_count_;
	}
	void Animation::SetTimelineCount(int count){
		timeline_count_ = count;
	}
	std::string Animation::GetName(){
		return name_;
	}
	void Animation::SetTimelineAtIndex(Timeline *timeline, int index){
		timelines_[index] = timeline;
	}
	/**/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: CurveTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**/
	
	static const float CURVE_LINEAR = 0;
	static const float CURVE_STEPPED = -1;
	static const int CURVE_SEGMENTS = 10;
	
	CurveTimeline::CurveTimeline ( int frameCount) :
	curves_ ( new float[(frameCount - 1) * 6])
	{	}
	
	CurveTimeline::~CurveTimeline () {
		delete [] curves_;
	}
	
	void CurveTimeline::SetLinear ( int frameIndex) {
		curves_[frameIndex * 6] = CURVE_LINEAR;
	}
	
	void CurveTimeline::SetStepped ( int frameIndex) {
		curves_[frameIndex * 6] = CURVE_STEPPED;
	}
	
	void CurveTimeline::SetCurve ( int frameIndex, float cx1, float cy1, float cx2, float cy2) {
		float subdiv_step = 1.0f / CURVE_SEGMENTS;
		float subdiv_step2 = subdiv_step * subdiv_step;
		float subdiv_step3 = subdiv_step2 * subdiv_step;
		float pre1 = 3 * subdiv_step;
		float pre2 = 3 * subdiv_step2;
		float pre4 = 6 * subdiv_step2;
		float pre5 = 6 * subdiv_step3;
		float tmp1x = -cx1 * 2 + cx2;
		float tmp1y = -cy1 * 2 + cy2;
		float tmp2x = (cx1 - cx2) * 3 + 1;
		float tmp2y = (cy1 - cy2) * 3 + 1;
		int i = frameIndex * 6;
		curves_[i] = cx1 * pre1 + tmp1x * pre2 + tmp2x * subdiv_step3;
		curves_[i + 1] = cy1 * pre1 + tmp1y * pre2 + tmp2y * subdiv_step3;
		curves_[i + 2] = tmp1x * pre4 + tmp2x * pre5;
		curves_[i + 3] = tmp1y * pre4 + tmp2y * pre5;
		curves_[i + 4] = tmp2x * pre5;
		curves_[i + 5] = tmp2y * pre5;
	}
	
	float CurveTimeline::GetCurvePercent (int frameIndex, float percent) const{
		float dfy;
		float ddfx;
		float ddfy;
		float dddfx;
		float dddfy;
		float x, y;
		int i;
		int curveIndex = frameIndex * 6;
		float dfx = curves_[curveIndex];
		if (dfx == CURVE_LINEAR) return percent;
		if (dfx == CURVE_STEPPED) return 0;
		dfy = curves_[curveIndex + 1];
		ddfx = curves_[curveIndex + 2];
		ddfy = curves_[curveIndex + 3];
		dddfx = curves_[curveIndex + 4];
		dddfy = curves_[curveIndex + 5];
		x = dfx, y = dfy;
		i = CURVE_SEGMENTS - 2;
		while (1) {
			if (x >= percent) {
				float lastX = x - dfx;
				float lastY = y - dfy;
				return lastY + (y - lastY) * (percent - lastX) / (x - lastX);
			}
			if (i == 0) break;
			i--;
			dfx += ddfx;
			dfy += ddfy;
			ddfx += dddfx;
			ddfy += dddfy;
			x += dfx;
			y += dfy;
		}
		return y + (1 - y) * (percent - x) / (1 - x); /* Last point is 1,1. */
	}
	
	/* @param target After the first and before the last entry. */
	static int binarySearch (float *values, int valuesLength, float target, int step) {
		int low = 0, current;
		int high = valuesLength / step - 2;
		if (high == 0) return step;
		current = high >> 1;
		while (1) {
			if (values[(current + 1) * step] <= target)
				low = current + 1;
			else
				high = current;
			if (low == high) return (low + 1) * step;
			current = (low + high) >> 1;
		}
		return 0;
	}
	
	/*static int linearSearch (float *values, int valuesLength, float target, int step) {
	 int i, last = valuesLength - step;
	 for (i = 0; i <= last; i += step) {
	 if (values[i] <= target) continue;
	 return i;
	 }
	 return -1;
	 }*/
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: BaseTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Many timelines have structure identical to struct BaseTimeline and extend CurveTimeline. **/
	BaseTimeline::BaseTimeline (int frameCount, int frameSize) :
	CurveTimeline(frameCount),
	frames_(nullptr),
	frames_length_(frameCount * frameSize)
	{
		frames_ = new float[frames_length_];
	}
	
	BaseTimeline::~BaseTimeline() {
		delete [] frames_;
	}

	float BaseTimeline::GetFrameAtIndex(int index){
		return frames_[index];
	}
	void BaseTimeline::SetFrameAtIndex(float v, int index){
		frames_[index] = v;
	}
	int BaseTimeline::GetFramesLength(){
		return frames_length_;
	}
	float *BaseTimeline::GetFrames(){
		return frames_;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: BoneBaseTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	BoneBaseTimeline::BoneBaseTimeline (int frameCount, int frameSize) :
	BaseTimeline(frameCount, frameSize),
	bone_index_(0)
	{}
	
	void BoneBaseTimeline::SetFrame( int , float , float , float ){
		assert(0); /*this method should have been implemented*/
	}

	int BoneBaseTimeline::GetBoneIndex(){
		return bone_index_;
	}
	void BoneBaseTimeline::SetBoneIndex(int index){
		bone_index_ = index;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: SlotBaseTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	SlotBaseTimeline::SlotBaseTimeline (int frameCount, int frameSize) :
	BaseTimeline(frameCount, frameSize),
	slot_index_(0)
	{}
	
	int SlotBaseTimeline::GetSlotIndex(){
		return slot_index_;
	}
	void SlotBaseTimeline::SetSlotIndex(int index){
		slot_index_ = index;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: RotateTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static const int ROTATE_LAST_FRAME_TIME = -2;
	static const int ROTATE_FRAME_VALUE = 1;
	
	RotateTimeline::RotateTimeline (int frameCount) :
	BoneBaseTimeline(frameCount, 2)
	{	}

	void RotateTimeline::Apply (Skeleton* skeleton, float time, float alpha) {
		Bone *bone;
		int frameIndex;
		float lastFrameValue, frameTime, percent, amount;
		
		if (time < GetFrameAtIndex(0)) return; /* Time is before first frame. */
		
		bone = skeleton->GetBoneAtIndex(GetBoneIndex());
		
		if (time >= GetFrameAtIndex(GetFramesLength() - 2)) { /* Time is after last frame. */
			float amount = bone->GetData()->GetRotation() + GetFrameAtIndex(GetFramesLength() - 1) - bone->GetRotation();
			while (amount > 180)
				amount -= 360;
			while (amount < -180)
				amount += 360;
			bone->SetRotation( bone->GetRotation() + amount * alpha);
			return;
		}
		
		/* Interpolate between the last frame and the current frame. */
		frameIndex = binarySearch(GetFrames(), GetFramesLength(), time, 2);
		lastFrameValue = GetFrameAtIndex(frameIndex - 1);
		frameTime = GetFrameAtIndex(frameIndex);
		percent = 1 - (time - frameTime) / (GetFrameAtIndex(frameIndex + ROTATE_LAST_FRAME_TIME) - frameTime);
		percent = GetCurvePercent( frameIndex / 2 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));
		
		amount = GetFrameAtIndex(frameIndex + ROTATE_FRAME_VALUE) - lastFrameValue;
		while (amount > 180)
			amount -= 360;
		while (amount < -180)
			amount += 360;
		amount = bone->GetData()->GetRotation() + (lastFrameValue + amount * percent) - bone->GetRotation();
		while (amount > 180)
			amount -= 360;
		while (amount < -180)
			amount += 360;
		bone->SetRotation(bone->GetRotation() + amount * alpha);
	}
	
	
	void RotateTimeline::SetFrame ( int frameIndex, float time, float angle) {
		frameIndex *= 2;
		SetFrameAtIndex(time, frameIndex);
		SetFrameAtIndex(angle, frameIndex + 1);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: RotateTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static const int TRANSLATE_LAST_FRAME_TIME = -3;
	static const int TRANSLATE_FRAME_X = 1;
	static const int TRANSLATE_FRAME_Y = 2;

	TranslateTimeline::TranslateTimeline (int frameCount) :
	BoneBaseTimeline(frameCount, 3)
	{	}

	void TranslateTimeline::Apply ( Skeleton* skeleton, float time, float alpha) {
		Bone *bone;
		int frameIndex;
		float lastFrameX, lastFrameY, frameTime, percent;
		
		if (time < GetFrameAtIndex(0)) return; /* Time is before first frame. */
		
		bone = skeleton->GetBoneAtIndex(GetBoneIndex());
		
		if (time >= GetFrameAtIndex(GetFramesLength() - 3)) { /* Time is after last frame. */
			GLKVector2 bone_add;
			bone_add.x = (bone->GetData()->GetXY().x + GetFrameAtIndex(GetFramesLength() - 2) - bone->GetXY().x) * alpha;
			bone_add.y = (bone->GetData()->GetXY().y + GetFrameAtIndex(GetFramesLength() - 1) - bone->GetXY().y) * alpha;
			bone->SetXY(GLKVector2Add(bone->GetXY(), bone_add));
			return;
		}
		
		/* Interpolate between the last frame and the current frame. */
		frameIndex = binarySearch(GetFrames(), GetFramesLength(), time, 3);
		lastFrameX = GetFrameAtIndex(frameIndex - 2);
		lastFrameY = GetFrameAtIndex(frameIndex - 1);
		frameTime = GetFrameAtIndex(frameIndex);
		percent = 1 - (time - frameTime) / (GetFrameAtIndex(frameIndex + TRANSLATE_LAST_FRAME_TIME) - frameTime);
		percent = GetCurvePercent(frameIndex / 3 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));
		
		GLKVector2 bone_xy = bone->GetXY();
		bone_xy.x += (bone->GetData()->GetXY().x + lastFrameX + (GetFrameAtIndex(frameIndex + TRANSLATE_FRAME_X) - lastFrameX) * percent - bone->GetXY().x) * alpha;
		bone_xy.y += (bone->GetData()->GetXY().y + lastFrameY + (GetFrameAtIndex(frameIndex + TRANSLATE_FRAME_Y) - lastFrameY) * percent - bone->GetXY().y) * alpha;
		bone->SetXY(bone_xy);
	}
	
	
	void TranslateTimeline::SetFrame ( int frameIndex, float time, float x, float y) {
		frameIndex *= 3;
		SetFrameAtIndex(time, frameIndex);
		SetFrameAtIndex(x, frameIndex + 1);
		SetFrameAtIndex(y, frameIndex + 2);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ScaleTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	ScaleTimeline::ScaleTimeline (int frameCount) :
	BoneBaseTimeline(frameCount, 3)
	{	}

	void ScaleTimeline::Apply (Skeleton* skeleton, float time, float alpha) {
		Bone *bone;
		int frameIndex;
		float lastFrameX, lastFrameY, frameTime, percent;
			
		if (time < GetFrameAtIndex(0)) return; /* Time is before first frame. */
		
		bone = skeleton->GetBoneAtIndex(GetBoneIndex());
		if (time >= GetFrameAtIndex(GetFramesLength() - 3)) { /* Time is after last frame. */
			GLKVector2 bone_scale = bone->GetScale();
			bone_scale.x += (bone->GetData()->GetScale().x - 1 + GetFrameAtIndex(GetFramesLength() - 2) - bone->GetScale().x) * alpha;
			bone_scale.y += (bone->GetData()->GetScale().y - 1 + GetFrameAtIndex(GetFramesLength() - 1) - bone->GetScale().y) * alpha;
			bone->SetScale(bone_scale);
			return;
		}
		
		/* Interpolate between the last frame and the current frame. */
		frameIndex = binarySearch(GetFrames(), GetFramesLength(), time, 3);
		lastFrameX = GetFrameAtIndex(frameIndex - 2);
		lastFrameY = GetFrameAtIndex(frameIndex - 1);
		frameTime = GetFrameAtIndex(frameIndex);
		percent = 1 - (time - frameTime) / (GetFrameAtIndex(frameIndex + TRANSLATE_LAST_FRAME_TIME) - frameTime);
		percent = GetCurvePercent( frameIndex / 3 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));
		
		GLKVector2 bone_scale = bone->GetScale();
		bone_scale.x += (bone->GetData()->GetScale().x - 1 + lastFrameX + (GetFrameAtIndex(frameIndex + TRANSLATE_FRAME_X) - lastFrameX) * percent - bone->GetScale().x) * alpha;
		bone_scale.y += (bone->GetData()->GetScale().y - 1 + lastFrameY + (GetFrameAtIndex(frameIndex + TRANSLATE_FRAME_Y) - lastFrameY) * percent - bone->GetScale().y) * alpha;
	}
	
	
	void ScaleTimeline::SetFrame ( int frameIndex, float time, float x, float y) {
		frameIndex *= 3;
		SetFrameAtIndex(time, frameIndex);
		SetFrameAtIndex(x, frameIndex + 1);
		SetFrameAtIndex(y, frameIndex + 2);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ColorTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static const int COLOR_LAST_FRAME_TIME = -5;
	static const int COLOR_FRAME_R = 1;
	static const int COLOR_FRAME_G = 2;
	static const int COLOR_FRAME_B = 3;
	static const int COLOR_FRAME_A = 4;
	
	ColorTimeline::ColorTimeline (int frameCount) :
	SlotBaseTimeline(frameCount, 5)
	{	}

	void ColorTimeline::Apply ( Skeleton* skeleton, float time, float alpha) {
		Slot *slot;
		int frameIndex;
		float lastFrameR, lastFrameG, lastFrameB, lastFrameA, percent, frameTime;
		float r, g, b, a;

		if (time < GetFrameAtIndex(0)) return; /* Time is before first frame. */
		
		slot = skeleton->GetSlotAtIndex(GetSlotIndex());
		
		if (time >= GetFrameAtIndex(GetFramesLength() - 5)) { /* Time is after last frame. */
			int i = GetFramesLength() - 1;
			slot->SetColor(GLKVector4Make(GetFrameAtIndex(i - 3), GetFrameAtIndex(i - 2), GetFrameAtIndex(i - 1), GetFrameAtIndex(i)));
			return;
		}
		
		/* Interpolate between the last frame and the current frame. */
		frameIndex = binarySearch(GetFrames(), GetFramesLength(), time, 5);
		lastFrameR = GetFrameAtIndex(frameIndex - 4);
		lastFrameG = GetFrameAtIndex(frameIndex - 3);
		lastFrameB = GetFrameAtIndex(frameIndex - 2);
		lastFrameA = GetFrameAtIndex(frameIndex - 1);
		frameTime = GetFrameAtIndex(frameIndex);
		percent = 1 - (time - frameTime) / (GetFrameAtIndex(frameIndex + COLOR_LAST_FRAME_TIME) - frameTime);
		
		percent = GetCurvePercent( frameIndex / 5 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));
		
		r = lastFrameR + (GetFrameAtIndex(frameIndex + COLOR_FRAME_R) - lastFrameR) * percent;
		g = lastFrameG + (GetFrameAtIndex(frameIndex + COLOR_FRAME_G) - lastFrameG) * percent;
		b = lastFrameB + (GetFrameAtIndex(frameIndex + COLOR_FRAME_B) - lastFrameB) * percent;
		a = lastFrameA + (GetFrameAtIndex(frameIndex + COLOR_FRAME_A) - lastFrameA) * percent;
		if (alpha < 1) {
			GLKVector4 color = slot->GetColor();
			color.r += (r - color.r) * alpha;
			color.g += (g - color.g) * alpha;
			color.b += (b - color.b) * alpha;
			color.a += (a - color.a) * alpha;
			slot->SetColor(color);
		} else {
			slot->SetColor(GLKVector4Make(r,g,b,a));
		}
	}
	
	
	void ColorTimeline::SetFrame ( int frameIndex, float time, float r, float g, float b, float a) {
		frameIndex *= 5;
		SetFrameAtIndex(time,frameIndex);
		SetFrameAtIndex(r, frameIndex + 1);
		SetFrameAtIndex(g, frameIndex + 2);
		SetFrameAtIndex(b, frameIndex + 3);
		SetFrameAtIndex(a, frameIndex + 4);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AttachmentTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	AttachmentTimeline::AttachmentTimeline (int frameCount)  :
	SlotBaseTimeline(frameCount, 1),
	attachment_names_(new std::string[frameCount])
	{	}

	AttachmentTimeline::~AttachmentTimeline () {
		delete [] attachment_names_;
	}

	void AttachmentTimeline::Apply ( Skeleton* skeleton, float time, float alpha) {
		int frameIndex;
		std::string attachmentName;
		
		if (time < GetFrameAtIndex(0)) return; /* Time is before first frame. */
		
		if (time >= GetFrameAtIndex(GetFramesLength() - 1)) /* Time is after last frame. */
			frameIndex = GetFramesLength() - 1;
		else
			frameIndex = binarySearch(GetFrames(), GetFramesLength(), time, 1) - 1;
		
		attachmentName = attachment_names_[frameIndex];
		skeleton->GetSlotAtIndex(GetSlotIndex())->SetAttachment( !attachmentName.empty() ? skeleton->GetAttachmentForSlotIndex(GetSlotIndex(), attachmentName) : 0);
	}
	

	void AttachmentTimeline::SetFrame ( int frameIndex, float time, std::string attachmentName) {
		SetFrameAtIndex(time,frameIndex);
		attachment_names_[frameIndex] = attachmentName;
	}

}
