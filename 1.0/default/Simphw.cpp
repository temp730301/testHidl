// FIXME: your file license if you have one

#include "Simphw.h"
#include <hidl/LegacySupport.h>
// add
#include <android/hidl/allocator/1.0/IAllocator.h>
//#include <hidlmemory/HidlMemoryDealer.h>
#include <hidlcache/MemoryDealer.h>
//#include <hidlmemory/mapping.h>
#include <hidlcache/mapping.h>
#include <android/hidl/memory/block/1.0/types.h>

#include <android/hidl/memory/1.0/IMemory.h>

namespace android {
namespace hardware {
namespace simple {
namespace V1_0 {
namespace implementation {

using ::android::hidl::memory::block::V1_0::MemoryBlock;

// add
using ::android::hidl::allocator::V1_0::IAllocator;
using ::android::hardware::hidl_memory;
using ::android::hardware::HidlMemoryDealer;
using ::android::hidl::memory::block::V1_0::MemoryBlock;
using ::android::hidl::memory::V1_0::IMemory;
using ::android::hardware::HidlMemoryDealer;

Simphw::Simphw()
{
#if 0
    sp<IAllocator> allocator = IAllocator::getService("ashmem");
    allocator->allocate(2048, [&](bool success, const hidl_memory& mem)
    {
        if (!success) {
			/* error */
			ALOGE("[MM] HAL: allocate error");
		} else {
            // you can now use the hidl_memory object 'mem' or pass it
            m_dealer = HidlMemoryDealer::getInstance(mem);
            if (m_dealer != nullptr) {
				m_mem = mem;
				ALOGE("[MM] HAL: allocate OK");
			} else {
				ALOGE("[MM] HAL: HidlMemoryDealer NG");
			}
		}
    });
#endif    
    
}

Simphw::~Simphw()
{


}

// Methods from ::android::hardware::simple::V1_0::ISimphw follow.
Return<int32_t> Simphw::simpfn(int32_t valueIn) {
    // TODO implement
    return (valueIn+100);
}

Return<void> Simphw::getSome(getSome_cb _hidl_cb) {
#if 0
    // TODO implement
	MemoryBlock retBlock;


#if 0
	ALOGE("[MM] HAL: getSome Start");
	MemoryBlock retBlock;
	if (m_dealer != nullptr) {
		MemoryBlock block = m_dealer->allocate(1024);
		ALOGE("[MM] HAL: m_dealer->allocate() called.");

		if(HidlMemoryDealer::isOk(block)){
			ALOGE("[MM] HAL: block OK");

		    sp<IMemory> memory = mapMemory(block);
	//        sp<IMemory> memory = mapMemory(m_mem);
		    uint8_t* data = static_cast<uint8_t*>(static_cast<void*>(memory->getPointer()));
		    data[0] = 0xAA;
		    data[1024-1] = 0xBB;
			retBlock = block;
		} else {
	 		ALOGE("[MM] HAL: block NG");
		}
	} else {
		ALOGE("[MM] HAL: m_dealer null");	
	}
	ALOGE("[MM] HAL: getSome Callback called.");
#else
	sp<HidlMemory> m1;
	sp<HidlMemory> m2;
    sp<IAllocator> allocator = IAllocator::getService("ashmem");
    allocator->allocate(4096, [&m2](bool success, const hidl_memory& mem)
    {
		if (!success) {
			/* error */
			ALOGE("[MM] HAL: allocate error");
		} else {
            // you can now use the hidl_memory object 'mem' or pass it
//            m_dealer = HidlMemoryDealer::getInstance(mem);

			m2 = HidlMemory::getInstance(mem);

			sp<HidlMemoryDealer> memory_dealer =  HidlMemoryDealer::getInstance(*m2);
            if (memory_dealer != nullptr) {
//				m_mem = mem;
				ALOGE("[MM] HAL: allocate OK");
				
				MemoryBlock block = memory_dealer->allocate(1024);
				ALOGE("[MM] HAL: m_dealer->allocate() called.");

				if(HidlMemoryDealer::isOk(block)){
					ALOGE("[MM] HAL: block OK");

					sp<IMemory> memory = mapMemory(block);
					uint8_t* data = static_cast<uint8_t*>(static_cast<void*>(memory->getPointer()));
					data[0] = 0xAA;
					data[1024-1] = 0xBB;
					retBlock = block;
				} else {
			 		ALOGE("[MM] HAL: block NG");
				}
			} else {
				ALOGE("[MM] HAL: HidlMemoryDealer NG");
			}
		}
    });
#endif

    _hidl_cb(retBlock);

    return Void();
#else

    sp<IAllocator> ashmemAllocator;

    ashmemAllocator = IAllocator::getService("ashmem");

    sp<HidlMemory> m2;
    // test MemoryDealer

    ashmemAllocator->allocate(4096, [&m2](bool success, const hidl_memory& mem)
    {
	    if (success) {
     	   m2 = HidlMemory::getInstance(mem);
    	}
    });

    sp<HidlMemoryDealer> dealer;
	MemoryBlock block;
	
    dealer = HidlMemoryDealer::getInstance(*m2);
    if (dealer != nullptr) {
		ALOGE("[MM] HAL: dealer OK");


		block = dealer->allocate(1024);
		ALOGE("[MM] HAL: m_dealer->allocate() called.");

		if(HidlMemoryDealer::isOk(block)){
			ALOGE("[MM] HAL: block OK");
			sp<IMemory> memory = mapMemory(block);
			uint8_t* data = static_cast<uint8_t*>(static_cast<void*>(memory->getPointer()));
			data[0] = 0xAA;
			data[1024-1] = 0xBB;
		} else {
	 		ALOGE("[MM] HAL: block NG");
		}
    } else {
    	ALOGE("[MM] HAL: dealer NG");
	}
    
    _hidl_cb(block);

    return Void();
#endif

}

Return<void> Simphw::giveBack(const ::android::hidl::memory::block::V1_0::MemoryBlock& block) {
    // TODO implement
    m_dealer->deallocate(block.offset);
 
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.
ISimphw *Simphw::getInstance(void){
  return new Simphw();
}

//ISimphw* HIDL_FETCH_ISimphw(const char* /* name */) {
    //return new Simphw();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace simple
}  // namespace hardware
}  // namespace android
