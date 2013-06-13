//
//  Asset.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Asset_h
#define HideousGameEngine_Asset_h
#include <he/Utils/DebugHelper.h>	// For assert()

namespace he {

	/** RAII for any asset that lives in memory
		Best use is for creating factories those instanciate objects.
	 */
	template <typename T>
	class Asset{
	public:
		/** Load an asset
		 @param	asset The asset to be loaded into the memory
		 @param	self_destruct If true, deletes the asset as soon goes out of scope. By default false
		 @note	Set self_destruct false, if the asset is not owned by the class constructing the asset
				Another case could be when the asset is to be used shared among many contexts.
		 */
		Asset(T *asset = nullptr, bool self_destruct = false) :
		asset_(asset),
		self_destruct_(self_destruct)
		{	}
		
		/** Destroys the contained asset, if self_destruct was enabled. */
		~Asset(){
			if(self_destruct_){
				delete asset_;
			}
		}
		
		/** Get a reference to the asset */
		T* Get() const{
			return asset_;
		}
		
		/** Load asset
			Load only if not loaded already. Otherwise, skip.
		 */
		void Load(T* asset, bool self_destruct){
			if(!asset_){
				asset_ = asset;
			}
			self_destruct_ = self_destruct;
			assert(asset_);
		}
		
		/* Reload asset
			If already loaded, delete the original asset and create new
		 */
		void Reload(T* asset, bool self_destruct){
			if(asset_){
				delete asset_;
			}
			asset_ = asset;
			self_destruct_ = self_destruct;
			assert(asset_);
		}
		
	private:
		T *asset_;				/**< the asset pointer */
		bool self_destruct_;		/**< can destroy after use. */
	};
	
	
} /*namespace he*/

#endif
