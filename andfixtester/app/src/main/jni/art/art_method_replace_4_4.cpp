/*
 *
 * Copyright (c) 2015, alipay.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * 	art_method_replace_4_4.cpp
 *
 * @author : sanping.li@alipay.com
 *
 */
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include <stdbool.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "art.h"
#include "art_4_4.h"
#include "common.h"

void replace_4_4(JNIEnv* env, jobject src, jobject dest) {
	art::mirror::ArtMethod* smeth =
			(art::mirror::ArtMethod*) env->FromReflectedMethod(src);

	art::mirror::ArtMethod* dmeth =
			(art::mirror::ArtMethod*) env->FromReflectedMethod(dest);

    void *temp = dmeth->declaring_class_->class_loader_;
	dmeth->declaring_class_->class_loader_ =
			smeth->declaring_class_->class_loader_; //for plugin classloader
    smeth->declaring_class_->class_loader_ = temp;

	//for reflection invoke
    reinterpret_cast<art::mirror::Class*>(dmeth->declaring_class_)->super_class_ = 0;
    reinterpret_cast<art::mirror::Class*>(smeth->declaring_class_)->super_class_ = 0;

    art::mirror::Class *ctemp = smeth->declaring_class_;
	smeth->declaring_class_ = dmeth->declaring_class_;
    dmeth->declaring_class_ = ctemp;

    temp = smeth->dex_cache_initialized_static_storage_;
    smeth->dex_cache_initialized_static_storage_ = dmeth->dex_cache_initialized_static_storage_;
    dmeth->dex_cache_initialized_static_storage_ = temp;

    temp = smeth->dex_cache_resolved_types_;
    smeth->dex_cache_resolved_types_ = dmeth->dex_cache_resolved_types_;
    dmeth->dex_cache_resolved_types_ = temp;

    temp = smeth->dex_cache_resolved_methods_;
    smeth->dex_cache_resolved_methods_ = dmeth->dex_cache_resolved_methods_;
    dmeth->dex_cache_resolved_methods_ = temp;

    temp = smeth->dex_cache_strings_;
    smeth->dex_cache_strings_ = dmeth->dex_cache_strings_;
    dmeth->dex_cache_strings_ = temp;

    uint32_t *uitemp = (uint32_t *) smeth->mapping_table_;
    smeth->mapping_table_ = dmeth->mapping_table_;
    dmeth->mapping_table_ = uitemp;

    uint8_t *u1temp = (uint8_t *) smeth->gc_map_;
    smeth->gc_map_ = dmeth->gc_map_;
    dmeth->gc_map_ = u1temp;

    temp = (void *) smeth->native_method_;
    smeth->native_method_ = dmeth->native_method_;
    dmeth->native_method_ = temp;

    temp = (void *) smeth->entry_point_from_compiled_code_;
    smeth->entry_point_from_compiled_code_ = dmeth->entry_point_from_compiled_code_;
    dmeth->entry_point_from_compiled_code_ = temp;

    temp = smeth->entry_point_from_interpreter_;
    smeth->entry_point_from_interpreter_ = dmeth->entry_point_from_interpreter_;
    dmeth->entry_point_from_interpreter_ = temp;

    uint16_t *u2temp = (uint16_t *) smeth->vmap_table_;
    smeth->vmap_table_ = dmeth->vmap_table_;
    dmeth->vmap_table_ = u2temp;


    smeth->method_index_ ^= dmeth->method_index_;
    smeth->frame_size_in_bytes_ ^= dmeth->frame_size_in_bytes_;
    smeth->method_index_ ^= dmeth->method_index_;
    smeth->method_dex_index_ ^= dmeth->method_dex_index_;
    smeth->fp_spill_mask_ ^= dmeth->fp_spill_mask_;
    smeth->core_spill_mask_ ^= dmeth->core_spill_mask_;
    smeth->code_item_offset_ ^= dmeth->code_item_offset_;
    smeth->access_flags_ ^= dmeth->access_flags_  | 0x0001;
    dmeth->declaring_class_->clinit_thread_id_ ^=
            smeth->declaring_class_->clinit_thread_id_;
    dmeth->declaring_class_->status_ ^= smeth->declaring_class_->status_-1;


    dmeth->method_index_ ^= smeth->method_index_;
    dmeth->frame_size_in_bytes_ ^= smeth->frame_size_in_bytes_;
    dmeth->method_index_ ^= smeth->method_index_;
    dmeth->method_dex_index_ ^= smeth->method_dex_index_;
    dmeth->fp_spill_mask_ ^= smeth->fp_spill_mask_;
    dmeth->core_spill_mask_ ^= smeth->core_spill_mask_;
    dmeth->code_item_offset_ ^= smeth->code_item_offset_;
    dmeth->access_flags_ ^= smeth->access_flags_  | 0x0001;
    smeth->declaring_class_->clinit_thread_id_ ^=
            dmeth->declaring_class_->clinit_thread_id_;
    smeth->declaring_class_->status_ ^= dmeth->declaring_class_->status_-1;

    smeth->method_index_ ^= dmeth->method_index_;
    smeth->frame_size_in_bytes_ ^= dmeth->frame_size_in_bytes_;
    smeth->method_index_ ^= dmeth->method_index_;
    smeth->method_dex_index_ ^= dmeth->method_dex_index_;
    smeth->fp_spill_mask_ ^= dmeth->fp_spill_mask_;
    smeth->core_spill_mask_ ^= dmeth->core_spill_mask_;
    smeth->code_item_offset_ ^= dmeth->code_item_offset_;
    smeth->access_flags_ ^= dmeth->access_flags_  | 0x0001;
    dmeth->declaring_class_->clinit_thread_id_ ^=
            smeth->declaring_class_->clinit_thread_id_;
    dmeth->declaring_class_->status_ ^= smeth->declaring_class_->status_-1;


	LOGD("replace_4_4: %d , %d", smeth->entry_point_from_compiled_code_,
			dmeth->entry_point_from_compiled_code_);

}

void setFieldFlag_4_4(JNIEnv* env, jobject field) {
	art::mirror::ArtField* artField =
			(art::mirror::ArtField*) env->FromReflectedField(field);
	artField->access_flags_ = artField->access_flags_ & (~0x0002) | 0x0001;
	LOGD("setFieldFlag_4_4: %d ", artField->access_flags_);
}

