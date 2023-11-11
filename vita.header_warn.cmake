
# Here are the backwards compatibility breaking changes that occur in vita-headers and their dates.

if(NOT SHOWED_DEPRECATION_WARNING)

string(TIMESTAMP __vitasdk_year  "%Y" UTC)
string(TIMESTAMP __vitasdk_month "%m" UTC)
string(TIMESTAMP __vitasdk_day   "%d" UTC)

math(EXPR __vitasdk_current_time "${__vitasdk_year} * 10000 + ${__vitasdk_month} * 100 + ${__vitasdk_day}")


math(EXPR __vitasdk_expires_kern_header_remove_no_depend_include "20230801 + 1 * 100")

if(${__vitasdk_current_time} LESS ${__vitasdk_expires_kern_header_remove_no_depend_include})
  message("#")
  message("# The unneeded non-dependent includes in kernel headers will be removed on 2023/08/01")
  message("#")
  message("")
endif()

math(EXPR __vitasdk_expires_kern_header_move "20231001 + 2 * 100")

if(${__vitasdk_current_time} LESS ${__vitasdk_expires_kern_header_move})
  message("#")
  message("# The location of the following kernel headers will be changed on 2023/10/01")
  message("#")
  message("")
  message("- psp2kern/sblacmgr.h        -> psp2kern/kernel/acmgr.h")
  message("- psp2kern/sblaimgr.h        -> psp2kern/kernel/aimgr.h")
  message("- psp2kern/sblauthmgr.h      -> psp2kern/kernel/authmgr.h")
  message("- psp2kern/syscon.h          -> psp2kern/kernel/syscon.h")
  message("- psp2kern/uart.h            -> psp2kern/kernel/uart.h")
  message("- psp2kern/net/net.h         -> psp2kern/netps.h")
  message("- psp2kern/avcodec/jpegenc.h -> psp2kern/jpegenc.h")
  message("")
endif()

math(EXPR __vitasdk_expires_kern_cpu_big_fix "20231015 + 2 * 100")

if(${__vitasdk_current_time} LESS ${__vitasdk_expires_kern_cpu_big_fix})
  message("#")
  message("# The many things in psp2kern/kernel/cpu.h will be fixed and not compatible with previous ones on 2023/10/15")
  message("#")
  message("")
endif()

math(EXPR __vitasdk_expires_removed_some_user_backwards_compat_20240801 "20240801 + 2 * 100")

if(${__vitasdk_current_time} LESS ${__vitasdk_expires_removed_some_user_backwards_compat_20240801})
  message("#")
  message("# The backwards compatibility of headers will be removed for the following users on 2024/08/01")
  message("# > power.h / paf.h")
  message("#")
  message("")
endif()

math(EXPR __vitasdk_expires_wrong_libs_module_name "20240101 + 2 * 100")

if(${__vitasdk_current_time} LESS ${__vitasdk_expires_wrong_libs_module_name})
endif()

if(Off)
  # Planned

  # Done with nothing
  # __vitasdk_expires_wrong_libs_module_name on 2023/07/19
  message("#")
  message("# The following library link will be obsolete on 2024/01/01")
  message("#")
  message("")
  # message("- ${LIB_NAME} library with ${OLD_MODULE_NAME}_stub")
  # message("Alternative: link ${NEW_MODULE_NAME}_stub instead.")
  # message("")
  message("- SceHttp library with SceHttp_stub")
  message("Alternative: link SceLibHttp_stub instead.")
  message("")
  message("- SceLibLocation library with SceLocation_stub")
  message("Alternative: link SceLibLocation_stub instead.")
  message("")
  message("- SceLibLocationExtension library with SceLocationExtension_stub")
  message("Alternative: link SceLibLocationExtension_stub instead.")
  message("")
  message("- ScePgf library with ScePgf_stub")
  message("Alternative: link SceLibPgf_stub instead.")
  message("")
  message("- ScePvf library with ScePvf_stub")
  message("Alternative: link SceLibPvf_stub instead.")
  message("")
  message("- SceLibRudp library with SceRudp_stub")
  message("Alternative: link SceLibRudp_stub instead.")
  message("")
  message("- SceLiveAreaUtil library with SceLiveArea_stub")
  message("Alternative: link SceLiveAreaUtil_stub instead.")
  message("")
  message("- SceDTrace library with SceDTrace_stub")
  message("Alternative: link SceDeci4pDtracep_stub instead.")
  message("")
  message("- SceAudioIn library with SceAudioIn_stub")
  message("Alternative: link SceAudioin_stub instead.")
  message("")

  message("#")
  message("# The following library link will be obsolete on ----/--/--")
  message("#")
  message("")
  message("- SceFios2User   library with SceFios2_stub")
  message("- SceRtcUser     library with SceRtc_stub")
  message("- SceDisplayUser library with SceDisplay_stub")
  message("- SceMotion      library with SceMotion_stub")
  message("- SceAppMgrUser  library with SceAppMgr_stub")
  message("Alternative: link SceDriverUser_stub instead.")
  message("")
  message("- SceAudiodecUser library with SceAudiodec_stub")
  message("- SceAudioencUser library with SceAudioenc_stub")
  message("- SceJpegUser     library with SceJpeg_stub")
  message("- SceJpegEncUser  library with SceJpegEnc_stub")
  message("- SceVideodecUser library with SceVideodec_stub")
  message("Alternative: link SceAvcodecUser_stub instead.")
endif()

set(SHOWED_DEPRECATION_WARNING On)

endif()