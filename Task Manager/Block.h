#pragma once
enum TYPE{ ONE_BYTE = 1, TWO_BYTE = 2, FOUR_BYTE = 4, EIGHT_BYTE = 8 };

class CBlock
{
public:
	CBlock();
	CBlock(DWORD dwAddress, TYPE ntype);
	~CBlock();

public:
	DWORD m_dwAddress;
	TYPE m_type;
};

