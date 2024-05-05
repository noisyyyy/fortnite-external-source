#include "includes/includes.hpp"
#include <iostream>
#include <stdio.h>
#include "auth.hpp"
#include <tchar.h>
#include <urlmon.h>
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"wininet.lib")

#include <Windows.h>
#include <string>
#include "includes/utils.hpp"
#include <urlmon.h>
#include <tchar.h>

#include "general.h"
#include "kdmapper/kdmapper.hpp"
#include <random>

using namespace std;

using namespace KeyAuth;

auto name = E("");
auto ownerid = E("");
auto secret = E("");
auto version = E("1.0");
auto url = skCrypt("https://keyauth.win/api/1.2/");
api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());



static std::time_t string_to_timet(std::string timestamp) {


	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {


	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

std::string tm_to_readable_time2(tm ctx) {


	std::time_t now = std::time(nullptr);
	std::time_t expiry = std::mktime(&ctx);

	double remainingSeconds = std::difftime(expiry, now);

	if (remainingSeconds >= 60 * 60 * 24) {
		int remainingDays = static_cast<int>(remainingSeconds / (60 * 60 * 24));
		return std::to_string(remainingDays) + " day(s).";
	}
	else if (remainingSeconds >= 60 * 60) {
		int remainingHours = static_cast<int>(remainingSeconds / (60 * 60));
		return std::to_string(remainingHours) + " hour(s).";
	}
	else {
		int remainingMinutes = static_cast<int>(remainingSeconds / 60);
		return std::to_string(remainingMinutes) + " minute(s).";
	}
}

void DeleteKey(std::ifstream& File)
{

	std::string regfile("key.txt");
	std::ofstream(regfile, std::ios::trunc);
	File.setstate(std::ios::failbit);
	remove(regfile.c_str());
}

void sleepMilliseconds(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::string readFileIntoString(const std::string& path) {


	auto ss = std::ostringstream{};
	std::ifstream input_file(path);
	if (!input_file.is_open()) {
		std::cerr << E("Could Not Open License Key File") << std::endl;
		exit(EXIT_FAILURE);
	}
	ss << input_file.rdbuf();
	return ss.str();
}

HWND windowid = NULL;





int choice;


bool fileExists(const std::string& filename) {
	std::ifstream file(filename.c_str());
	return file.good();
}

void slowPrint(const std::string& text, std::chrono::milliseconds delay) {
	for (char c : text) {
		std::cout << c << std::flush;
		std::this_thread::sleep_for(delay);
	}
}
void rndmTitle() {
	constexpr int length = 25;
	const auto characters = (("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	TCHAR title[length + 1]{};

	while (true) {
		for (int j = 0; j != length; j++) {
			title[j] = characters[rand() % 55 + 1];
		}

		SetConsoleTitle(title);

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
std::thread titleThread;

BOOL WINAPI MyHandlerRoutine(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		//HWND handle = FindWindowA(NULL, "Untitled - Paint");
		//ShowWindow(handle, SW_SHOW);
		system(E("taskkill /F /T /IM mspaint.exe"));
	}
	return FALSE;
}

DWORD processID;

struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

static std::uint32_t _GetProcessId(std::string process_name) {
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return 0;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE) {
		if (process_name.compare(processentry.szExeFile) == 0)
			return processentry.th32ProcessID;
	}
	return 0;
}

bool CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size)
{
	std::ofstream file_ofstream(desired_file_path.c_str(), std::ios_base::out | std::ios_base::binary);

	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();
		return false;
	}

	file_ofstream.close();
	return true;
}
#include "bytes.h"

void loader()
{
	auto drv = E("C:\\Windows\\System32\\dr.sys").decrypt();
	auto mp = E("C:\\Windows\\System32\\mp.exe").decrypt();

	CreateFileFromMemory(drv, reinterpret_cast<const char*>(bytes3), sizeof(bytes3));
	CreateFileFromMemory(mp, reinterpret_cast<const char*>(bytes2), sizeof(bytes2));



	system(E("C:\\Windows\\System32\\mp.exe C:\\Windows\\System32\\dr.sys").decrypt());

	remove(E("C:\\Windows\\System32\\dr.sys").decrypt());
	remove(E("C:\\Windows\\System32\\mp.exe").decrypt());

}


int main()
{

	std::thread security(security_loop);
	name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();
	mouse_interface();

	std::string consoleTitle = skCrypt("Xotic.wtff Fortnite Public").decrypt();
	SetConsoleTitleA(consoleTitle.c_str());
	Sleep(200);
	system(E("cls").decrypt());
	KeyAuthApp.init();

	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ").decrypt() << KeyAuthApp.data.message;
		Sleep(1500);
		exit(1);
	}
	std::cout << skCrypt("\n[1] License key only\n\n Choose option: ").decrypt();

	int option;
	std::string key;

	std::cin >> option;
	switch (option)
	{
	
	case 1:
		system(E("cls").decrypt());
		std::cout << skCrypt("\n Enter license: ").decrypt();
		std::cin >> key;
		KeyAuthApp.license(key);
		break;
	default:
		system(E("cls").decrypt());
		std::cout << skCrypt("\n\n Status: Failure: Invalid Selection").decrypt();
	    Sleep(3000);
		exit(1);
	}

	if (!KeyAuthApp.data.success)
	{
		system(E("cls").decrypt());
	   std::cout << skCrypt("\n Status: ").decrypt() << KeyAuthApp.data.message;
		Sleep(1500);
		exit(1);
	}
		system(E("cls").decrypt());
	//string DriverPin = E("886027").decrypt();
	//std::vector<std::uint8_t> stdafx = KeyAuthApp.download(DriverPin);
	//disk(stdafx);


	system("color a");




		if (Cheat_shi.River)
		{
			Cheat_shi.Cheat_name = E("Xotic.wtff");
			Cheat_shi.Cheat_Version = E("Public");
			Cheat_shi.branding_type = 1;
		}

	

		LI_FN(Sleep)(1000);
		ShowWindow_Spoofed(GetConsoleWindow(), SW_HIDE);
		loader();

		system(E("cls").decrypt());

		LI_FN(Sleep)(1000);
		ShowWindow_Spoofed(GetConsoleWindow(), SW_SHOW);


		LI_FN(Sleep)(1000);
		std::cout << (skCrypt(" Waiting For Game...")) << std::flush;


		while (windowid == NULL)
		{
			XorS(wind, "Fortnite  ");
			windowid = FindWindowA_Spoofed(0, wind.decrypt());

		}

		LI_FN(Sleep)(1000);

		globals->hwnd = FindWindowA_Spoofed(NULL, "Fortnite  ");

		LI_FN(Sleep)(1000);
		system(E("cls").decrypt());

		std::cout << (skCrypt("[+] Found Game.")) << std::flush;
		system(E("cls").decrypt());
		LI_FN(Sleep)(1000);

		if (!librarys::init)
		{
			printf("\n The Libraries did not load");
			Sleep(5000);
			exit(0);

		}
		else
		{
			printf("\n The Libraries Loaded");
		}
		while (!driver.init()) {

			std::cout << "Driver is not loaded\n";

		}
		
		system(E("cls").decrypt());
		


		driver.process_id = driver.get_process_id("FortniteClient-Win64-Shipping.exe");
		driver.base_address = driver.get_base_address();
		virtualaddy = driver.base_address;

		if (virtualaddy)
		{
			LI_FN(Sleep)(1000);
			std::cout << (skCrypt(" Got Base Address -> ")) << virtualaddy << std::flush;

			LI_FN(Sleep)(1000);



		}
		else
		{
			std::cout << (skCrypt(" Failed To Get Base Address")) << std::flush;
			LI_FN(Sleep)(-1);
			LI_FN(exit)(0);

		}


		std::cout << virtualaddy << std::endl; 


		globals->width = GetSystemMetrics_Spoofed(SM_CXSCREEN); globals->height = GetSystemMetrics_Spoofed(SM_CYSCREEN);


		if (!Utilities->debug)
		{

			ShowWindow_Spoofed(GetConsoleWindow(), SW_HIDE);

		}


		if (Render1->Setup() != RENDER_INFORMATION::RENDER_SETUP_SUCCESSFUL) ExitProcess(0);


		if (Hook->Setup() != HOOK_INFORMATION::HOOKS_SUCCESSFUL) ExitProcess(0);

		if (Game->Setup() != GAME_INFORMATION::GAME_SETUP_SUCCESSFUL) ExitProcess(0);

		Render1->Render();
	
}

