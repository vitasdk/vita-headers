var group__SceVoiceUser =
[
    [ "SceVoiceEventPortDataReady", "group__SceVoiceUser.html#structSceVoiceEventPortDataReady", [
      [ "port_count", "group__SceVoiceUser.html#ga5d279b13c9c30d4a0556fb408d2edbe1", null ],
      [ "port_ids", "group__SceVoiceUser.html#ga4d6b3ee4278f178954c730ff40fb57d4", null ]
    ] ],
    [ "SceVoiceEventAudioInputOwnershipChanged", "group__SceVoiceUser.html#structSceVoiceEventAudioInputOwnershipChanged", [
      [ "owned", "group__SceVoiceUser.html#gabc8c3fb4afc7e0e678b792048d7421ff", null ],
      [ "reserved", "group__SceVoiceUser.html#ga20d9896b1fd20df32c5349c94503d2f7", null ]
    ] ],
    [ "SceVoiceEvent", "group__SceVoiceUser.html#structSceVoiceEvent", [
      [ "event_type", "group__SceVoiceUser.html#ga78f80fd983b9b6d0307cf132f2012fc1", null ],
      [ "user_data", "group__SceVoiceUser.html#ga1440e5495522c0c37e0e319cc8664eeb", null ],
      [ "event_payload", "group__SceVoiceUser.html#ga82c0a6ecac018db0bf8eff16b50f0cc7", null ]
    ] ],
    [ "SceVoiceInitParam", "group__SceVoiceUser.html#structSceVoiceInitParam", [
      [ "application_type", "group__SceVoiceUser.html#gaf20a369a7e5deea750c575fede00fa59", null ],
      [ "event_callback", "group__SceVoiceUser.html#ga9fb7c9d9e0f3fd2c5aed0005023471f5", null ],
      [ "user_data", "group__SceVoiceUser.html#gaf42af2f83901cfe7aefb4a266063da21", null ],
      [ "reserved", "group__SceVoiceUser.html#gab1f0d7d42f731ad59d873de3c5a185db", null ]
    ] ],
    [ "SceVoiceStartParam", "group__SceVoiceUser.html#structSceVoiceStartParam", [
      [ "mem_block_id", "group__SceVoiceUser.html#gaf4c3a664322eeebf82924909d16ca838", null ],
      [ "reserved", "group__SceVoiceUser.html#gac3fb72b81d10e34cc9db346646f97d64", null ]
    ] ],
    [ "SceVoicePortParam", "group__SceVoiceUser.html#structSceVoicePortParam", [
      [ "port_type", "group__SceVoiceUser.html#ga9c3f63602faace0423de9520d13d509f", null ],
      [ "threshold", "group__SceVoiceUser.html#ga7f67521b26916a2ddc5728e695883806", null ],
      [ "mute_flag", "group__SceVoiceUser.html#ga9a08a4338184779314e0348dd3da02f0", null ],
      [ "volume", "group__SceVoiceUser.html#ga68c25d735c992e09e91a319658d2a7b7", null ],
      [ "data", "group__SceVoiceUser.html#gad43aa9f9ee8cfc920465c14a9a9be36c", null ],
      [ "pcm_data_type", "group__SceVoiceUser.html#ga906222aa508c1ff99603142203be793d", null ],
      [ "sampling_rate", "group__SceVoiceUser.html#ga91608c7c7de29adbc61b5ad43e9e05d8", null ]
    ] ],
    [ "SceVoiceResourceInfo", "group__SceVoiceUser.html#structSceVoiceResourceInfo", [
      [ "max_voice_input_ports", "group__SceVoiceUser.html#ga62163b9ed7eccd8595548a3ab173cc0e", null ],
      [ "max_voice_output_ports", "group__SceVoiceUser.html#ga5136de8fdc8c03a00a2ed47da0059841", null ],
      [ "max_device_input_ports", "group__SceVoiceUser.html#ga74787d00076115ad59331aeb821c3c9b", null ],
      [ "max_device_output_ports", "group__SceVoiceUser.html#gaca9506fb106a0531fdcf5ea07a4a4626", null ],
      [ "max_ports", "group__SceVoiceUser.html#gac99dfb8f640cf0b0f4406f89a416fddc", null ]
    ] ],
    [ "SceVoicePortInfo", "group__SceVoiceUser.html#structSceVoicePortInfo", [
      [ "port_type", "group__SceVoiceUser.html#ga289e7ef2ddd69b444e381aac343cc505", null ],
      [ "state", "group__SceVoiceUser.html#ga67ac166d74538642bc436971dc05ffef", null ],
      [ "reserved0", "group__SceVoiceUser.html#ga3b58e15d6d1518859d492b29ac3b423a", null ],
      [ "data_size", "group__SceVoiceUser.html#ga0c3f961bc86d97689ca2f436b59f7a91", null ],
      [ "frame_size", "group__SceVoiceUser.html#gaf246946fc3f0db2f7ecb09272b8fa656", null ],
      [ "reserved1", "group__SceVoiceUser.html#ga0d8d543eb96897644f3132d58e042e05", null ]
    ] ],
    [ "SceVoiceEvent.event_payload", "group__SceVoiceUser.html#unionSceVoiceEvent_8event__payload", [
      [ "port_data_ready", "group__SceVoiceUser.html#a72f9cbdf9efc1e86f54560f8b4fcab40", null ],
      [ "audio_input_ownership_changed", "group__SceVoiceUser.html#a95a0be249c2bffc678d4a6fc09b097d7", null ]
    ] ],
    [ "SceVoicePortParam.data", "group__SceVoiceUser.html#unionSceVoicePortParam_8data", [
      [ "buffer_size", "group__SceVoiceUser.html#a73631e47eecd054084ba9ca6b6c8cfeb", null ],
      [ "bit_rate", "group__SceVoiceUser.html#a172103461a17f37920fe6cef12e7a4bc", null ]
    ] ],
    [ "SCE_VOICE_VERSION", "group__SceVoiceUser.html#gaf58f928e32afe58249dcb993a5778b0d", null ],
    [ "SCE_VOICE_WORKING_MEMORY_SIZE", "group__SceVoiceUser.html#gacb3c4187d9aa5c1a7ec823b14fe5b9c6", null ],
    [ "SCE_VOICE_MAX_EVENT_PORTS", "group__SceVoiceUser.html#gab7af0f4488a3584685bdb266918be0eb", null ],
    [ "SceVoicePortId", "group__SceVoiceUser.html#gae496895e57f4b03a23360703b452d884", null ],
    [ "SceVoiceEventCallback", "group__SceVoiceUser.html#gacb3c29bb30d4c28d24904602cfd28c3c", null ],
    [ "SceVoiceErrorCode", "group__SceVoiceUser.html#ga2d12674892c52001f6fe51a5d726769f", [
      [ "SCE_VOICE_ERROR_NOT_INITIALIZED", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fa51b9a0b4084d38cea9eb67aebd2d02e0", null ],
      [ "SCE_VOICE_ERROR_ALREADY_INITIALIZED", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faea7f79edac61439c77060dff6aedba01", null ],
      [ "SCE_VOICE_ERROR_INTERNAL", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fab19d1bf3731bac417970c8a7d1e5f369", null ],
      [ "SCE_VOICE_ERROR_INVALID_PORT_ID", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fa28a2cad42c56ea72d98d583cf967c327", null ],
      [ "SCE_VOICE_ERROR_INVALID_ARGUMENT", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faf1024b91a7a968b546a0e869c29ac5d3", null ],
      [ "SCE_VOICE_ERROR_INVALID_MEMBLOCK", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fa03723c788eebb3efe640ea7a81b5f966", null ],
      [ "SCE_VOICE_ERROR_INVALID_PORT", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faf86ecf08c5f4e948de853864d9d71e0d", null ],
      [ "SCE_VOICE_ERROR_RESOURCE_LIMIT", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faeee5ff6c85980d1b41db253be91fb8eb", null ],
      [ "SCE_VOICE_ERROR_NOT_STARTED", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fab5af21e9255a12a9e059e5c6645801b9", null ]
    ] ],
    [ "SceVoiceApplicationType", "group__SceVoiceUser.html#ga513046a1d02c344291e80a003bd770bf", [
      [ "SCE_VOICE_APPLICATION_TYPE_UNK_0x20000000", "group__SceVoiceUser.html#gga513046a1d02c344291e80a003bd770bfacbbaec44286d5060028d9c1f749ec947", null ],
      [ "SCE_VOICE_APPLICATION_TYPE_UNK_0x80000000", "group__SceVoiceUser.html#gga513046a1d02c344291e80a003bd770bfa8eb4ff356ae327ac9634bb3fb4332153", null ]
    ] ],
    [ "SceVoicePortType", "group__SceVoiceUser.html#gad406ca767589c75f8da1d6a9e4b44c03", [
      [ "SCE_VOICE_PORT_TYPE_IN_DEVICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a9f865edb8f96bc1736218d638f144742", null ],
      [ "SCE_VOICE_PORT_TYPE_IN_PCMAUDIO", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a5ab93a34e42671895cab242cf97c40f2", null ],
      [ "SCE_VOICE_PORT_TYPE_IN_VOICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a579e8a0e095f08389c0f88ae1640a9c4", null ],
      [ "SCE_VOICE_PORT_TYPE_OUT_PCMAUDIO", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a62c9a5c2da10ba02de3a948729927d0b", null ],
      [ "SCE_VOICE_PORT_TYPE_OUT_VOICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a5a50cae3af5ea0f0a0bfa8b8504bf595", null ],
      [ "SCE_VOICE_PORT_TYPE_OUT_DEVICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a122f66fe14ee4a8240804777d3431a40", null ]
    ] ],
    [ "SceVoicePortState", "group__SceVoiceUser.html#gaab08afebb9b74e2a8412eef2fa78a98b", [
      [ "SCE_VOICE_PORT_STATE_INACTIVE", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98ba51b152b8f37235c6891fc4f1ae604c0a", null ],
      [ "SCE_VOICE_PORT_STATE_IDLE", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98ba5737643cf91d306556da9e4f2a6e38a8", null ],
      [ "SCE_VOICE_PORT_STATE_BUFFERING", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98bacf02803cda1820c921090b62fe70b178", null ],
      [ "SCE_VOICE_PORT_STATE_ACTIVE", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98ba1c8120ff2cf807bf3ead3db8d8a19402", null ]
    ] ],
    [ "SceVoiceBitRate", "group__SceVoiceUser.html#ga1882d031857e440181fcf51bb80f944b", [
      [ "SCE_VOICE_BIT_RATE_3850", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944ba7b01867c2b55c84ccad84aea34562339", null ],
      [ "SCE_VOICE_BIT_RATE_4650", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944bae2f188a8ae69cff8a2c5239942b1ba10", null ],
      [ "SCE_VOICE_BIT_RATE_5700", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944ba48cd9e82b3f4980785761dcb2d6029f7", null ],
      [ "SCE_VOICE_BIT_RATE_7300", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944ba3725f44f9a0f9a86eb1160f2e68a3ff6", null ],
      [ "SCE_VOICE_BIT_RATE_12200", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944bad5a2f4aac118106c7b4575a30f46eff3", null ]
    ] ],
    [ "SceVoicePcmDataType", "group__SceVoiceUser.html#ga153a86e27a8c2df9330267be5f796fe0", [
      [ "SCE_VOICE_PCM_DATA_TYPE_S16LE", "group__SceVoiceUser.html#gga153a86e27a8c2df9330267be5f796fe0ae2af796c584b9373c503832ac13a783c", null ]
    ] ],
    [ "SceVoiceSamplingRate", "group__SceVoiceUser.html#ga97c02381cb676d31c1c6ea0bb35ec786", [
      [ "SCE_VOICE_SAMPLING_RATE_16000", "group__SceVoiceUser.html#gga97c02381cb676d31c1c6ea0bb35ec786ac1d8fa09234dace6b56219563dbcadb3", null ]
    ] ],
    [ "SceVoicePortAttr", "group__SceVoiceUser.html#ga77acdeb58a29ee640cabcdabd84bf40a", [
      [ "SCE_VOICE_PORT_ATTR_AUDIO_INPUT_OWNERSHIP", "group__SceVoiceUser.html#gga77acdeb58a29ee640cabcdabd84bf40aa95667cbf6302b8fd5d05fcbdf2212236", null ]
    ] ],
    [ "SceVoiceEventType", "group__SceVoiceUser.html#ga0fdc1ac84e596e6838ad6c22242603fb", [
      [ "SCE_VOICE_EVENT_TYPE_PORT_DATA_READY", "group__SceVoiceUser.html#gga0fdc1ac84e596e6838ad6c22242603fbafabc89ab88ba46204d1e8a5dd63d4b83", null ],
      [ "SCE_VOICE_EVENT_TYPE_AUDIO_INPUT_OWNERSHIP_CHANGED", "group__SceVoiceUser.html#gga0fdc1ac84e596e6838ad6c22242603fbab45b70d6286602f033616d86cb2da73a", null ]
    ] ],
    [ "SCE_VOICE_ERROR_NOT_INITIALIZED", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fa51b9a0b4084d38cea9eb67aebd2d02e0", null ],
    [ "SCE_VOICE_ERROR_ALREADY_INITIALIZED", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faea7f79edac61439c77060dff6aedba01", null ],
    [ "SCE_VOICE_ERROR_INTERNAL", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fab19d1bf3731bac417970c8a7d1e5f369", null ],
    [ "SCE_VOICE_ERROR_INVALID_PORT_ID", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fa28a2cad42c56ea72d98d583cf967c327", null ],
    [ "SCE_VOICE_ERROR_INVALID_ARGUMENT", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faf1024b91a7a968b546a0e869c29ac5d3", null ],
    [ "SCE_VOICE_ERROR_INVALID_MEMBLOCK", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fa03723c788eebb3efe640ea7a81b5f966", null ],
    [ "SCE_VOICE_ERROR_INVALID_PORT", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faf86ecf08c5f4e948de853864d9d71e0d", null ],
    [ "SCE_VOICE_ERROR_RESOURCE_LIMIT", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769faeee5ff6c85980d1b41db253be91fb8eb", null ],
    [ "SCE_VOICE_ERROR_NOT_STARTED", "group__SceVoiceUser.html#gga2d12674892c52001f6fe51a5d726769fab5af21e9255a12a9e059e5c6645801b9", null ],
    [ "SCE_VOICE_APPLICATION_TYPE_UNK_0x20000000", "group__SceVoiceUser.html#gga513046a1d02c344291e80a003bd770bfacbbaec44286d5060028d9c1f749ec947", null ],
    [ "SCE_VOICE_APPLICATION_TYPE_UNK_0x80000000", "group__SceVoiceUser.html#gga513046a1d02c344291e80a003bd770bfa8eb4ff356ae327ac9634bb3fb4332153", null ],
    [ "SCE_VOICE_PORT_TYPE_IN_DEVICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a9f865edb8f96bc1736218d638f144742", null ],
    [ "SCE_VOICE_PORT_TYPE_IN_PCMAUDIO", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a5ab93a34e42671895cab242cf97c40f2", null ],
    [ "SCE_VOICE_PORT_TYPE_IN_VOICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a579e8a0e095f08389c0f88ae1640a9c4", null ],
    [ "SCE_VOICE_PORT_TYPE_OUT_PCMAUDIO", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a62c9a5c2da10ba02de3a948729927d0b", null ],
    [ "SCE_VOICE_PORT_TYPE_OUT_VOICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a5a50cae3af5ea0f0a0bfa8b8504bf595", null ],
    [ "SCE_VOICE_PORT_TYPE_OUT_DEVICE", "group__SceVoiceUser.html#ggad406ca767589c75f8da1d6a9e4b44c03a122f66fe14ee4a8240804777d3431a40", null ],
    [ "SCE_VOICE_PORT_STATE_INACTIVE", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98ba51b152b8f37235c6891fc4f1ae604c0a", null ],
    [ "SCE_VOICE_PORT_STATE_IDLE", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98ba5737643cf91d306556da9e4f2a6e38a8", null ],
    [ "SCE_VOICE_PORT_STATE_BUFFERING", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98bacf02803cda1820c921090b62fe70b178", null ],
    [ "SCE_VOICE_PORT_STATE_ACTIVE", "group__SceVoiceUser.html#ggaab08afebb9b74e2a8412eef2fa78a98ba1c8120ff2cf807bf3ead3db8d8a19402", null ],
    [ "SCE_VOICE_BIT_RATE_3850", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944ba7b01867c2b55c84ccad84aea34562339", null ],
    [ "SCE_VOICE_BIT_RATE_4650", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944bae2f188a8ae69cff8a2c5239942b1ba10", null ],
    [ "SCE_VOICE_BIT_RATE_5700", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944ba48cd9e82b3f4980785761dcb2d6029f7", null ],
    [ "SCE_VOICE_BIT_RATE_7300", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944ba3725f44f9a0f9a86eb1160f2e68a3ff6", null ],
    [ "SCE_VOICE_BIT_RATE_12200", "group__SceVoiceUser.html#gga1882d031857e440181fcf51bb80f944bad5a2f4aac118106c7b4575a30f46eff3", null ],
    [ "SCE_VOICE_PCM_DATA_TYPE_S16LE", "group__SceVoiceUser.html#gga153a86e27a8c2df9330267be5f796fe0ae2af796c584b9373c503832ac13a783c", null ],
    [ "SCE_VOICE_SAMPLING_RATE_16000", "group__SceVoiceUser.html#gga97c02381cb676d31c1c6ea0bb35ec786ac1d8fa09234dace6b56219563dbcadb3", null ],
    [ "SCE_VOICE_PORT_ATTR_AUDIO_INPUT_OWNERSHIP", "group__SceVoiceUser.html#gga77acdeb58a29ee640cabcdabd84bf40aa95667cbf6302b8fd5d05fcbdf2212236", null ],
    [ "SCE_VOICE_EVENT_TYPE_PORT_DATA_READY", "group__SceVoiceUser.html#gga0fdc1ac84e596e6838ad6c22242603fbafabc89ab88ba46204d1e8a5dd63d4b83", null ],
    [ "SCE_VOICE_EVENT_TYPE_AUDIO_INPUT_OWNERSHIP_CHANGED", "group__SceVoiceUser.html#gga0fdc1ac84e596e6838ad6c22242603fbab45b70d6286602f033616d86cb2da73a", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#gad608c7259fae53366165912c4c1a2a81", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#ga40000005b372ce2ce812f7b26ad419e7", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#ga652b9253a5f8021adc6a3238509dd071", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#gae045d4efd301c74791cba85c5558cf8c", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#ga7238d42471c9ba68f9f6ca89d7b5e14a", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#ga6577663eb492e48135a5fe46a03efb46", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#gac8b7c150830523cad5990e9f750d4107", null ],
    [ "VITASDK_BUILD_ASSERT_EQ", "group__SceVoiceUser.html#ga6014e6fa17edc191ab85c460f5c3274b", null ],
    [ "sceVoiceInit", "group__SceVoiceUser.html#ga5c31202daedeaf73690f2096ce375208", null ],
    [ "sceVoiceEnd", "group__SceVoiceUser.html#gab694c98909257d78670576996670631b", null ],
    [ "sceVoiceStart", "group__SceVoiceUser.html#ga4654d86b71747fab925520a81c098439", null ],
    [ "sceVoiceStop", "group__SceVoiceUser.html#ga8d5b9bfab0f6affb4570d64a8ea23c55", null ],
    [ "sceVoiceGetResourceInfo", "group__SceVoiceUser.html#ga76f238a5ca0e9cd38d0c69d66b2acea0", null ],
    [ "sceVoiceCheckTopology", "group__SceVoiceUser.html#ga6bc83f0377085c35d6549a45858f21b2", null ],
    [ "sceVoiceSetMuteFlagAll", "group__SceVoiceUser.html#ga718d9b8c01e261c3ca9050f1f57746e0", null ],
    [ "sceVoiceSetMuteFlag", "group__SceVoiceUser.html#gaa074ad0b220ba5fa746b80304e944867", null ],
    [ "sceVoiceGetMuteFlag", "group__SceVoiceUser.html#gaae8a1d11f1865b698debb83f1cfbef7a", null ],
    [ "sceVoiceSetVolume", "group__SceVoiceUser.html#ga645a5b3d75ca7601d50962d53ca860de", null ],
    [ "sceVoiceGetVolume", "group__SceVoiceUser.html#gaf30c5f1d6fd050cc628b8dd73a45c1b8", null ],
    [ "sceVoiceSetBitRate", "group__SceVoiceUser.html#ga0695a3302dd76609151fe03098eca285", null ],
    [ "sceVoiceGetBitRate", "group__SceVoiceUser.html#gafaca850d8b71e44aa06ea11c7d152d70", null ],
    [ "sceVoiceSetPortAttr", "group__SceVoiceUser.html#ga6c807d594043e8869c37c0f52ee5152b", null ],
    [ "sceVoiceGetPortAttr", "group__SceVoiceUser.html#ga2e6d653c11f7ad3ac98d9311733645d4", null ],
    [ "sceVoiceCreatePort", "group__SceVoiceUser.html#gad94ff62b563d4cf072b9634211df6f9a", null ],
    [ "sceVoiceUpdatePort", "group__SceVoiceUser.html#ga3645f2750b61101179659d23fd548c71", null ],
    [ "sceVoiceConnectIPortToOPort", "group__SceVoiceUser.html#ga4fabf4af1d4ad28712d08b88f122c173", null ],
    [ "sceVoiceDisconnectIPortFromOPort", "group__SceVoiceUser.html#ga85d1ca83cf9c67d0ee37e1f8ae99460a", null ],
    [ "sceVoiceDeletePort", "group__SceVoiceUser.html#gabf5d40ccf14ead1583f4ce314bb51ecd", null ],
    [ "sceVoiceWriteToIPort", "group__SceVoiceUser.html#ga19dfe11134c217ba8fe24e998571c97a", null ],
    [ "sceVoiceReadFromOPort", "group__SceVoiceUser.html#ga6cfb105dae221c267a845c866fa2b552", null ],
    [ "sceVoiceGetPortInfo", "group__SceVoiceUser.html#ga8ba8ac965d9b357aa7c7b0226b4a2892", null ],
    [ "sceVoiceResetPort", "group__SceVoiceUser.html#ga4f0971dca2c8857762f863b07982246e", null ],
    [ "sceVoicePausePort", "group__SceVoiceUser.html#ga139ae4230637296e02e9359779f5d4ed", null ],
    [ "sceVoiceResumePort", "group__SceVoiceUser.html#ga94c8146ccea00ce2064910bbaac19e8c", null ],
    [ "sceVoicePausePortAll", "group__SceVoiceUser.html#ga1f238825319a6853beb1a86277d96c78", null ],
    [ "sceVoiceResumePortAll", "group__SceVoiceUser.html#gafd5076bdfa79720e55d790b963641c1b", null ],
    [ "SceVoiceEventPortDataReady::port_count", "group__SceVoiceUser.html#ga5d279b13c9c30d4a0556fb408d2edbe1", null ],
    [ "SceVoiceEventPortDataReady::port_ids", "group__SceVoiceUser.html#ga4d6b3ee4278f178954c730ff40fb57d4", null ],
    [ "SceVoiceEventAudioInputOwnershipChanged::owned", "group__SceVoiceUser.html#gabc8c3fb4afc7e0e678b792048d7421ff", null ],
    [ "SceVoiceEventAudioInputOwnershipChanged::reserved", "group__SceVoiceUser.html#ga20d9896b1fd20df32c5349c94503d2f7", null ],
    [ "SceVoiceEvent::event_type", "group__SceVoiceUser.html#ga78f80fd983b9b6d0307cf132f2012fc1", null ],
    [ "SceVoiceEvent::user_data", "group__SceVoiceUser.html#ga1440e5495522c0c37e0e319cc8664eeb", null ],
    [ "SceVoiceEvent::@11::port_data_ready", "group__SceVoiceUser.html#ga4588717ee1c3ba398ad2d8b741e9be93", null ],
    [ "SceVoiceEvent::@11::audio_input_ownership_changed", "group__SceVoiceUser.html#ga7de3b56f9a445208636c0a80474a2b71", null ],
    [ "SceVoiceEvent::event_payload", "group__SceVoiceUser.html#ga82c0a6ecac018db0bf8eff16b50f0cc7", null ],
    [ "SceVoiceInitParam::application_type", "group__SceVoiceUser.html#gaf20a369a7e5deea750c575fede00fa59", null ],
    [ "SceVoiceInitParam::event_callback", "group__SceVoiceUser.html#ga9fb7c9d9e0f3fd2c5aed0005023471f5", null ],
    [ "SceVoiceInitParam::user_data", "group__SceVoiceUser.html#gaf42af2f83901cfe7aefb4a266063da21", null ],
    [ "SceVoiceInitParam::reserved", "group__SceVoiceUser.html#gab1f0d7d42f731ad59d873de3c5a185db", null ],
    [ "SceVoiceStartParam::mem_block_id", "group__SceVoiceUser.html#gaf4c3a664322eeebf82924909d16ca838", null ],
    [ "SceVoiceStartParam::reserved", "group__SceVoiceUser.html#gac3fb72b81d10e34cc9db346646f97d64", null ],
    [ "SceVoicePortParam::port_type", "group__SceVoiceUser.html#ga9c3f63602faace0423de9520d13d509f", null ],
    [ "SceVoicePortParam::threshold", "group__SceVoiceUser.html#ga7f67521b26916a2ddc5728e695883806", null ],
    [ "SceVoicePortParam::mute_flag", "group__SceVoiceUser.html#ga9a08a4338184779314e0348dd3da02f0", null ],
    [ "SceVoicePortParam::volume", "group__SceVoiceUser.html#ga68c25d735c992e09e91a319658d2a7b7", null ],
    [ "SceVoicePortParam::@12::buffer_size", "group__SceVoiceUser.html#gaffbb0096d68da5cf109900f8cd9daa8c", null ],
    [ "SceVoicePortParam::@12::bit_rate", "group__SceVoiceUser.html#gafaa102c9de57572c78a35252508617ef", null ],
    [ "SceVoicePortParam::data", "group__SceVoiceUser.html#gad43aa9f9ee8cfc920465c14a9a9be36c", null ],
    [ "SceVoicePortParam::pcm_data_type", "group__SceVoiceUser.html#ga906222aa508c1ff99603142203be793d", null ],
    [ "SceVoicePortParam::sampling_rate", "group__SceVoiceUser.html#ga91608c7c7de29adbc61b5ad43e9e05d8", null ],
    [ "SceVoiceResourceInfo::max_voice_input_ports", "group__SceVoiceUser.html#ga62163b9ed7eccd8595548a3ab173cc0e", null ],
    [ "SceVoiceResourceInfo::max_voice_output_ports", "group__SceVoiceUser.html#ga5136de8fdc8c03a00a2ed47da0059841", null ],
    [ "SceVoiceResourceInfo::max_device_input_ports", "group__SceVoiceUser.html#ga74787d00076115ad59331aeb821c3c9b", null ],
    [ "SceVoiceResourceInfo::max_device_output_ports", "group__SceVoiceUser.html#gaca9506fb106a0531fdcf5ea07a4a4626", null ],
    [ "SceVoiceResourceInfo::max_ports", "group__SceVoiceUser.html#gac99dfb8f640cf0b0f4406f89a416fddc", null ],
    [ "SceVoicePortInfo::port_type", "group__SceVoiceUser.html#ga289e7ef2ddd69b444e381aac343cc505", null ],
    [ "SceVoicePortInfo::state", "group__SceVoiceUser.html#ga67ac166d74538642bc436971dc05ffef", null ],
    [ "SceVoicePortInfo::reserved0", "group__SceVoiceUser.html#ga3b58e15d6d1518859d492b29ac3b423a", null ],
    [ "SceVoicePortInfo::data_size", "group__SceVoiceUser.html#ga0c3f961bc86d97689ca2f436b59f7a91", null ],
    [ "SceVoicePortInfo::frame_size", "group__SceVoiceUser.html#gaf246946fc3f0db2f7ecb09272b8fa656", null ],
    [ "SceVoicePortInfo::reserved1", "group__SceVoiceUser.html#ga0d8d543eb96897644f3132d58e042e05", null ]
];