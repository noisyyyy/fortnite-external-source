#include <Windows.h>



namespace PlayerColor {
	float BoxVisible[4] = { 0.f, 255.0f, 0.0f, 0.0f };
	float BoxNotVisible[4] = { 255.f, 0.0f, 0.0f, 0.0f };
	float targetcol[4] = { 1.f, 0, 0, 1.0f };
	
	float accentcolor[4] = { 1.f, 1.f, 1.f, 1.0f };

	float SkeletonVisible[4] = { 0.f, 255.0f, 0.0f, 0.0f };
	float SkeletonNotVisible[4] =  { 255.f, 0.0f, 0.0f, 0.0f };

	float SnaplineVisible[4]{ 1.f, 1.f, 1.f };
	float SnaplineNotVisible[4];

	float TopTextVisible[4] = { 0.f, 255.0f, 0.0f, 0.0f };
	float TopTextNotVisible[4] = { 255.f, 0.0f, 0.0f, 0.0f };

	float BottomTextVisible[4] = { 0.f, 255.0f, 0.0f, 0.0f };
	float BottomTextNotVisible[4] = { 255.f, 0.0f, 0.0f, 0.0f };
}

namespace rifle
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool render_fov = 0;

	inline bool visible_check = 1;
	inline bool target_line = 1;
	inline float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;
}

namespace shotgun
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool render_fov = 0;

	inline bool visible_check = 1;
	inline bool target_line = 1;
	inline float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;



}

namespace smg
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool render_fov = 0;

	inline bool visible_check = 1;
	inline bool target_line = 1;
	inline 	float aim_fov = 15;
	inline 	float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;


}

namespace sniper
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool render_fov = 0;

	inline bool visible_check = 1;
	inline bool target_line = 1;
	inline	float aim_fov = 15;
	inline float smooth = 1;
	inline int hitbox = 0;
	inline int aimkey;
	inline int trggerbotkey;


	namespace images {
		IDirect3DTexture9* profile_img = nullptr;
		IDirect3DTexture9* profiles_img = nullptr;
		IDirect3DTexture9* car_img = nullptr;
		IDirect3DTexture9* yeas_img = nullptr;
		IDirect3DTexture9* aim_img = nullptr;
		IDirect3DTexture9* gun_img = nullptr;
		IDirect3DTexture9* settings_img = nullptr;
		IDirect3DTexture9* visual_img = nullptr;
	}
}


class c_globals {
public:
	int width, height;
	bool render_menu = 0;
	HWND hwnd = 0;


	bool pred1 = false;
	bool pred2 = false;
	bool pred3 = false;

	bool skeletons = 1;
	bool bounding_box = 1;
	bool username = 0;
	bool platform = 0;

	bool distance = 1;
	bool enemiesaround = 0;
	bool outline = 0;
	bool text_outline = 0;

	int font_size = 20;
	bool finger = 0;
	int add = 3;
	bool head = 0;
	bool weapon_rarity = 1;
	bool snaplines = 0;
	bool Cornerbox = 0;
	int Smoothing = 1;
	bool weapon_esp = 0;
	bool aimbot = 1;
	bool memory = 0;

	bool HeadBone = 1;
	bool target_line = 0;
	bool target_text = 0;
	bool player_info = 1;

	bool NeckBone = 0;
	bool ChestBone = 0;
	bool PelvisBone = 0;
	


	int max_distance = 100;
	int max_distance1 = 100;
	int max_distance2 = 250;
	int max_distance3 = 500;
	int max_distance4 = 100;


	int smooth = 1.0f;
	int field_of_view = 150.0f;
	bool render_field_of_view = 1;
	bool rendercrosshair = 0;
	bool rendercrosshairefk = 0;
	


	bool normal_fov = 1;
	bool star_fov = 0;
	bool chrome_fov = 0;
	bool weapon_cfg = 0;
	int aimbot_bone = 0;
	bool prediction = 1;
	int projectileGravityScale = 3.5f;
	

	bool color_crosshair = 1;
	bool box_color = 1;
	
	int aimbot_key = VK_XBUTTON2;
	int triggerbot_key = VK_XBUTTON2;

	bool showSelectKeyModal;
	bool DoVisibleCheck = 1;
	bool keyselected;
	bool triggerbot = 0;
	int custom_delay = 1;
	int maximum_distance = 10;
	bool has_clicked = 1;
	std::chrono::steady_clock::time_point tb_begin;
	std::chrono::steady_clock::time_point tb_end;
	int tb_time_since;

	int Linethick = 2.f;

	int box_thick = 1.f, skeleton_thick = 2.f;
}; static c_globals* globals = new c_globals();