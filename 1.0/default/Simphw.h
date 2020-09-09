// FIXME: your file license if you have one

#pragma once

#include <android/hardware/simple/1.0/ISimphw.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <hidlcache/MemoryDealer.h>

namespace android {
namespace hardware {
namespace simple {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;
using ::android::hardware::HidlMemoryDealer;

struct Simphw : public ISimphw {
    Simphw();
    ~Simphw();
    // Methods from ::android::hardware::simple::V1_0::ISimphw follow.
    Return<int32_t> simpfn(int32_t valueIn) override;
    Return<void> getSome(getSome_cb _hidl_cb) override;
    Return<void> giveBack(const ::android::hidl::memory::block::V1_0::MemoryBlock& block) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    static ISimphw* getInstance(void);
    hidl_memory m_mem;
    sp<HidlMemoryDealer> m_dealer;
};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" ISimphw* HIDL_FETCH_ISimphw(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace simple
}  // namespace hardware
}  // namespace android
