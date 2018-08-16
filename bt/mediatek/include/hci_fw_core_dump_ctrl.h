#pragma once
#include "hci/include/vendor.h"

//M: host trigger FW assert 
#ifdef MTK_BT_COMMON
bool is_chip_doing_reset();

bool handleFirmwareReset(int error_code);

bool triggerFirmwareAssert();

void setFimrwareCoreDumpVendor(const vendor_t * vendor);
#endif
//M: END
