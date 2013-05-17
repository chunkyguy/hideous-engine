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

#ifndef SPINE_ANIMATION_H_
#define SPINE_ANIMATION_H_

#include <string>

namespace spine {
	
	class Skeleton;
	
	/**/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Timeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Timeline {
		virtual ~Timeline(){};
		virtual void Apply(Skeleton* skeleton, float time, float alpha) = 0;
	};
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Animation
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Animation {
	public:
		~Animation();
		Animation(const std::string name, int timelineCount);
		void Apply ( Skeleton* skeleton, float time, bool loop);
		void Mix ( Skeleton* skeleton, float time, bool loop, float alpha) const;
		float GetDuration();
		void SetDuration(float duration);
		int GetTimelineCount();
		void SetTimelineCount(int count);
		std::string GetName();
		void SetTimelineAtIndex(Timeline *timeline, int index);
		
	private:
		float duration_;
		std::string name_;
		int timeline_count_;
		Timeline** timelines_;
	};
	
	
	/**/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: CurveTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class CurveTimeline : public Timeline{
	public:
		virtual ~CurveTimeline();
		explicit CurveTimeline(int frameCount);
		void SetLinear ( int frameIndex);
		void SetStepped ( int frameIndex);
		/* Sets the control handle positions for an interpolation bezier curve used to transition from this keyframe to the next.
		 * cx1 and cx2 are from 0 to 1, representing the percent of time between the two keyframes. cy1 and cy2 are the percent of
		 * the difference between the keyframe's values. */
		void SetCurve (int frameIndex, float cx1, float cy1, float cx2, float cy2);
		float GetCurvePercent ( int frameIndex, float percent) const;
		
	private:
		float* curves_; /* dfx, dfy, ddfx, ddfy, dddfx, dddfy, ... */
	};
	
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: BaseTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**/
	class BaseTimeline : public CurveTimeline{
	public:
		virtual ~BaseTimeline();
		BaseTimeline (int frameCount, int frameSize);

		float GetFrameAtIndex(int index);
		void SetFrameAtIndex(float v, int index);
		int GetFramesLength();
		float *GetFrames();
		
	private:
		float *frames_; /* time, angle, ... for rotate. time, x, y, ... for translate and scale. */
		int frames_length_;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: BoneBaseTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class BoneBaseTimeline : public BaseTimeline{
	public:
		virtual ~BoneBaseTimeline(){}
		BoneBaseTimeline (int frameCount, int frameSize);
		virtual	void SetFrame( int , float , float , float );
		int GetBoneIndex();
		void SetBoneIndex(int index);

	private:
		int bone_index_;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: SlotBaseTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class SlotBaseTimeline : public BaseTimeline{
	public:
		virtual ~SlotBaseTimeline(){}
		SlotBaseTimeline (int frameCount, int frameSize);
		int GetSlotIndex();
		void SetSlotIndex(int index);

	private:
		int slot_index_;
	};

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: RotateTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class RotateTimeline : public BoneBaseTimeline{
	public:
		RotateTimeline(int frameCount);
		void SetFrame ( int frameIndex, float time, float angle);
		void Apply(Skeleton* skeleton, float time, float alpha);
		
		 /*frames: time, angle, ... for rotate. time, x, y, ... for translate and scale. */
	} ;
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: RotateTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class TranslateTimeline : public BoneBaseTimeline{
	public:
		explicit TranslateTimeline(int frameCount);
		void SetFrame ( int frameIndex, float time, float x, float y);
		void Apply(Skeleton* skeleton, float time, float alpha);
	};
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ScaleTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ScaleTimeline : public BoneBaseTimeline{
	public:
		explicit ScaleTimeline(int frameCount);
		void SetFrame( int frameIndex, float time, float x, float y);
		void Apply(Skeleton* skeleton, float time, float alpha);
	};
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ColorTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ColorTimeline : public SlotBaseTimeline{
	public:
		explicit ColorTimeline(int frameCount);
		void SetFrame ( int frameIndex, float time, float r, float g, float b, float a);
		void Apply(Skeleton* skeleton, float time, float alpha);

		/*frames: time, r, g, b, a, ... */
	};
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: AttachmentTimeline
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class AttachmentTimeline : public SlotBaseTimeline {
	public:
		explicit AttachmentTimeline(int frameCount);
		~AttachmentTimeline();
		/* @param attachmentName May be 0. */
		void SetFrame ( int frameIndex, float time, std::string attachmentName);
		void Apply(Skeleton* skeleton, float time, float alpha);
		
		/*frames: time, ... */
	private:
		std::string *attachment_names_;
	} ;
	
	
}

#endif /* SPINE_ANIMATION_H_ */
