#include "stdafx.h"
#include "pch.h"
#include "FileRW.h"

void RoyaReadFile(CString strPath, CStringArray &m_saRead)
{
	CFile file;
	file.Open(strPath,CFile::modeNoTruncate|CFile::modeReadWrite|CFile::modeCreate);
	DWORD dLength=file.SeekToEnd( );
	file.SeekToBegin( );
	CString strFile;
	long length=(long)dLength;
	while(strFile.GetLength()<length)
	{
		char buffer[1024];
		int iRead=file.Read(buffer,1024);
		buffer[iRead]=0;
		strFile+=buffer;
	}
	int iF=strFile.Find("\r\n");
	while(iF!=-1)
	{
		m_saRead.Add(strFile.Left(iF));
		strFile.Delete(0,iF+2);
		iF=strFile.Find("\r\n");
	}
	m_saRead.Add(strFile);
	file.Close();
}

void RoyaWriteFile(CString strPath, CString		strWrite)
{
	CFile file(strPath,CFile::modeCreate|CFile::modeReadWrite);
	file.Write(strWrite,strWrite.GetLength());                      // ÐÞ¸ÄWriteHugeÎªWrite 
	file.Close();
}

bool JudgeFileExist(CString strPath)
{
	try
	{
	CFile file;
	file.Open(strPath,CFile::modeRead);
	CString strFile;
	
		char buffer[10];
		int iRead=file.Read(buffer,10);
		buffer[iRead]=0;
		strFile+=buffer;
	}
	catch(CFileException*	pe)
	{
		return false;
		pe->ReportError();		
	}
	return true;
}

bool RemoveFileExist(CString strPath)
{
	try
	{
	CFile file;
//	file.Open(strPath,CFile::modeRead);
	file.Remove(strPath);
	}
	catch(CFileException*	pe)
	{
		return false;
		pe->ReportError();		
	}
	return true;
}