#include "stdafx.h"
#include "Block.h"


CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}

CBlock::CBlock(DWORD dwAddress, TYPE ntype)
{
	m_dwAddress = dwAddress;
	m_type = ntype;
}
