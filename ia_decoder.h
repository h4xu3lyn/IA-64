#ifndef _IA_DECODER_H
#define _IA_DECODER_H

EaInfoPtr ea16Info(ModRM modrm);
EaInfoPtr ea32Info(ModRM modrm);
BOOL ia_decode(ADDR4 eip, IAinstInfoPtr info);

#endif
