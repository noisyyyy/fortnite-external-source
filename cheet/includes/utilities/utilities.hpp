#pragma once

enum bone : int
{
	HumanBase = 0,
	HumanPelvis = 2,
	HumanLThigh1 = 71,
	HumanLThigh2 = 77,
	HumanLThigh3 = 72,
	HumanLCalf = 74,
	HumanLFoot2 = 73,
	HumanLFoot = 86,
	HumanLToe = 76,
	HumanRThigh1 = 78,
	HumanRThigh2 = 84,
	HumanRThigh3 = 79,
	HumanRCalf = 81,
	HumanRFoot2 = 82,
	HumanRFoot = 87,
	HumanRToe = 83,
	HumanSpine1 = 7,
	HumanSpine2 = 5,
	HumanSpine3 = 2,
	HumanLCollarbone = 9,
	HumanLUpperarm = 35,
	HumanLForearm1 = 36,
	HumanLForearm23 = 10,
	HumanLForearm2 = 34,
	HumanLForearm3 = 33,
	HumanLPalm = 32,
	HumanLHand = 11,
	HumanRCollarbone = 98,
	HumanRUpperarm = 64,
	HumanRForearm1 = 65,
	HumanRForearm23 = 39,
	HumanRForearm2 = 63,
	HumanRForearm3 = 62,
	HumanRHand = 40,
	HumanRPalm = 58,
	HumanNeck = 67,
	HumanHead = 110,
	HumanLowerHead = 106,

	HumanChest = 66
};

enum offset {
	uworld = 0x12634238, // new
	game_instance = 0x1D8, // new
	game_state = 0x160, // new
	persistent_level = 0x30, // new
	local_player = 0x38, // new
	player_controller = 0x30, // new
	acknowledged_pawn = 0x338, // new
	skeletal_mesh = 0x540,  // new
	player_state = 0x2B0, // new
	root_component = 0x198, // new
	relative_location = 0x120, // new
	relative_rotation = 0x138, // new
	team_index = 0x1211, // new
	player_array = 0x2A8, // new
	pawn_private = 0x308, // new
	current_weapon = 0xa20, // new
	weapon_data = 0x4F0, // new
	velocity = 0x168, // new
	tier = 0x0,
	is_cached = 0x45c,
	bone_array = 0x5B0, // new
	custom_time_dilation = 0x68, // new
	component_to_world = 0x1c0, // new
	location_under_reticle = 0x2560,
	fLastSubmitTime = 0x368,
	fLastRenderTimeOnScreen = 0x370,
};



class Pointers {
public:
	uintptr_t
		uworld,
		game_instance,
		game_state,
		local_player,
		acknowledged_pawn,
		player_state,
		player_controller,
		root_component,
		skeletal_mesh,
		persistent_level,
		world_settings,
		WorldGravityZ,
		player_array,
		levels,

		player_array_size,
		current_weapon,
		current_vehicle;
	int
		team_index;
	FVector
		relative_location;
}; static Pointers* pointer = new Pointers();

namespace camera
{
	FVector location, rotation;
	float fov;
}

struct WeaponInformation
{
	int32_t ammo_count;
	int32_t max_ammo;

	BYTE tier;
	std::string weapon_name;
	std::string buildplan;

};
std::string LocalPlayerWeapon;

struct Cheat_info
{

	std::string Cheat_name;
	std::string Cheat_Version;
	int branding_type = 0;
	bool star = false;
	bool orbit = false;
	bool River = true;


};

struct camera_position_s {
	FVector location{};
	FVector rotation{};
	float fov{};
};
inline camera_position_s camera_postion{};

Cheat_info Cheat_shi;

WeaponInformation WeaponInfo;

float target_dist = FLT_MAX;
uintptr_t  target_entity = NULL;
uintptr_t  desync_target_entity = NULL;
namespace utilities {
	class c_utilities {
	public:
		bool debug = 0;
		bool debug2 = 1;

