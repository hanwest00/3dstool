#ifndef PATCH_H_
#define PATCH_H_

#include "utility.h"
#include "3dstool.h"

class CPatch
{
public:
	enum EPatchCommand
	{
		kPatchCommandOver,
		kPatchCommandCheck,
		kPatchCommandMove,
		kPatchCommandSet,
		kPatchCommandChangeSize,
		kPatchCommandSeekWrite = 0x10
	};
	struct S3DSPatchSystemHeader
	{
		u32 Signature;
		u8 VersionMajor;
		u8 VersionMinor;
		u8 VersionPatchLevel;
		u8 Reserved;
		n64 ExtDataOffset;
	};
	CPatch();
	~CPatch();
	void SetFileType(C3DSTool::EFileType a_eFileType);
	void SetFileName(const char* a_pFileName);
	void SetVerbose(bool a_bVerbose);
	void SetOldFileName(const char* a_pOldFileName);
	void SetNewFileName(const char* a_pNewFileName);
	void SetPatchFileName(const char* a_pPatchFileName);
	bool CreatePatchFile();
	bool ApplyPatchFile();
	static const u32 s_uSignature;
	static const u8 s_uCurrentVersionMajor;
	static const u8 s_uCurrentVersionMinor;
	static const u8 s_uCurrentVersionPatchLevel;
private:
	bool createNcsdPatchFile();
	bool createNcchPatchFile(C3DSTool::EFileType a_eFileType, n64 a_nOffsetOld, n64 a_nOffsetNew, bool a_bCreateCheck);
	bool createPatchFile(n64 a_nOffsetOld, n64 a_nSizeOld, n64 a_nOffsetNew, n64 a_nSizeNew);
	void writeOver();
	void writeCheck(n64 a_nOffset, n64 a_nSize, u8* a_pSHA256);
	void writeMove(n64 a_nFromOffset, n64 a_nToOffset, n64 a_nSize);
	void writeSet(n64 a_nStartOffset, n64 a_nSize, u8 a_uData);
	void writeChangeSize(n64 a_nSize);
	void writeSeekWrite(bool a_bSeekSet, n64 a_nOffset, size_t a_nSize, u8* a_pData);
	void writePatch(u8 a_uPatchCommand, n64* a_pArg);
	void calculateVersion();
	void executeMove(n64 a_nFromOffset, n64 a_nToOffset, n64 a_nSize);
	void executeSet(n64 a_nStartOffset, n64 a_nSize, u8 a_uData);
	void executeChangeSize(n64 a_nSize);
	void executeSeekWrite(bool a_bSeekSet, n64 a_nOffset, size_t a_nSize, u8* a_pData);
	C3DSTool::EFileType m_eFileType;
	const char* m_pFileName;
	bool m_bVerbose;
	const char* m_pOldFileName;
	const char* m_pNewFileName;
	const char* m_pPatchFileName;
	FILE* m_fpOld;
	FILE* m_fpNew;
	FILE* m_fpPatch;
	S3DSPatchSystemHeader m_3DSPatchSystemHeader;
	u32 m_uVersion;
};

#endif	// PATCH_H_
