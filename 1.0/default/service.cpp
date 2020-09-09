#define LOG_TAG "android.hardware.simple@1.0-service"

#include <android/hardware/simple/1.0/ISimphw.h>

#include <hidl/LegacySupport.h>

#include "Simphw.h"

using android::hardware::simple::V1_0::ISimphw;
using android::hardware::simple::V1_0::implementation::Simphw;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

int main() {
      int res;
      android::sp<ISimphw> ser = Simphw::getInstance();
      ALOGE("[MM] service: simp main");
      configureRpcThreadpool(1, true /*callerWillJoin*/);

      if (ser != nullptr) {
          res = ser->registerAsService();
          if(res != 0)
            ALOGE("[MM] service: Can't register instance of SimpleHardware, nullptr");
      } else {
          ALOGE("[MM] service: Can't create instance of SimpleHardware, nullptr");
       }

      joinRpcThreadpool();

      return 0; // should never get here
}

