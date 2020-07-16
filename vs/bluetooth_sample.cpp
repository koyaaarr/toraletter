#include <Windows.h>
#include<iostream>
#include <BluetoothAPIs.h>

#pragma comment(lib, "Bthprops")



int main() {

	while (1) {
		BLUETOOTH_DEVICE_SEARCH_PARAMS params = { 0 };
		params.fReturnAuthenticated = TRUE;
		params.fReturnRemembered = TRUE;
		params.fReturnUnknown = TRUE;
		params.fReturnConnected = TRUE;
		params.fIssueInquiry = TRUE;
		params.cTimeoutMultiplier = 5;
		params.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);

		BLUETOOTH_DEVICE_INFO info = { 0 };
		info.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
		HBLUETOOTH_DEVICE_FIND find = BluetoothFindFirstDevice(&params, &info);

		if (find) {
			do {
				std::wcout << info.szName << std::endl;
			} while (BluetoothFindNextDevice(find, &info));

			BluetoothFindDeviceClose(find);
		}
	}
	

system("pause");
return 0;

}