		auto InScreen(FVector2d screen_position) -> bool {

			if (screen_position.x > 0 && screen_position.x < globals->width && screen_position.y > 0 && screen_position.y < globals->height)
				return true;
			else
				return false;

		}
		auto IsShootable(FVector lur, FVector wl) -> bool {

			if (lur.x >= wl.x - 20 && lur.x <= wl.x + 20 && lur.y >= wl.y - 20 && lur.y <= wl.y + 20 && lur.z >= wl.z - 30 && lur.z <= wl.z + 30)
				return true;
			else
				return false;

		}
		auto IsVisible(uintptr_t skeletal_mesh) -> bool {
			auto last_submit = driver.read<float>(skeletal_mesh + offset::fLastSubmitTime);
			auto last_render = driver.read<float>(skeletal_mesh + offset::fLastRenderTimeOnScreen);
			const float fVisionTick = 0.06f;
			bool visible = last_render + fVisionTick >= last_submit;
			return visible;
		}
		static auto GetBoneLocation(uintptr_t skeletal_mesh, int bone_index) -> FVector {
			bool bonedebgu = 0;
			uintptr_t bone_array = driver.read<uintptr_t>(skeletal_mesh + offset::bone_array);
			if (bonedebgu)
			{
				std::printf(" [bone_array] -> %I64d\n", bone_array);
			}
			if (bone_array == NULL) bone_array = driver.read<uintptr_t>(skeletal_mesh + offset::bone_array + 0x10);
			ftransform bone = driver.read<ftransform>(bone_array + (bone_index * 0x60));
			if (bonedebgu)
			{
				std::printf(" [bone] -> %I64d\n", bone);
			}
			ftransform component_to_world = driver.read<ftransform>(skeletal_mesh + offset::component_to_world);
			if (bonedebgu)
			{
				std::printf(" [component_to_world] -> %I64d\n", component_to_world);
			}
			D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), component_to_world.ToMatrixWithScale());
			return FVector(matrix._41, matrix._42, matrix._43);
		}
		struct FMinimalViewInfo
		{
			FVector Location, Rotation;
			float FOV;
		};
		struct CamewaDescwipsion
		{
			Vector3 Location;
			Vector3 Rotation;
			float FieldOfView;
		};
		static auto UpdateCamera() -> void
		{
			bool camdebgu = 0;
			auto location_pointer = driver.read<uintptr_t>(pointer->uworld + 0x110);
			if (camdebgu)
			{
				std::printf(" [location_pointer] -> %I64d\n", location_pointer);
			}
			auto rotation_pointer = driver.read<uintptr_t>(pointer->uworld + 0x120);
			if (camdebgu)
			{
				std::printf(" [rotation_pointer] -> %I64d\n", rotation_pointer);
			}
			struct FNRotation
			{
				double a; //0x0000
				char pad_0008[24]; //0x0008
				double b; //0x0020
				char pad_0028[424]; //0x0028
				double c; //0x01D0
			}tpmrotation;

			tpmrotation.a = driver.read<double>(rotation_pointer);
			tpmrotation.b = driver.read<double>(rotation_pointer + 0x20);
			tpmrotation.c = driver.read<double>(rotation_pointer + 0x1d0);

			if (camdebgu)
			{
				std::printf(" [tpmrotation.c] -> %I64d\n", tpmrotation.c);
			}
			if (camdebgu)
			{
				std::printf(" [tpmrotation.b] -> %I64d\n", tpmrotation.b);
			}

			camera::rotation.x = asin(tpmrotation.c) * (180.0 / M_PI);
			camera::rotation.y = ((atan2(tpmrotation.a * -1, tpmrotation.b) * (180.0 / M_PI)) * -1) * -1;
			camera::rotation.z = 0;
			camera::location = driver.read<FVector>(location_pointer);
			camera::fov = driver.read<float>(pointer->player_controller + 0x394) * 90.f;
			if (camdebgu)
			{
				std::printf(" [camera::fov] -> %I64d\n", camera::fov);
			}
		}
		static auto WorldToScreen(FVector worldlocation) -> FVector2d {


			D3DMATRIX tempMatrix = Matrix(camera::rotation);

			FVector vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
			FVector vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
			FVector vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

			FVector vDelta = worldlocation - camera::location;
			FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

			if (vTransformed.z < 1.f)
				vTransformed.z = 1.f;
			return FVector2d((globals->width / 2.0f) + vTransformed.x * (((globals->width / 2.0f) / tanf(camera::fov * (float)M_PI / 360.f))) / vTransformed.z, (globals->height / 2.0f) - vTransformed.y * (((globals->width / 2.0f) / tanf(camera::fov * (float)M_PI / 360.f))) / vTransformed.z);

		}
		int screen_width1;
		int screen_heigh1t;

		auto cursor_to(float x, float y) -> void {
			FVector center(globals->width / 2, globals->height / 2, 0);
			FVector target(0, 0, 0);

			if (x != 0) {
				if (x > center.x) {
					target.x = -(center.x - x);
					target.x /= (globals->smooth);
					if (target.x + center.x > center.x * 2)
						target.x = 0;
				}

				if (x < center.x) {
					target.x = x - center.x;
					target.x /= (globals->smooth);
					if (target.x + center.x < 0)
						target.x = 0;
				}
			}
			if (y != 0) {
				if (y > center.y) {
					target.y = -(center.y - y);
					target.y /= (globals->smooth);
					if (target.y + center.y > center.y * 2)
						target.y = 0;
				}

				if (y < center.y) {
					target.y = y - center.y;
					target.y /= (globals->smooth);
					if (target.y + center.y < 0)
						target.y = 0;
				}
			}
			const float snapThreshold = 1.0f;
			if (std::abs(target.x) < snapThreshold) {
				target.x = 0;
			}
			if (std::abs(target.y) < snapThreshold) {
				target.y = 0;
			}
			
			Inject->set_cursor_position(target.x, target.y);

		}

		
		FVector calc_angle(FVector LocalPos, FVector WorldPos) {
			FVector RelativePos = WorldPos - LocalPos;
			float yaw = atan2(RelativePos.y, RelativePos.x) * 180.0f / M_PI;
			float pitch = -((acos(RelativePos.z / LocalPos.Distance(WorldPos)) * 180.0f / M_PI) - 90.0f);
			return FVector(pitch, yaw, 0);
		}
		static void normalize(FVector& in)
		{
			while (in.x > 180.0f)
				in.x -= 360.0f;

			while (in.x < -180.0f)
				in.x += 360.0f;

			while (in.y > 180.0f)
				in.y -= 360.0f;

			while (in.y < -180.0f)
				in.y += 360.0f;

			in.z = 0;
		}
		__forceinline double Clamp(double value, double min, double max)
		{
			if (value < min) {
				return min;
			}
			else if (value > max) {
				return max;
			}
			else {
				return value;
			}
		}
		auto DecryptName(uintptr_t player_state) -> std::string
		{
			int pNameLength;
			_WORD* pNameBufferPointer;
			int i;
			char v25;
			int v26;
			int v29;

			char16_t* pNameBuffer;

			uintptr_t pNameStructure = driver.read < uintptr_t >(player_state + 0xAF0); //pNameStructure
			if (driver.is_valid(pNameStructure)) {
				pNameLength = driver.read <int>(pNameStructure + 0x10);
				if (pNameLength <= 0)
					return "AI";

				pNameBuffer = new char16_t[pNameLength];
				uintptr_t pNameEncryptedBuffer = driver.read <uintptr_t>(pNameStructure + 0x8);
				if (driver.is_valid(pNameEncryptedBuffer)) {
					driver.read_array(pNameEncryptedBuffer, pNameBuffer, pNameLength);

					v25 = pNameLength - 1;
					v26 = 0;
					pNameBufferPointer = (_WORD*)pNameBuffer;

					for (i = (v25) & 3;; *pNameBufferPointer++ += i & 7) {
						v29 = pNameLength - 1;
						if (!(_DWORD)pNameLength)
							v29 = 0;

						if (v26 >= v29)
							break;

						i += 3;
						++v26;
					}

					std::u16string temp_wstring(pNameBuffer);
					delete[] pNameBuffer;
					return std::string(temp_wstring.begin(), temp_wstring.end());
				}
			}
		}
		std::string RetreivePlayerWeapon(uintptr_t player)
		{

			uint64_t PlayersCurrentWeapon = driver.read<uint64_t>(player + offset::current_weapon);
			std::string PlayersWeaponName = "";

			if (PlayersCurrentWeapon) {

				uint64_t WeaponData = driver.read<uint64_t>(PlayersCurrentWeapon + offset::weapon_data);
				if (WeaponData) {

					uint64_t DisplayName = driver.read<uint64_t>(WeaponData + 0x90);

					if (DisplayName) {

						uint64_t FTextData = driver.read<uint64_t>(DisplayName + 0x38);
						int FTextLength = driver.read<int>(DisplayName + 0x30);

						if (FTextLength > 0 && FTextLength < 50) {

							wchar_t* WeaponBuffer = new wchar_t[FTextLength];
							driver.readm((PVOID)FTextData, (PVOID)WeaponBuffer, FTextLength * sizeof(wchar_t));
							std::wstring wstr_buf(WeaponBuffer);
							PlayersWeaponName.append(std::string(wstr_buf.begin(), wstr_buf.end()));

							delete[] WeaponBuffer;
						}
					}
				}
			}
			return PlayersWeaponName;
		}
		ImColor GetWeaponColor(uintptr_t weaponData)
		{
			uint8_t tier = driver.read<uint8_t>(weaponData + offset::tier);

			switch (tier)
			{
			case 0:
				return { 50, 205, 50 };
				break;
			case 1:
				return { 211, 211, 211 };
				break;
			case 2:
				return { 50 ,205 ,50 };
				break;
			case 3:
				return { 0, 0, 255 };
				break;
			case 4:
				return { 255, 0, 255 };
				break;
			case 5:
				return { 255, 165, 0 };
				break;
			}


			return { 255, 255, 255 };
		}
		ImColor GetWeaponDataColor(uintptr_t player)
		{
			uint64_t PlayersCurrentWeapon = driver.read<uint64_t>(player + offset::current_weapon);
			ImColor ReturnedColor = ImColor(255, 255, 255);

			if (PlayersCurrentWeapon) {

				uint64_t weapon_data = driver.read<uint64_t>(PlayersCurrentWeapon + offset::weapon_data);
				if (weapon_data)
				{
					ReturnedColor = GetWeaponColor(weapon_data);
				}
			}

			return ReturnedColor;
		}

		__forceinline std::string platform(uint64_t PlayerState)
		{
			PVOID test_platform = driver.read<PVOID>(PlayerState + 0x438);
			wchar_t platform[64];
			driver.readm(test_platform, (uint8_t*)platform, sizeof(platform));
			std::wstring platform_wstr(platform);
			std::string platform_str(platform_wstr.begin(), platform_wstr.end());
			return platform_str;
		}
		static float powf_(float _X, float _Y) {
			return (_mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y))));
		}
		static float sqrtf_(float _X) {
			return (_mm_cvtss_f32(_mm_sqrt_ps(_mm_set_ss(_X))));
		}
		static double GetCrossDistance(double x1, double y1, double x2, double y2) {
			return sqrtf(powf((x2 - x1), 2) + powf_((y2 - y1), 2));
		}

	};
} static utilities::c_utilities* Utilities = new utilities::c_utilities();