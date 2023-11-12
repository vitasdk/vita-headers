#ifndef _VITASDKKERN_H_
#define _VITASDKKERN_H_

#include <psp2kern/types.h>
#include <psp2kern/appmgr.h>
#include <psp2kern/bt.h>
#include <psp2kern/ctrl.h>
#include <psp2kern/display.h>
#include <psp2kern/fios2.h>
#include <psp2kern/gpu_es4.h>
#include <psp2kern/idstorage.h>
#include <psp2kern/jpegenc.h>
#include <psp2kern/netps.h>
#include <psp2kern/npdrm.h>
#include <psp2kern/pfsmgr.h>
#include <psp2kern/post_ss_mgr.h>
#include <psp2kern/power.h>
#include <psp2kern/registrymgr.h>
#include <psp2kern/touch.h>
#include <psp2kern/udcd.h>
#include <psp2kern/usbd.h>
#include <psp2kern/usbserial.h>
#include <psp2kern/usbserv.h>

#include <psp2kern/internal/exfatfs.h>
#include <psp2kern/internal/sdstor.h>

#include <psp2kern/io/devctl.h>
#include <psp2kern/io/dirent.h>
#include <psp2kern/io/fcntl.h>
#include <psp2kern/io/stat.h>

#include <psp2kern/kernel/acmgr.h>
#include <psp2kern/kernel/aimgr.h>
#include <psp2kern/kernel/authmgr.h>
#include <psp2kern/kernel/cpu.h>
#include <psp2kern/kernel/debug.h>
#include <psp2kern/kernel/debugled.h>
#include <psp2kern/kernel/dipsw.h>
#include <psp2kern/kernel/dmac.h>
#include <psp2kern/kernel/excpmgr.h>
#include <psp2kern/kernel/intrmgr.h>
#include <psp2kern/kernel/iofilemgr.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/msif.h>
#include <psp2kern/kernel/pm_mgr.h>
#include <psp2kern/kernel/proc_event.h>
#include <psp2kern/kernel/processmgr.h>
#include <psp2kern/kernel/rtc.h>
#include <psp2kern/kernel/sm_comm.h>
#include <psp2kern/kernel/ssmgr.h>
#include <psp2kern/kernel/suspend.h>
#include <psp2kern/kernel/sysclib.h>
#include <psp2kern/kernel/syscon.h>
#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/kernel/sysroot.h>
#include <psp2kern/kernel/systimer.h>
#include <psp2kern/kernel/threadmgr.h>
#include <psp2kern/kernel/uart.h>
#include <psp2kern/kernel/utils.h>
#include <psp2kern/kernel/kbl/kbl.h>
#include <psp2kern/kernel/sysmem/address_space.h>
#include <psp2kern/kernel/sysmem/data_transfers.h>
#include <psp2kern/kernel/sysmem/heap.h>
#include <psp2kern/kernel/sysmem/uid_class.h>
#include <psp2kern/kernel/sysmem/uid_guid.h>
#include <psp2kern/kernel/sysmem/uid_puid.h>

#include <psp2kern/lowio/dsi.h>
#include <psp2kern/lowio/gpio.h>
#include <psp2kern/lowio/i2c.h>
#include <psp2kern/lowio/iftu.h>
#include <psp2kern/lowio/pervasive.h>

#endif /* _VITASDKKERN_H_ */
