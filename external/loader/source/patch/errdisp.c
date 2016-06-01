#include "patch.h"

void errdisp_devpatch(u64 progId, u8* code, u32 size) {
	static const u8 unitinfoCheckPattern1[] = {0x14, 0x00, 0xD0, 0xE5, 0xDB, 0x9A, 0x9F, 0xED};
	static const u8 unitinfoCheckPattern2[] = {0x14, 0x00, 0xD0, 0xE5, 0x01, 0x00, 0x10, 0xE3} ;
	static const u8 unitinfoCheckPatch[] = {0x00, 0x00, 0xA0, 0xE3} ;

	patchMemory(code, size,
		unitinfoCheckPattern1,
		sizeof(unitinfoCheckPattern1), 0,
		unitinfoCheckPatch,
		sizeof(unitinfoCheckPatch), 1
	);

	patchMemory(code, size,
		unitinfoCheckPattern2,
		sizeof(unitinfoCheckPattern2), 0,
		unitinfoCheckPatch,
		sizeof(unitinfoCheckPatch), 3
	);
}
